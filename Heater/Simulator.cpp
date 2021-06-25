#include "Simulator.h"
#include "model.h" // information from the modelDescription.xml
#include <QApplication>
#include <QDir>

// no runtime resources
#define RESOURCE_LOCATION ""

// callback functions
static void cb_logMessage(fmi2ComponentEnvironment componentEnvironment, fmi2String instanceName, fmi2Status status, fmi2String category, fmi2String message, ...) {
    printf("%s\n", message);
}

static void* cb_allocateMemory(size_t nobj, size_t size) {
    return calloc(nobj, size);
}

static void cb_freeMemory(void* obj) {
    free(obj);
}

// TODO: return error message if status != fmi2OK
#define CHECK_STATUS(c) status = c; if (status > fmi2Warning) { emit errorMessage("The FMU return an error status."); goto OUT; }


void Simulator::run()
{
    const QString sharedLibrary = QApplication::applicationDirPath() + QDir::separator() +
#ifdef _WIN32
            "Heater.dll";
#else
            "Heater.so";
#endif

    if (!QFileInfo::exists(sharedLibrary)) {
        emit errorMessage("Failed to load " + sharedLibrary + ". The shared library must be placed next to the executable.");
        return;
    }

    fmu = new FMU(sharedLibrary);

    fmi2Status status = fmi2OK;

    fmi2CallbackFunctions callbacks = { cb_logMessage, cb_allocateMemory, cb_freeMemory, NULL, NULL };

    const fmi2Component c = fmu->m_fmi2Instantiate("instance1", fmi2CoSimulation, GUID, RESOURCE_LOCATION, &callbacks, fmi2False, fmi2False);

    if (!c) {
        emit errorMessage("Failed to instantiate FMU.");
        return;
    }

    fmi2Real time = 0;
    fmi2Real stepSize = 0.1;

    CHECK_STATUS(fmu->m_fmi2SetupExperiment(c, fmi2False, 0, time, fmi2False, 0));

    CHECK_STATUS(fmu->m_fmi2EnterInitializationMode(c));

    CHECK_STATUS(fmu->m_fmi2ExitInitializationMode(c));

    // simulation loop
    while (true) {

        // set an input
        const fmi2ValueReference vr_u = VR_U;
        fmi2Boolean u = switchClosed ? fmi2False : fmi2True;
        CHECK_STATUS(fmu->m_fmi2SetBoolean(c, &vr_u, 1, &u));

        // set a tuneable paramter
        fmi2ValueReference vr_TAmb = VR_TAMB;
        fmi2Real TAmb = 273.15 + ambientTemperature;
        CHECK_STATUS(fmu->m_fmi2SetReal(c, &vr_TAmb, 1, &TAmb));

        // perform a simulation step
        CHECK_STATUS(fmu->m_fmi2DoStep(c, time, stepSize, fmi2True));

        // get an output
        const fmi2ValueReference vr_T = VR_T;
        fmi2Real T;
        CHECK_STATUS(fmu->m_fmi2GetReal(c, &vr_T, 1, &T));

        emit resultReady(T);

        time += stepSize;

        msleep(stepSize * 1000);
     }

    OUT:
    return;
}

void Simulator::openSwitch()
{
    switchClosed = false;
}

void Simulator::closeSwitch()
{
    switchClosed = true;
}

void Simulator::setAmbientTemperature(double temperature)
{
    ambientTemperature = temperature;
}
