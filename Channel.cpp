/* Dependencies */
#include "Channel.h"
#include "Oscillator.h"
#include "AmplitudeModulator.h"
#include "Envelope.h"

namespace CheapTune {

Channel::Channel(Oscillator* oscillator, Envelope* envelope, Amplitude_t amplitude) :
		_oscillator(oscillator), _envelope(envelope), _amplitude(amplitude) {
}

void Channel::setOscillator(Oscillator* oscillator) {
	_oscillator = oscillator;
}

void Channel::setEnvelope(Envelope* envelope) {
	_envelope = envelope;
}

void Channel::setAmplitude(Amplitude_t amplitude) {
	_amplitude = amplitude;
}

Sample_t Channel::getSample() {

	/* Get a sample from the oscillator and the envelope */
	Sample_t sample = _oscillator->getSample();
	Amplitude_t envelope = _envelope->getSample();

	/* Modulate the amplitude of the oscillator's sample using the envelope's sample */
	sample = AmplitudeModulator::compute(sample, envelope);

	/* Apply the channel volume */
	return AmplitudeModulator::compute(sample, _amplitude);
}

void Channel::reset() {
	_oscillator->reset();
	_envelope->reset();
	_amplitude = 255;
}

Oscillator* Channel::oscillator() {
	return _oscillator;
}

Envelope* Channel::envelope() {
	return _envelope;
}

}
