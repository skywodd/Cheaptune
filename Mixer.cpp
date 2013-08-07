/* Dependencies */
#include <stdint.h>
#include "Mixer.h"
#include "AmplitudeModulator.h"

namespace CheapTune {

Mixer::Mixer(uint8_t globalAmplitude) :
		_channels(), _filter(), _globalAmplitude(globalAmplitude) {
}

void Mixer::setGlobalAmplitude(uint8_t globalAmplitude) {
	_globalAmplitude = globalAmplitude;
}

int8_t Mixer::mixTwoSamples(int16_t A, int16_t B) {
	int16_t Z;
	if (A < 0 && B < 0)
		Z = (A + B) - ((A * B) / -127);
	else if ((A > 0) & (B > 0))
		Z = (A + B) - ((A * B) / 127);
	else
		Z = A + B;
	return Z;
}

int8_t Mixer::getSample() {

	/* Get the first channel sample */
	int8_t sample = _channels[0].getSample();

	/* Get all other channels samples */
	for (unsigned char i = 1; i < CHANNELS_COUNT; ++i) {

		/* Get channel sample and mix them with the previous sample */
		sample = mixTwoSamples(sample, _channels[i].getSample());
	}

	/* Pass the resulting sample into the filter */
	sample = _filter.computeSample(sample);

	/* Amplitude modulate the sample */
	sample = AmplitudeModulator::compute(sample, _globalAmplitude);

	/* Return the final sample value */
	return sample;
}

void Mixer::reset() {
	for (unsigned char i = 0; i < CHANNELS_COUNT; ++i)
		_channels[i].reset();
	_filter.reset();
	_globalAmplitude = 255;
}

Channel& Mixer::channel(unsigned char index) {
	return _channels[index];
}

Filter& Mixer::filter() {
	return _filter;
}

}
