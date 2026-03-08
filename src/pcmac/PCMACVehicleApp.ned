package pcmac;

import org.car2x.veins.modules.application.ieee80211p.DemoBaseApplLayer;

simple PCMACVehicleApp extends DemoBaseApplLayer
{
    parameters:
        @class(PCMACVehicleApp);
        @display("i=block/app2");
        bool usePCMAC = default(true);  // false = standard IEEE 802.11p baseline

        @signal[delay](type=double);
        @signal[emergencyServiced](type=long);
        @signal[throughput](type=double);

        @statistic[delay](
            source=delay;
            record=mean,max,vector;
            unit=s;
            title="Emergency message end-to-end delay");

        @statistic[emergencyServiced](
            source=emergencyServiced;
            record=count,sum;
            title="Emergency messages successfully received");

        @statistic[throughput](
            source=throughput;
            record=mean,timeavg;
            title="Channel throughput");
}
