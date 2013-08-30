/* Dependencies */
#include "Waveform.h"
#include "StandardOscillator.h"

namespace CheapTune {

StandardOscillator::StandardOscillator(Waveform* waveform, Frequency_t frequency) :
		_waveform(waveform), _tuningWord(0), _phaseAccumulator(0), _syncFlag(false) {
	if (frequency)
		setFrequency(frequency);
}

void StandardOscillator::setFrequency(Frequency_t frequency) {

	/* Based on DDS algebra : Fo (output frequency) = (M (tuning word) x Fc (sample frequency)) / pow(2, N)*/
	_tuningWord = ((uint32_t) frequency * WAVETABLE_SAMPLES_COUNT) / SAMPLE_RATE;
}

void StandardOscillator::setWaveform(Waveform* waveform) {
	_waveform = waveform;
}

Sample_t StandardOscillator::getSample() {

	/* Get the current indexed sample from the waveform generator */
	Sample_t sample = _waveform->getSample(_phaseAccumulator);

	/* Go to the next sample index */
	uint32_t acc = (uint32_t) _phaseAccumulator + _tuningWord;
	_phaseAccumulator = acc & WAVETABLE_INDEX_BITMASK;

	/* Set the sync flag */
	_syncFlag = !!(acc & 0xFFFF0000);

	/* Return the sample */
	return sample;
}

void StandardOscillator::reset() {
	_waveform->reset();
	_tuningWord = 0;
	_phaseAccumulator = 0;
	_syncFlag = false;
}

bool StandardOscillator::isCycleFinished() const {
	return _syncFlag;
}

void StandardOscillator::restartCycle(WavetableIndex_t index) {
	_phaseAccumulator = index;
}

Waveform* StandardOscillator::waveform() {
	return _waveform;
}

}

