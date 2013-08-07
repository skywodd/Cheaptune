/* Dependencies */
#include <stdint.h>
#include "Channel.h"
#include "AmplitudeModulator.h"

namespace CheapTune {

Channel::Channel(uint8_t amplitude) :
		_oscillator(), _envelope(), _amplitude(amplitude) {
}

void Channel::setAmplitude(uint8_t amplitude) {
	_amplitude = amplitude;
}

int8_t Channel::getSample() {

	/* Get a sample from the oscillator and the envelope */
	int8_t sample = _oscillator.getSample();
	uint8_t envelope = _envelope.getSample();

	/* Modulate the amplitude of the oscillator's sample using the envelope's sample */
	sample = AmplitudeModulator::compute(sample, envelope);

	/* Apply the channel volume */
	return AmplitudeModulator::compute(sample, _amplitude);
}

void Channel::reset() {
	_oscillator.reset();
	_envelope.reset();
	_amplitude = 255;
}

Oscillator& Channel::oscillator() {
	return _oscillator;
}

Envelope& Channel::envelope() {
	return _envelope;
}

}
