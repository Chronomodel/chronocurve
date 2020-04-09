#include "ChronocurveConfig.h"
#include "Application.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    cout << "---------------------------------------------------------------------" << endl;
    cout << "=> Chronocurve " << Chronocurve_VERSION_MAJOR << "." << Chronocurve_VERSION_MINOR << endl;
    cout << "---------------------------------------------------------------------" << endl;
    
    // standalone : argc and argv should be used
    // library : export functions to call the app

    Application app;
    app.display();
    
    return 1;
}
