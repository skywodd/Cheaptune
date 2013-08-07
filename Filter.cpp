/* Dependencies */
#include <stdint.h>
#include "Filter.h"
#include "config.h"
#include "Mixer.h"

namespace CheapTune {

Filter::Filter(FilterMode_t mode, float coeffA, float coeffB) :
		_mode(mode), _oldRaw(0), _oldProcessed(0), _coeffLow(coeffA), _coeffHigh(
				coeffB) {
}

void Filter::setMode(FilterMode_t mode) {
	_mode = mode;
}

void Filter::setCoeffLow(float coeffLow) {
	_coeffLow = coeffLow;
}

void Filter::setCoeffHigh(float coeffHigh) {
	_coeffHigh = coeffHigh;
}

float Filter::computeLowPass(int8_t sample, float alpha) {
	return _oldProcessed + alpha * (sample - _oldProcessed);
}

float Filter::computeHighPass(int8_t sample, float alpha) {
	return alpha * (_oldProcessed + sample - _oldRaw);
}

int8_t Filter::computeSample(int8_t sample) {

	/* Output filter sample */
	int8_t output;

	/* Switch according filter mode */
	switch (_mode) {
	case FILTER_PASSTHROUGH:
		return sample;
		break;

	case FILTER_LOWPASS:
		output = (int8_t) computeLowPass(sample, _coeffLow);
		break;

	case FILTER_HIGHPASS:
		output = (int8_t) computeHighPass(sample, _coeffHigh);
		break;

	case FILTER_BANDPASS:
		output = (int8_t) computeLowPass(sample, _coeffLow);
		output = Mixer::mixTwoSamples(output,
				(int8_t) computeHighPass(sample, _coeffHigh));
		break;

	case FILTER_NOTCH:
		output = (int8_t) computeLowPass(sample, _coeffLow);
		output = (int8_t) computeHighPass(output, _coeffHigh);
		break;
	}

	/* Store raw sample and processed sample */
	_oldRaw = sample;
	_oldProcessed = output;

	/* Return the sample */
	return output;
}

void Filter::reset() {
	_mode = FILTER_PASSTHROUGH;
	_oldRaw = 0;
	_oldProcessed = 0;
	_coeffLow = 0;
	_coeffHigh = 0;
}

float Filter::computeFrequencyLowPass(uint16_t frequency) {
	float RC = 1.0 / (frequency * 2 * 3.14);
	float dt = 1.0 / SAMPLE_RATE;
	return dt / (RC + dt);
}

float Filter::computeFrequencyHighPass(uint16_t frequency) {
	float RC = 1.0 / (frequency * 2 * 3.14);
	float dt = 1.0 / SAMPLE_RATE;
	return RC / (RC + dt);
}

}
