/**
 * @brief Envelope generator - ADSR envelope
 * @author SkyWodd
 * @version 2.0
 * @see http://skyduino.wordpress.com/
 *
 * @section licence_sec License
 *  This program is free software: you can redistribute it and/or modify\n
 *  it under the terms of the GNU General Public License as published by\n
 *  the Free Software Foundation, either version 3 of the License, or\n
 *  (at your option) any later version.\n
 * \n
 *  This program is distributed in the hope that it will be useful,\n
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of\n
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n
 *  GNU General Public License for more details.\n
 * \n
 *  You should have received a copy of the GNU General Public License\n
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.\n
 */
#ifndef ADSRENVELOPE_H
#define	ADSRENVELOPE_H

/* Dependencies */
#include "Envelope.h"

/** CheapTune namespace */
namespace CheapTune {

/** Forward declaration of Response class */
class Response;

/**
 * ADSR envelope generator
 */
class AdsrEnvelope: public CheapTune::Envelope {
public:

	/** ADSR timings structure */
	typedef struct {
		uint16_t attack_time; /*!< Attack time (in tick) */
		uint16_t decay_time; /*!< Decay time (in tick) */
		Amplitude_t sustain_level; /*!< Sustain level (amplitude) */
		uint16_t release_time; /*!< Release time (in tick) */
	} AdsrTiming_t;

	/**
	 * Envelope states enumeration
	 */
	typedef enum {
		ENV_ATTACK,  //!< Attack phase
		ENV_DECAY,   //!< Decay phase
		ENV_SUSTAIN, //!< Sustain phase
		ENV_RELEASE, //!< Release phase
		ENV_ENDED    //!< End of envelope
	} EnvelopeState_t;

	/**
	 * Helper function - convert milliseconds to clock tick number
	 *
	 * @param ms Milliseconds value
	 * @return Tick count value
	 */
	static uint16_t msToTick(uint16_t ms) {
		return (uint32_t) ms * SAMPLE_RATE / 1000;
	}

protected:
	/* ADSR envelope timings */
	AdsrTiming_t _adsr;

	/** Envelope state */
	EnvelopeState_t _state;

	/** Envelope response */
	Response* _response;

	/** Time tick before state upgrade */
	uint16_t _timeTick;

	/** Current time tick counter */
	uint16_t _currentTick;

	/**
	 * Set the state of the envelope
	 *
	 * @param state The new state of the envelope
	 */
	void setState(EnvelopeState_t state);

public:
	/**
	 * Instantiate a new ADSR envelope
	 *
	 * @param response The response mode
	 * @param adsr Adsr timings structure
	 */
	AdsrEnvelope(Response* response, AdsrTiming_t adsr);

	/**
	 * Set the response of the envelope
	 *
	 * @param response The new response instance pointer of the envelope
	 */
	void setResponse(Response* response);

	/**
	 * Start note
	 */
	void noteOn();

	/**
	 * Stop note
	 */
	void noteOff();

	/**
	 * Set the ADSR timings
	 *
	 * @param adsr The new ADSR timings structure
	 */
	void setAdsrTimings(AdsrTiming_t adsr);

	void reset();

	Amplitude_t getSample();

};

}

#endif	/* ADSRENVELOPE_H */

