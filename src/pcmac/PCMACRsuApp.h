#pragma once
#include "veins/modules/application/ieee80211p/DemoBaseApplLayer.h"
#include "PCMACMessage_m.h"
using namespace veins;

class PCMACRsuApp : public DemoBaseApplLayer {
  public:
    void initialize(int stage) override;
  protected:
    void handleSelfMsg(cMessage* msg) override;
    void onWSM(BaseFrame1609_4* wsm) override;

    int    currentPlatoonSize = 0;
    double currentAvgVelocity = 0.0;

    cMessage* broadcastTimer = nullptr;
    static constexpr double BROADCAST_INTERVAL = 0.05; // 50ms CCH interval
};
