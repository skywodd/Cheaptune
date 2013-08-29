/* Dependencies */
#include "LowFrequencyOscillator.h"

namespace CheapTune {

LowFrequencyOscillator::LowFrequencyOscillator(Waveform* waveform,
		Prescaler_t prescaler, Frequency_t frequency) :
		Oscillator(waveform, frequency), _sample(0), _prescaler(prescaler), _counter(0) {
}

void LowFrequencyOscillator::setPrescaler(Prescaler_t prescaler) {
	_prescaler = prescaler;
}

void LowFrequencyOscillator::setFrequency(Frequency_t frequency) {

	/* Based on DDS algebra : Fo (output frequency) = (M (tuning word) x Fc (sample frequency)) / pow(2, N)*/
	_tuningWord = ((uint32_t) frequency * WAVETABLE_SAMPLES_COUNT) / (SAMPLE_RATE / _prescaler);
}

Sample_t LowFrequencyOscillator::getSample() {

	/* If counter reach zero */
	if(_counter == 0) {

		/* Get a fresh sample */
		_sample = Oscillator::getSample();

		/* Restart counter */
		_counter = _prescaler;

	} else
		/* Decrement counter */
		--_counter;

	/* Return the sample */
	return _sample;
}

void LowFrequencyOscillator::reset() {
	_sample = 0;
	_prescaler = 1;
	_counter = 0;
	Oscillator::reset();
}

void LowFrequencyOscillator::restartCycle(WavetableIndex_t index) {
	_counter = 0;
	Oscillator::restartCycle(index);
}

}
