#include "FMU.h"

FMU::FMU(QString sharedLibrary, QObject *parent) : QObject(parent)
{

    QByteArray ba = sharedLibrary.toLocal8Bit();
    const char *cstr = ba.data();

#ifdef _WIN32
    libraryHandle = LoadLibraryA(cstr);
#else
    libraryHandle = dlopen(cstr, RTLD_LAZY);
#endif

//    if (!libraryHandle) {
//        throw runtime_error("Failed to load shared library " + libraryPath + ".");
//    }

    /***************************************************
    Types for Common Functions
    ****************************************************/

    /* Inquire version numbers of header files and setting logging status */
    m_fmi2GetTypesPlatform = get<fmi2GetTypesPlatformTYPE> ("fmi2GetTypesPlatform");
    m_fmi2GetVersion       = get<fmi2GetVersionTYPE>       ("fmi2GetVersion");
    m_fmi2SetDebugLogging  = get<fmi2SetDebugLoggingTYPE>  ("fmi2SetDebugLogging");

    /* Creation and destruction of FMU instances and setting debug status */
    m_fmi2Instantiate  = get<fmi2InstantiateTYPE>  ("fmi2Instantiate");
    m_fmi2FreeInstance = get<fmi2FreeInstanceTYPE> ("fmi2FreeInstance");

    /* Enter and exit initialization mode, terminate and reset */
    m_fmi2SetupExperiment         = get<fmi2SetupExperimentTYPE>         ("fmi2SetupExperiment");
    m_fmi2EnterInitializationMode = get<fmi2EnterInitializationModeTYPE> ("fmi2EnterInitializationMode");
    m_fmi2ExitInitializationMode  = get<fmi2ExitInitializationModeTYPE>  ("fmi2ExitInitializationMode");
    m_fmi2Terminate               = get<fmi2TerminateTYPE>               ("fmi2Terminate");
    m_fmi2Reset                   = get<fmi2ResetTYPE>                   ("fmi2Reset");

    /* Getting and setting variable values */
    m_fmi2GetReal    = get<fmi2GetRealTYPE>    ("fmi2GetReal");
    m_fmi2GetInteger = get<fmi2GetIntegerTYPE> ("fmi2GetInteger");
    m_fmi2GetBoolean = get<fmi2GetBooleanTYPE> ("fmi2GetBoolean");
    m_fmi2GetString  = get<fmi2GetStringTYPE>  ("fmi2GetString");

    m_fmi2SetReal    = get<fmi2SetRealTYPE>    ("fmi2SetReal");
    m_fmi2SetInteger = get<fmi2SetIntegerTYPE> ("fmi2SetInteger");
    m_fmi2SetBoolean = get<fmi2SetBooleanTYPE> ("fmi2SetBoolean");
    m_fmi2SetString  = get<fmi2SetStringTYPE>  ("fmi2SetString");

    /* Getting and setting the internal FMU state */
    m_fmi2GetFMUstate            = get<fmi2GetFMUstateTYPE>            ("fmi2GetFMUstate");
    m_fmi2SetFMUstate            = get<fmi2SetFMUstateTYPE>            ("fmi2SetFMUstate");
    m_fmi2FreeFMUstate           = get<fmi2FreeFMUstateTYPE>           ("fmi2FreeFMUstate");
    m_fmi2SerializedFMUstateSize = get<fmi2SerializedFMUstateSizeTYPE> ("fmi2SerializedFMUstateSize");
    m_fmi2SerializeFMUstate      = get<fmi2SerializeFMUstateTYPE>      ("fmi2SerializeFMUstate");
    m_fmi2DeSerializeFMUstate    = get<fmi2DeSerializeFMUstateTYPE>    ("fmi2DeSerializeFMUstate");

    /* Getting partial derivatives */
    m_fmi2GetDirectionalDerivative = get<fmi2GetDirectionalDerivativeTYPE>("fmi2GetDirectionalDerivative");

    /***************************************************
    Types for Functions for FMI2 for Model Exchange
    ****************************************************/

    /* Enter and exit the different modes */
    m_fmi2EnterEventMode                = get<fmi2EnterEventModeTYPE>                ("fmi2EnterEventMode");
    m_fmi2NewDiscreteStates             = get<fmi2NewDiscreteStatesTYPE>             ("fmi2NewDiscreteStates");
    m_fmi2EnterContinuousTimeMode       = get<fmi2EnterContinuousTimeModeTYPE>       ("fmi2EnterContinuousTimeMode");
    m_fmi2CompletedIntegratorStep       = get<fmi2CompletedIntegratorStepTYPE>       ("fmi2CompletedIntegratorStep");

    /* Providing independent variables and re-initialization of caching */
    m_fmi2SetTime                       = get<fmi2SetTimeTYPE>                       ("fmi2SetTime");
    m_fmi2SetContinuousStates           = get<fmi2SetContinuousStatesTYPE>           ("fmi2SetContinuousStates");

    /* Evaluation of the model equations */
    m_fmi2GetDerivatives                = get<fmi2GetDerivativesTYPE>                ("fmi2GetDerivatives");
    m_fmi2GetEventIndicators            = get<fmi2GetEventIndicatorsTYPE>            ("fmi2GetEventIndicators");
    m_fmi2GetContinuousStates           = get<fmi2GetContinuousStatesTYPE>           ("fmi2GetContinuousStates");
    m_fmi2GetNominalsOfContinuousStates = get<fmi2GetNominalsOfContinuousStatesTYPE> ("fmi2GetNominalsOfContinuousStates");

    /***************************************************
    Types for Functions for FMI2 for Co-Simulation
    ****************************************************/

    /* Simulating the slave */
    m_fmi2SetRealInputDerivatives  = get<fmi2SetRealInputDerivativesTYPE>  ("fmi2SetRealInputDerivatives");
    m_fmi2GetRealOutputDerivatives = get<fmi2GetRealOutputDerivativesTYPE> ("fmi2GetRealOutputDerivatives");
    m_fmi2DoStep                   = get<fmi2DoStepTYPE>                   ("fmi2DoStep");
    m_fmi2CancelStep               = get<fmi2CancelStepTYPE>               ("fmi2CancelStep");

    /* Inquire slave status */
    m_fmi2GetStatus        = get<fmi2GetStatusTYPE>        ("fmi2GetStatus");
    m_fmi2GetRealStatus    = get<fmi2GetRealStatusTYPE>    ("fmi2GetRealStatus");
    m_fmi2GetIntegerStatus = get<fmi2GetIntegerStatusTYPE> ("fmi2GetIntegerStatus");
    m_fmi2GetBooleanStatus = get<fmi2GetBooleanStatusTYPE> ("fmi2GetBooleanStatus");
    m_fmi2GetStringStatus  = get<fmi2GetStringStatusTYPE>  ("fmi2GetStringStatus");

}
