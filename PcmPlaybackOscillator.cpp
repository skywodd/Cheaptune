/* Dependencies */
#include "PcmPlaybackOscillator.h"

namespace CheapTune {

PcmPlaybackOscillator::PcmPlaybackOscillator() :
		_index(0), _limit(PCM_SAMPLES_COUNT) {
}

SampleCount_t PcmPlaybackOscillator::writeBufferData(Sample_t* src,
		SampleCount_t count, SampleCount_t offset) {

	/* Avoid overflow */
	if ((count + offset) > PCM_SAMPLES_COUNT)
		count = PCM_SAMPLES_COUNT - offset;

	/* Copy data block */
	for (SampleCount_t i = offset; i < count; ++i)
		_buffer[i] = src[i];

	/* Return the "real" count */
	return count;
}

SampleCount_t PcmPlaybackOscillator::fillBuffer(Sample_t value,
		SampleCount_t count, SampleCount_t offset) {

	/* Avoid overflow */
	if ((count + offset) > PCM_SAMPLES_COUNT)
			count = PCM_SAMPLES_COUNT - offset;

	/* Copy data block */
	for (SampleCount_t i = offset; i < count; ++i)
		_buffer[i] = value;

	/* Return the "real" count */
	return count;
}

void PcmPlaybackOscillator::reset() {
	_index = 0;
	_limit = PCM_SAMPLES_COUNT;
	for (SampleCount_t i = 0; i < PCM_SAMPLES_COUNT; ++i)
		_buffer[i] = 0;
}

void PcmPlaybackOscillator::setLogicalBufferSize(SampleCount_t size) {
	_limit = size;
}

void PcmPlaybackOscillator::restartCycle() {
	_index = 0;
}

Sample_t PcmPlaybackOscillator::getSample() {

	/* get the current sample */
	Sample_t sample = _buffer[_index];

	/* Increment (and loop) the buffer index */
	if (++_index == _limit)
		_index = 0;

	/* Return the sample */
	return sample;
}

}
