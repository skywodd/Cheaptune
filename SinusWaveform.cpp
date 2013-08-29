/* Dependencies */
#include "SinusWaveform.h"

namespace CheapTune {

const Sample_t SinusWaveform::_sinusWavetable[WAVETABLE_SAMPLES_COUNT / 4] PROGMEM
= {
#if WAVETABLE_BITSIZE == 9
#include "data/sinus_9b.inc"
#elif WAVETABLE_BITSIZE == 10
#include "data/sinus_10b.inc"
#elif WAVETABLE_BITSIZE == 11
#include "data/sinus_11b.inc"
#elif WAVETABLE_BITSIZE == 12
#include "data/sinus_12b.inc"
#elif WAVETABLE_BITSIZE == 13
#include "data/sinus_13b.inc"
#elif WAVETABLE_BITSIZE == 14
#include "data/sinus_14b.inc"
#elif WAVETABLE_BITSIZE == 15
#include "data/sinus_15b.inc"
#elif WAVETABLE_BITSIZE == 16
#include "data/sinus_16b.inc"
#else
#error "Wave table size not supported"
#endif
		};

Sample_t SinusWaveform::getSample(WavetableIndex_t index) {

	/* Return sinus sample using only 1/4 of wave */
	if (index < (WAVETABLE_SAMPLES_COUNT / 4)) {
		return PROGMEM_READWORD(_sinusWavetable, index);
	} else if (index >= (WAVETABLE_SAMPLES_COUNT / 4) && index < (WAVETABLE_SAMPLES_COUNT / 2)) {
		index -= WAVETABLE_SAMPLES_COUNT / 4;
		return PROGMEM_READWORD(_sinusWavetable, (WAVETABLE_INDEX_BITMASK / 4) - index);
	} else if (index >= (WAVETABLE_SAMPLES_COUNT / 2) && index < (WAVETABLE_SAMPLES_COUNT / 4 * 3)) {
		index -= WAVETABLE_SAMPLES_COUNT / 2;
		return -PROGMEM_READWORD(_sinusWavetable, index);
	} else {
		index -= WAVETABLE_SAMPLES_COUNT / 4 * 3;
		return -PROGMEM_READWORD(_sinusWavetable, (WAVETABLE_INDEX_BITMASK / 4) - index);
	}
}

}
