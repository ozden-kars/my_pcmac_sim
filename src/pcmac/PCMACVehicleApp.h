#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "PCMACMessage_m.h"
using namespace veins;

class PCMACVehicleApp : public DemoBaseApplLayer {
  public:
    void initialize(int stage) override;
    void finish() override;

  protected:
    // OMNeT++ application layer hooks
    void onBSM(DemoSafetyMessage* bsm) override;
    void onWSM(BaseFrame1609_4* wsm) override;
    void handleSelfMsg(cMessage* msg) override;
    void handlePositionUpdate(cObject* obj) override;

    // ── PCMAC core — implements paper Equations 1–5 ──────────────────
    double computeImpact();              // Equation 1: vehicles_behind / N
    double computeAvgRelativeDistance(); // Equation 2: avg distance to neighbours
    double computePriority();            // Equation 4: AD / (Impact * AV)
    int    mapPriorityToCW(double priority); // Equation 5: CW from priority
    void   sendEmergencyMessage();       // adapts CW then sends emergency packet

    // ── RSU-provided platoon state (updated via onWSM) ────────────────
    int    platoonSize        = 0;
    double platoonAvgVelocity = 0.0;
    bool   eventActive        = false;
    double accidentX          = -1;
    double accidentY          = -1;
    bool   usePCMAC           = true;  // set false to run as standard IEEE 802.11p

    // ── Neighbour table — built from received beacons ─────────────────
    struct NeighborInfo {
        double x, y, speed;
        simtime_t lastSeen;
    };
    std::map<int, NeighborInfo> neighbors;

    // ── OMNeT++ statistic signals ─────────────────────────────────────
    simsignal_t sigDelay;
    simsignal_t sigEmergencyServiced;
    simsignal_t sigThroughput;

    // ── Constants matching paper parameters ──────────────────────────
    static constexpr double COMM_RANGE = 100.0; // communication range in metres
    static constexpr int    CWMIN_VO   = 3;     // AC_VO cwMin (IEEE 802.11p)
    static constexpr int    CWMAX_VO   = 7;     // AC_VO cwMax (IEEE 802.11p)
};
