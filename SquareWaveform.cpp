/* Dependencies */
#include "SquareWaveform.h"

namespace CheapTune {

SquareWaveform::SquareWaveform(uint8_t duty) :
	_duty(duty) {
}

void SquareWaveform::setDuty(uint8_t duty) {
	_duty = duty;
}

void SquareWaveform::reset() {
	_duty = 127;
}

Sample_t SquareWaveform::getSample(WavetableIndex_t index) {

	/* Move index value into the unsigned 8 bits range */
	index >>= (WAVETABLE_BITSIZE - 8);

	/* Return the sample */
	return (index >= _duty) ? SAMPLE_VMAX : SAMPLE_VMIN;
}

}
