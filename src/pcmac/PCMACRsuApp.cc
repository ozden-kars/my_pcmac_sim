#include "PCMACRsuApp.h"

Define_Module(PCMACRsuApp);

void PCMACRsuApp::initialize(int stage)
{
    DemoBaseApplLayer::initialize(stage);
    if (stage == 0) {
        broadcastTimer = new cMessage("rsuBroadcast");
        scheduleAt(simTime() + BROADCAST_INTERVAL, broadcastTimer);
    }
}

void PCMACRsuApp::handleSelfMsg(cMessage* msg)
{
    if (msg == broadcastTimer) {
        PCMACMessage* beacon = new PCMACMessage();
        populateWSM(beacon);
        beacon->setIsEmergency(false);
        beacon->setPlatoonSize(currentPlatoonSize);
        beacon->setPlatoonAvgVelocity(currentAvgVelocity);
        beacon->setUserPriority(3); // AC_BE — RSU broadcasts are not safety-critical
        beacon->setBitLength(400);
        sendDown(beacon);
        scheduleAt(simTime() + BROADCAST_INTERVAL, broadcastTimer);
    } else {
        DemoBaseApplLayer::handleSelfMsg(msg);
    }
}

void PCMACRsuApp::onWSM(BaseFrame1609_4* wsm)
{
    // RSU passively listens to vehicle beacons to track platoon size/velocity
    if (auto* pcmsg = dynamic_cast<PCMACMessage*>(wsm)) {
        // Update running estimates — in a full implementation this would
        // aggregate across all received beacons in the last interval
        currentAvgVelocity = pcmsg->getSenderSpeed();
    }
}
