/* Dependencies */
#include "TriangleWaveform.h"

namespace CheapTune {

Sample_t TriangleWaveform::getSample(WavetableIndex_t index) {

	/* Triangle wave algorithm */
	if (index < (WAVETABLE_SAMPLES_COUNT / 4))
		return ((Sample_t) index) * SAMPLE_VMAX / (WAVETABLE_INDEX_BITMASK / 4);
	else if (index >= (WAVETABLE_SAMPLES_COUNT / 4) && index < (WAVETABLE_SAMPLES_COUNT / 4 * 2))
		return ((Sample_t) index - (WAVETABLE_SAMPLES_COUNT / 4)) * SAMPLE_VMIN / (WAVETABLE_INDEX_BITMASK / 4) + SAMPLE_VMAX;
	else if (index >= (WAVETABLE_SAMPLES_COUNT / 4 * 2) && index < (WAVETABLE_SAMPLES_COUNT / 4 * 3))
		return ((Sample_t) index - (WAVETABLE_SAMPLES_COUNT / 4 * 2)) * SAMPLE_VMIN / (WAVETABLE_INDEX_BITMASK / 4);
	else
		return ((Sample_t) index - (WAVETABLE_SAMPLES_COUNT / 4 * 3)) * SAMPLE_VMAX / (WAVETABLE_INDEX_BITMASK / 4) + SAMPLE_VMIN;
}

}
