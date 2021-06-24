#ifndef FMU_H
#define FMU_H

#ifdef _WIN32
#include <Windows.h>
#include "Shlwapi.h"
#pragma comment(lib, "shlwapi.lib")
#else
#include <dlfcn.h>
#define MAX_PATH 2048
#endif

#include <QObject>
#include "fmi2Functions.h"

class FMU : public QObject
{
    Q_OBJECT

public:
    explicit FMU(QString sharedLibrary, QObject *parent = nullptr);

#ifdef _WIN32
    HMODULE libraryHandle;
#else
    void *libraryHandle;
#endif
    template<typename T> T *get(const char *functionName) {

# ifdef _WIN32
        FARPROC fp = GetProcAddress(libraryHandle, functionName);
# else
        void *fp = dlsym(libraryHandle, functionName);
# endif

        return reinterpret_cast<T *>(fp);
    }

    /***************************************************
    Types for Common Functions
    ****************************************************/

    /* Inquire version numbers of header files and setting logging status */
    fmi2GetTypesPlatformTYPE *m_fmi2GetTypesPlatform;
    fmi2GetVersionTYPE       *m_fmi2GetVersion;
    fmi2SetDebugLoggingTYPE  *m_fmi2SetDebugLogging;

    /* Creation and destruction of FMU instances and setting debug status */
    fmi2InstantiateTYPE  *m_fmi2Instantiate;
    fmi2FreeInstanceTYPE *m_fmi2FreeInstance;

    /* Enter and exit initialization mode, terminate and reset */
    fmi2SetupExperimentTYPE         *m_fmi2SetupExperiment;
    fmi2EnterInitializationModeTYPE *m_fmi2EnterInitializationMode;
    fmi2ExitInitializationModeTYPE  *m_fmi2ExitInitializationMode;
    fmi2TerminateTYPE               *m_fmi2Terminate;
    fmi2ResetTYPE                   *m_fmi2Reset;

    /* Getting and setting variable values */
    fmi2GetRealTYPE    *m_fmi2GetReal;
    fmi2GetIntegerTYPE *m_fmi2GetInteger;
    fmi2GetBooleanTYPE *m_fmi2GetBoolean;
    fmi2GetStringTYPE  *m_fmi2GetString;

    fmi2SetRealTYPE    *m_fmi2SetReal;
    fmi2SetIntegerTYPE *m_fmi2SetInteger;
    fmi2SetBooleanTYPE *m_fmi2SetBoolean;
    fmi2SetStringTYPE  *m_fmi2SetString;

    /* Getting and setting the internal FMU state */
    fmi2GetFMUstateTYPE            *m_fmi2GetFMUstate;
    fmi2SetFMUstateTYPE            *m_fmi2SetFMUstate;
    fmi2FreeFMUstateTYPE           *m_fmi2FreeFMUstate;
    fmi2SerializedFMUstateSizeTYPE *m_fmi2SerializedFMUstateSize;
    fmi2SerializeFMUstateTYPE      *m_fmi2SerializeFMUstate;
    fmi2DeSerializeFMUstateTYPE    *m_fmi2DeSerializeFMUstate;

    /* Getting partial derivatives */
    fmi2GetDirectionalDerivativeTYPE *m_fmi2GetDirectionalDerivative;

    /***************************************************
    Types for Functions for FMI2 for Model Exchange
    ****************************************************/

    /* Enter and exit the different modes */
    fmi2EnterEventModeTYPE          *m_fmi2EnterEventMode;
    fmi2NewDiscreteStatesTYPE       *m_fmi2NewDiscreteStates;
    fmi2EnterContinuousTimeModeTYPE *m_fmi2EnterContinuousTimeMode;
    fmi2CompletedIntegratorStepTYPE *m_fmi2CompletedIntegratorStep;

    /* Providing independent variables and re-initialization of caching */
    fmi2SetTimeTYPE             *m_fmi2SetTime;
    fmi2SetContinuousStatesTYPE *m_fmi2SetContinuousStates;

    /* Evaluation of the model equations */
    fmi2GetDerivativesTYPE                *m_fmi2GetDerivatives;
    fmi2GetEventIndicatorsTYPE            *m_fmi2GetEventIndicators;
    fmi2GetContinuousStatesTYPE           *m_fmi2GetContinuousStates;
    fmi2GetNominalsOfContinuousStatesTYPE *m_fmi2GetNominalsOfContinuousStates;

    /***************************************************
    Types for Functions for FMI2 for Co-Simulation
    ****************************************************/

    /* Simulating the slave */
    fmi2SetRealInputDerivativesTYPE  *m_fmi2SetRealInputDerivatives;
    fmi2GetRealOutputDerivativesTYPE *m_fmi2GetRealOutputDerivatives;
    fmi2DoStepTYPE                   *m_fmi2DoStep;
    fmi2CancelStepTYPE               *m_fmi2CancelStep;

    /* Inquire slave status */
    fmi2GetStatusTYPE        *m_fmi2GetStatus;
    fmi2GetRealStatusTYPE    *m_fmi2GetRealStatus;
    fmi2GetIntegerStatusTYPE *m_fmi2GetIntegerStatus;
    fmi2GetBooleanStatusTYPE *m_fmi2GetBooleanStatus;
    fmi2GetStringStatusTYPE  *m_fmi2GetStringStatus;

signals:

};

#endif // FMU_H
