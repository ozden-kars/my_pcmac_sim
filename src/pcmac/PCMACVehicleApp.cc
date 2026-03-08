#include "PCMACVehicleApp.h"
#include <cmath>
#include <algorithm>

Define_Module(PCMACVehicleApp);

void PCMACVehicleApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        sigDelay             = registerSignal("delay");
        sigEmergencyServiced = registerSignal("emergencyServiced");
        sigThroughput        = registerSignal("throughput");
        usePCMAC             = par("usePCMAC").boolValue();
    }
}

void PCMACVehicleApp::finish()
{
    DemoBaseApplLayer::finish();
}

// ── Equation (1): Impact = vehicles_behind / total_platoon ───────────────
double PCMACVehicleApp::computeImpact()
{
    int behind = 0;
    Coord myPos = mobility->getPositionAt(simTime());
    for (auto& [id, nb] : neighbors)
        if (nb.x < myPos.x) behind++;
    if (platoonSize <= 1) return 0.0;
    return (double)behind / platoonSize;
}

// ── Equation (2): ADi = (1/(N-1)) * sum of distances to all neighbours ──
double PCMACVehicleApp::computeAvgRelativeDistance()
{
    if (neighbors.empty()) return COMM_RANGE;
    Coord myPos = mobility->getPositionAt(simTime());
    double sum = 0.0;
    for (auto& [id, nb] : neighbors) {
        double dx = nb.x - myPos.x;
        double dy = nb.y - myPos.y;
        sum += std::sqrt(dx * dx + dy * dy);
    }
    return sum / neighbors.size();
}

// ── Equation (4): Priority = AD / (Impact * AV) ──────────────────────────
double PCMACVehicleApp::computePriority()
{
    double impact = computeImpact();
    double ad     = computeAvgRelativeDistance();
    double av     = (platoonAvgVelocity > 0.0) ? platoonAvgVelocity : 1.0;
    double denom  = impact * av;
    if (denom < 1e-9) return 1.0; // guard against division by zero
    return ad / denom;
}

// ── Equation (5): CWnewmax = (P*10) * (CWmax - CWmin) / 13 ──────────────
int PCMACVehicleApp::mapPriorityToCW(double P)
{
    int cw = (int)((P * 10.0) * (CWMAX_VO - CWMIN_VO) / 13.0);
    return std::max(CWMIN_VO, std::min(cw, CWMAX_VO));
}

// ── Send emergency message with PCMAC-adapted contention window ──────────
void PCMACVehicleApp::sendEmergencyMessage()
{
    double priority = computePriority();
    int    newCw    = mapPriorityToCW(priority);

    if (usePCMAC) {
        mac->setPCMACContWindow(newCw); // PCMAC mode
    }

    PCMACMessage* msg = new PCMACMessage();
    populateWSM(msg);
    msg->setIsEmergency(true);
    msg->setPriority(priority);
    Coord pos = mobility->getPositionAt(simTime());
    msg->setSenderX(pos.x);
    msg->setSenderY(pos.y);
    msg->setSenderSpeed(mobility->getSpeed());
    msg->setPlatoonSize(platoonSize);
    msg->setPlatoonAvgVelocity(platoonAvgVelocity);
    msg->setUserPriority(7);    // AC_VO — highest priority queue
    msg->setBitLength(800);     // 100 bytes as specified in paper
    sendDown(msg);

    if (usePCMAC) {
        mac->resetContWindow();
    }
}

// ── Handle received beacons — update neighbour table ─────────────────────
void PCMACVehicleApp::onBSM(DemoSafetyMessage* bsm)
{
    NeighborInfo info;
    info.x        = bsm->getSenderPos().x;
    info.y        = bsm->getSenderPos().y;
    info.speed    = bsm->getSenderSpeed().length();
    info.lastSeen = simTime();
    neighbors[bsm->getSenderModuleId()] = info;
}

// ── Handle received WSM — read RSU platoon broadcasts ────────────────────
void PCMACVehicleApp::onWSM(BaseFrame1609_4* wsm)
{
    if (auto* pcmsg = dynamic_cast<PCMACMessage*>(wsm)) {
        if (!pcmsg->isEmergency()) {
            // RSU broadcast — update platoon-level state
            platoonSize        = pcmsg->getPlatoonSize();
            platoonAvgVelocity = pcmsg->getPlatoonAvgVelocity();
        } else {
            // Emergency message received — record delivery metrics
            double delay = (simTime() - pcmsg->getCreationTime()).dbl();
            emit(sigDelay, delay);
            emit(sigEmergencyServiced, (long)1);
        }
    }
}

// ── Handle self messages — accident trigger ───────────────────────────────
void PCMACVehicleApp::handleSelfMsg(cMessage* msg)
{
    if (strcmp(msg->getName(), "sendEmergency") == 0) {
        sendEmergencyMessage();
        delete msg;
    } else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

// ── Handle position updates from TraCI — detect leading vehicle stop ──────
void PCMACVehicleApp::handlePositionUpdate(cObject* obj)
{
    DemoBaseApplLayer::handlePositionUpdate(obj);

    // At t=10s the leading vehicle stops abruptly to simulate accident
    if (simTime() >= 10.0 && !eventActive) {
        Coord myPos = mobility->getPositionAt(simTime());
        bool isLeader = true;
        for (auto& [id, nb] : neighbors)
            if (nb.x > myPos.x) { isLeader = false; break; }

        if (isLeader) {
            traciVehicle->setSpeed(0); // abrupt stop via TraCI
            eventActive = true;
            scheduleAt(simTime(), new cMessage("sendEmergency"));
        }
    }
}
