/* Dependencies */
#include "ExponentialResponse.h"

namespace CheapTune {

const Sample_t ExponentialResponse::_expWavetable[WAVETABLE_EXP_SAMPLES_COUNT] PROGMEM
= {
#if WAVETABLE_BITSIZE == 9
#include "data/exp_9b.inc"
#elif WAVETABLE_BITSIZE == 10
#include "data/exp_10b.inc"
#elif WAVETABLE_BITSIZE == 11
#include "data/exp_11b.inc"
#elif WAVETABLE_BITSIZE == 12
#include "data/exp_12b.inc"
#elif WAVETABLE_BITSIZE == 13
#include "data/exp_13b.inc"
#elif WAVETABLE_BITSIZE == 14
#include "data/exp_14b.inc"
#elif WAVETABLE_BITSIZE == 15
#include "data/exp_15b.inc"
#elif WAVETABLE_BITSIZE == 16
#include "data/exp_16b.inc"
#else
#error "Wave table size not supported"
#endif
		};

Amplitude_t ExponentialResponse::getResponse(WavetableIndex_t t,
		WavetableIndex_t T, Amplitude_t MIN, Amplitude_t MAX) {

	/* Get the index in wave table */
	uint16_t index = ((uint16_t) WAVETABLE_INDEX_BITMASK * t) / T;

	/* Get the exponential sample */
	Sample_t exp = PROGMEM_READBYTE(_expWavetable, index);

	/* Check for "falling response" */
	if (MAX < MIN)
		/* Reverse exponential sample */
		exp = 255 - exp;

	/* Map exponential sample from 0~255 to MIN~MAX limits */
	exp = exp * (MAX - MIN) / 255 + MIN;

	/* Return the response amplitude */
	return (Amplitude_t) exp;
}

}
