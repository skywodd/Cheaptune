/* Dependencies */
#include <stdint.h>
#include "Oscillator.h"
#include "config.h"

namespace CheapTune {

Oscillator::Oscillator(uint16_t frequency) :
		_waveform(), _tuningWord(0), _phaseAccumulator(0), _syncFlag(0) {
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
	uint16_t acc = (uint16_t) _phaseAccumulator + _tuningWord;
	_phaseAccumulator = acc & 0xFF;

	/* Set the sync flag */
	_syncFlag = !!(acc & 0xFF00);

	/* Return the sample */
	return sample;
}

void Oscillator::reset() {
	_waveform.reset();
	_tuningWord = 0;
	_phaseAccumulator = 0;
}

uint8_t Oscillator::isCycleFinished() const {
	return _syncFlag;
}

void Oscillator::restartCycle() {
	_phaseAccumulator = 0;
}

Waveform& Oscillator::waveform() {
	return _waveform;
}

}

