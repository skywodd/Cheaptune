/* Dependencies */
#include "SawtoothWaveform.h"

namespace CheapTune {

Sample_t SawtoothWaveform::getSample(WavetableIndex_t index) {

	/* Sawtooth wave algorithm */
	if (index < (WAVETABLE_SAMPLES_COUNT / 2))
		return ((Sample_t) index) * SAMPLE_VMAX / (WAVETABLE_INDEX_BITMASK / 2);
	else
		return ((Sample_t) index - (WAVETABLE_SAMPLES_COUNT / 2)) * SAMPLE_VMAX / (WAVETABLE_INDEX_BITMASK / 2) + SAMPLE_VMIN;
}

}
