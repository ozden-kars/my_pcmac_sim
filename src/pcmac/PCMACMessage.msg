cplusplus {{
#include "veins/modules/messages/BaseFrame1609_4_m.h"
}}

class veins::BaseFrame1609_4 extends omnetpp::cPacket {
    @existingClass;
    @descriptor(false);
    @castFunction(false);
}

packet PCMACMessage extends veins::BaseFrame1609_4 {
    bool   isEmergency = false;      // true = event msg, false = beacon
    double priority    = 0.0;        // PCMAC priority (Equation 4)
    double senderX;                  // sender position at send time
    double senderY;
    double senderSpeed;              // m/s
    int    platoonSize;              // N — received from RSU broadcast
    double platoonAvgVelocity;       // V — received from RSU broadcast
    int    vehiclesBehind;           // count of trailing vehicles
}
