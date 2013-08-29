/* Dependencies */
#include "Response.h"
#include "AdsrEnvelope.h"

namespace CheapTune {

AdsrEnvelope::AdsrEnvelope(Response* response, AdsrTiming_t adsr) :
		_adsr(adsr), _state(ENV_ENDED), _response(response), _timeTick(0), _currentTick(
				0) {
}

void AdsrEnvelope::setResponse(Response* response) {
	_response = response;
}

void AdsrEnvelope::setAdsrTimings(AdsrTiming_t adsr) {
	_adsr = adsr;
}

void AdsrEnvelope::setState(EnvelopeState_t state) {

	/* Store the new state and reset the tick counter */
	_state = state;
	_currentTick = 0;

	/* Switch according the new state */
	switch (state) {
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

void AdsrEnvelope::noteOn() {
	setState(ENV_ATTACK);
}

void AdsrEnvelope::noteOff() {
	if (_state != ENV_ENDED) /* Avoid glitch */
		setState(ENV_RELEASE);
}

uint8_t AdsrEnvelope::getSample() {

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
			sample = _response->getResponse(_currentTick, _timeTick, 0, 255);
			break;

		case ENV_DECAY:
			sample = 255
					- _response->getResponse(_currentTick, _timeTick, 0,
							_adsr.sustain_level);
			break;

		case ENV_SUSTAIN:
			sample = _adsr.sustain_level;
			break;

		case ENV_RELEASE:
			sample = _adsr.sustain_level
					- _response->getResponse(_currentTick, _timeTick, 0,
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

void AdsrEnvelope::reset() {
	_adsr.attack_time = 0;
	_adsr.decay_time = 0;
	_adsr.sustain_level = 0;
	_adsr.release_time = 0;
	_state = ENV_ENDED;
	_timeTick = 0;
	_currentTick = 0;
}

}
