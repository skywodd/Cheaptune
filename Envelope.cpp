/* Dependencies */
#include <stdint.h>
#include <cmath>
#include "Envelope.h"

namespace CheapTune {

Envelope::Envelope(EnvelopeState_t state, EnvelopeResponse_t response) :
		_adsr(), _state(state), _response(response), _timeTick(0), _currentTick(
				0) {
}

Envelope::Adsr& Envelope::adsr() {
	return _adsr;
}

void Envelope::setResponse(EnvelopeResponse_t response) {
	_response = response;
}

void Envelope::setState(EnvelopeState_t state) {

	/* Store the new state and reset the tick counter */
	_state = state;
	_currentTick = 0;

	/* Switch according the new state */
	switch (state) {
	case ENV_DISABLE:
	case ENV_SUSTAIN:
	case ENV_ENDED:
		_timeTick = 0xFFFF; // Avoid the getSample() routine to do useless stuff
		break;

	case ENV_ATTACK:
		_timeTick = _adsr.attack_time;
		break;

	case ENV_DECAY:
		_timeTick = _adsr.decay_time;
		break;

	case ENV_RELEASE:
		_timeTick = _adsr.release_time;
		break;
	}
}

uint8_t Envelope::linearResponse(uint16_t t, uint16_t T, uint8_t MIN,
		uint8_t MAX) {
	return ((uint16_t) MAX * t) / T + MIN; // Simple y = ax + b equation
}

uint8_t Envelope::exponentialResponse(uint16_t t, uint16_t T, uint8_t MIN,
		uint8_t MAX) {
	return MIN + (MAX - MIN) * (1 - exp(-5.0 * t / T)); // Capacitor charge equation
}

uint8_t Envelope::getSample() {

	/* Check if the envelope is disable */
	if (_state == ENV_DISABLE)
		return 255;

	/* Check if the envelope has ended */
	if (_state == ENV_ENDED)
		return 0;

	/* Check if the current state has finish */
	if (_currentTick == _timeTick) {

		/* Reset the tick counter */
		_currentTick = 0;

		/* Switch according the current state */
		switch (_state) {
		case ENV_ATTACK:
			/* Test if the decay time is null */
			if (_adsr.decay_time) {

				/* Upgrade the envelope state to the DECAY phase */
				_state = ENV_DECAY;
				_timeTick = _adsr.decay_time;

			} else { /* No decay phase */

				/* Upgrade the envelope state to the SUSTAIN phase */
				_state = ENV_SUSTAIN;
				_timeTick = 0xFFFF;
			}
			break;

		case ENV_DECAY:
			/* Upgrade the envelope state to the SUSTAIN phase */
			_state = ENV_SUSTAIN;
			_timeTick = 0xFFFF;
			break;

		case ENV_SUSTAIN:
			/* Nothing to do, this phase is stable */
			/* Only setState(ENV_RELEASE) can make the state change */
			break;

		case ENV_RELEASE:
			/* Upgrade the envelope state to the ENDED phase */
			_state = ENV_ENDED;
			return 0;

		default:
			break;
		}
	}

	/* At this step the envelope is already upgraded if necessary and not in ENV_DISABLE or ENV_ENDED state */

	{
		/* The generated sample */
		uint8_t sample;

		/* Switch according the current state */
		switch (_state) {
		case ENV_ATTACK:
			if (_response == ENV_LINEAR_RESPONSE)
				sample = linearResponse(_currentTick, _timeTick, 0, 255);
			else
				sample = exponentialResponse(_currentTick, _timeTick, 0, 255);
			break;

		case ENV_DECAY:
			if (_response == ENV_LINEAR_RESPONSE)
				sample = 255
						- linearResponse(_currentTick, _timeTick, 0,
								_adsr.sustain_level);
			else
				sample = 255
						- exponentialResponse(_currentTick, _timeTick, 0,
								_adsr.sustain_level);
			break;

		case ENV_SUSTAIN:
			sample = _adsr.sustain_level;
			break;

		case ENV_RELEASE:
			if (_response == ENV_LINEAR_RESPONSE)
				sample = _adsr.sustain_level
						- linearResponse(_currentTick, _timeTick, 0,
								_adsr.sustain_level);
			else
				sample = _adsr.sustain_level
						- exponentialResponse(_currentTick, _timeTick, 0,
								_adsr.sustain_level);
			break;

		default:
			break;
		}

		/* Increment the tick counter */
		++_currentTick;

		/* Return the generated sample */
		return sample;
	}
}

void Envelope::reset() {
	_adsr.attack_time = 0;
	_adsr.decay_time = 0;
	_adsr.sustain_level = 0;
	_adsr.release_time = 0;
	_state = ENV_DISABLE;
	_timeTick = 0;
	_currentTick = 0;
}

}
