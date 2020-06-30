#include <stdio.h>

// from the modelDescription.xml
#define FMI2_FUNCTION_PREFIX Heater_
#define GUID                 "{f9fd9ac5-e928-4f40-869d-f3292ba07eba}"
#define VR_T                 335544320
#define VR_U                 352321536
#define VR_TAMB              16777216

// no runtime resources
#define RESOURCE_LOCATION ""

#include "fmi2Functions.h"

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

#define CHECK_STATUS(S) { status = S; if (status != fmi2OK) goto TERMINATE; }

int main(int argc, char *argv[]) {

	fmi2Status status = fmi2OK;

	fmi2CallbackFunctions callbacks = { cb_logMessage, cb_allocateMemory, cb_freeMemory, NULL, NULL };

	fmi2Component c = Heater_fmi2Instantiate("instance1", fmi2CoSimulation, GUID, RESOURCE_LOCATION, &callbacks, fmi2False, fmi2False);

	if (!c) return 1;

	fmi2Real time = 0;
	fmi2Real stepSize = 0.1;

	CHECK_STATUS(Heater_fmi2SetupExperiment(c, fmi2False, 0, time, fmi2False, 0));

	CHECK_STATUS(Heater_fmi2EnterInitializationMode(c));

	fmi2ValueReference vr_TAmb = VR_TAMB;
	fmi2Real TAmb = 266;

	// set a tuneable paramter
	CHECK_STATUS(Heater_fmi2SetReal(c, &vr_TAmb, 1, &TAmb));

	CHECK_STATUS(Heater_fmi2ExitInitializationMode(c));

	printf("time, u, T\n");

	for (int nSteps = 0; nSteps <= 100; nSteps++) {

		time = nSteps * stepSize;

		fmi2ValueReference vr_T = VR_T;
		fmi2Real T;

		// get an output
		CHECK_STATUS(Heater_fmi2GetReal(c, &vr_T, 1, &T));

		// perform a simulation step
		CHECK_STATUS(Heater_fmi2DoStep(c, time, stepSize, fmi2True));

		fmi2ValueReference vr_u = VR_U;
		fmi2Boolean u = T > 40;

		// set an input
		CHECK_STATUS(Heater_fmi2SetBoolean(c, &vr_u, 1, &u));

		printf("%.2f, %d, %.2f\n", time, u, T);
	}

TERMINATE:

	// clean up
	if (status < fmi2Fatal) {
		Heater_fmi2FreeInstance(c);
	}

	return status;
}
