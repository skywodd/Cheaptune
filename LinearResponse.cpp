/* Dependencies */
#include "LinearResponse.h"

namespace CheapTune {

Amplitude_t LinearResponse::getResponse(WavetableIndex_t t, WavetableIndex_t T,
		Amplitude_t MIN, Amplitude_t MAX) {
	return ((uint16_t) MAX * t) / T + MIN; // Simple y = ax + b equation
}

}
