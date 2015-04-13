#include <iostream>
#include <thread>
#include <chrono>
#include <iomanip>

#include <kybernetes/constants/constants.hpp>
#include <kybernetes/utility/application.hpp>
#include <kybernetes/sensor/garmingps.hpp>

using namespace std;

using namespace kybernetes::sensor;
using namespace kybernetes::constants;
using namespace kybernetes::utility;

class TestApplication : public Application::Delegate
{
    GarminGPS *gps;

public:
    void ApplicationDidLaunch(Application *application, int argc, char **argv)
    {
        gps = new GarminGPS(GPSPath, dispatch_get_main_queue());
        gps->SetHandler([] (const GarminGPS::State& state)
        {
            cout << "Received GPS Packet @ " << asctime(localtime((time_t *) &state.timestamp));
            cout << setprecision(10) << "    Latitude  = " << state.latitude << " degrees" << endl;
            cout << setprecision(10) <<  "    Longitude = " << state.longitude << " degrees" << endl;
            cout << setprecision(10) <<  "    Altitude  = " << state.altitude << " meters" << endl;
            cout << endl;
        });
    }
    void ApplicationWillTerminate()
    {
        cout << "Termination Requested" << endl;
        delete gps;
    }
};

int main (int argc, char** argv)
{
    Application::Run<TestApplication>(argc, argv);
    return 0;
}
