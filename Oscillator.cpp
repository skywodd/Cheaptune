/* Dependencies */
#include <stdint.h>
#include "Oscillator.h"
#include "config.h"

namespace CheapTune {

Oscillator::Oscillator(uint16_t frequency) :
		_waveform(), _tuningWord(0), _phaseAccumulator(0) {
	if (frequency)
		setFrequency(frequency);
}

void Oscillator::setFrequency(uint16_t frequency) {

	/* Based on DDS algebra : Fo (output frequency) = (M (tuning word) x Fc (sample frequency)) / pow(2, N)*/
	_tuningWord = ((uint32_t) frequency * 256) / SAMPLE_RATE;
}

int8_t Oscillator::getSample() {

	/* Get the current indexed sample from the waveform generator */
	int8_t sample = _waveform.getSample(_phaseAccumulator);

	/* Go to the next sample index */
	_phaseAccumulator = ((uint16_t) _phaseAccumulator + _tuningWord) & 0xFF;

	/* Return the sample */
	return sample;
}

void Oscillator::reset() {
	_waveform.reset();
	_tuningWord = 0;
	_phaseAccumulator = 0;
}

Waveform& Oscillator::waveform() {
	return _waveform;
}

}

