
package pcmac;

import org.car2x.veins.base.connectionManager.ConnectionManager;
import org.car2x.veins.base.modules.BaseWorldUtility;
import org.car2x.veins.modules.world.annotations.AnnotationManager;
import org.car2x.veins.nodes.RSU;

import org.car2x.plexe.PlexeManager;
import org.car2x.plexe.traci.PlexeScenarioManager;
import org.car2x.plexe.traci.PlexeScenarioManagerLaunchd;
import org.car2x.plexe.traci.PlexeScenarioManagerForker;
import org.car2x.plexe.mobility.TraCIBaseTrafficManager;

import org.car2x.veins.nodes.Car;
import org.car2x.cooperis.Ris;

network HighwayPCMAC
{
    parameters:
        double playgroundSizeX @unit(m);
        double playgroundSizeY @unit(m);
        double playgroundSizeZ @unit(m);
        string traffic_type;
        bool useLaunchd = default(false);
        bool useManager = default(true);
        bool useTraffic = default(true);
        string manager_type = useLaunchd ? "PlexeScenarioManagerLaunchd" : "PlexeScenarioManagerForker";
        int numVehicles = default(10);
        int numRis      = default(0);
        @display("bgb=dropUnit($playgroundSizeX),dropUnit($playgroundSizeY)");

    submodules:
        annotations: AnnotationManager {
            @display("p=260,50");
        }
        connectionManager: ConnectionManager {
            parameters:
                @display("p=150,0;i=abstract/multicast");
        }
        world: BaseWorldUtility {
            parameters:
                playgroundSizeX = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeX", 1525, "parent.playgroundSizeX");
                playgroundSizeY = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeY", 1525, "parent.playgroundSizeY");
                playgroundSizeZ = veins_eval_by_version(veins_omnetpp_buildnum(), "playgroundSizeZ", 1525, "parent.playgroundSizeZ");
                @display("p=30,0;i=misc/globe");
        }
        manager: <manager_type> like PlexeScenarioManager if useManager {
            parameters:
                @display("p=512,128");
        }
        plexe: PlexeManager if useManager {
            @display("p=280,50");
        }
        traffic: <traffic_type> like TraCIBaseTrafficManager if useTraffic {
            parameters:
                @display("p=200,200");
        }

        // Vehicle nodes — size 0 when TraCI manager handles spawning, numVehicles for static
        node[useManager ? 0 : numVehicles]: Car {
            @display("i=car;is=vs");
        }

        // Single RSU broadcasting platoon state every 50ms
        rsu[1]: RSU {
            parameters:
                applType = "PCMACRsuApp";
                @display("i=device/antennatower;is=s");
        }

        // RIS panels — numRis=0 for NoRIS config, numRis=2 for WithRIS config
        ris[numRis]: Ris {
            @display("i=device/receiverdish;is=s");
        }

    connections allowunconnected:
}
