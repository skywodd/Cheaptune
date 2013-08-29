/* Dependencies */
#include "Waveform.h"
#include "Oscillator.h"

namespace CheapTune {

Oscillator::Oscillator(Waveform* waveform, Frequency_t frequency) :
		_waveform(waveform), _tuningWord(0), _phaseAccumulator(0), _syncFlag(false) {
	if (frequency)
		setFrequency(frequency);
}

Oscillator::~Oscillator() {
}

void Oscillator::setFrequency(Frequency_t frequency) {

	/* Based on DDS algebra : Fo (output frequency) = (M (tuning word) x Fc (sample frequency)) / pow(2, N)*/
	_tuningWord = ((uint32_t) frequency * WAVETABLE_SAMPLES_COUNT) / SAMPLE_RATE;
}

void Oscillator::setWaveform(Waveform* waveform) {
	_waveform = waveform;
}

Sample_t Oscillator::getSample() {

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

void Oscillator::reset() {
	_waveform->reset();
	_tuningWord = 0;
	_phaseAccumulator = 0;
	_syncFlag = false;
}

bool Oscillator::isCycleFinished() const {
	return _syncFlag;
}

void Oscillator::restartCycle(WavetableIndex_t index) {
	_phaseAccumulator = index;
}

Waveform* Oscillator::waveform() {
	return _waveform;
}

}

