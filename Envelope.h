/**
 * @brief Envelope generator (ADSR)
 * @author SkyWodd
 * @version 1.0
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
#ifndef ENVELOPE_H
#define	ENVELOPE_H

/** CheapTune namespace */
namespace CheapTune {

/* Forward declaration of the Channel class */
class Channel;

/**
 * ADSR envelope generator
 */
class Envelope {
public:

	/**
	 * The ADSR data model structure
	 */
	struct Adsr {
		uint16_t attack_time; /*!< Attack time (in tick) */
		uint16_t decay_time; /*!< Decay time (in tick) */
		uint8_t sustain_level; /*!< Sustain level (amplitude) */
		uint16_t release_time; /*!< Release time (in tick) */
	};

	/**
	 * Envelope states enumeration
	 */
	typedef enum {
		ENV_DISABLE, //!< Envelope disable
		ENV_ATTACK,  //!< Attack phase
		ENV_DECAY,   //!< Decay phase
		ENV_SUSTAIN, //!< Sustain phase
		ENV_RELEASE, //!< Release phase
		ENV_ENDED    //!< End of envelope
	} EnvelopeState_t;

	/**
	 * Envelope responses enumeration
	 */
	typedef enum {
		ENV_LINEAR_RESPONSE,     //!< Linear response
		ENV_EXPONENTIAL_RESPONSE //!< Exponential response
	} EnvelopeResponse_t;

protected:
	/** ADSR envelope data */
	Adsr _adsr;

	/** Envelope state */
	EnvelopeState_t _state;

	/** Envelope response mode */
	EnvelopeResponse_t _response;

	/** Time tick before state upgrade */
	uint16_t _timeTick;

	/** Current time tick counter */
	uint16_t _currentTick;

	/**
	 * Compute an amplitude sample from the ADSR envelope
	 *
	 * @return The computed amplitude sample
	 */
	uint8_t getSample();

	/**
	 * Simple linear response formula
	 *
	 * @param t Time value between 0 and T
	 * @param T Max time value
	 * @param MIN Min amplitude value
	 * @param MAX Max amplitude value
	 * @return The linear response for the given time value
	 */
	static uint8_t linearResponse(uint16_t t, uint16_t T, uint8_t MIN,
			uint8_t MAX);

	/**
	 * Advanced exponential response formula
	 *
	 * @param t Time value between 0 and T
	 * @param T Max time value
	 * @param MIN Min amplitude value
	 * @param MAX Max amplitude value
	 * @return The linear response for the given time value
	 */
	static uint8_t exponentialResponse(uint16_t t, uint16_t T, uint8_t MIN,
			uint8_t MAX);

public:
	/**
	 * Instantiate a new ADSR envelope
	 *
	 * @param state The envelope state
	 * @param response The response mode
	 */
	Envelope(EnvelopeState_t state = ENV_DISABLE, EnvelopeResponse_t response =
			ENV_LINEAR_RESPONSE);

	/**
	 * Get a reference to the ADSR data model of this envelope
	 *
	 * return A reference to the ADSR data model of this envelope
	 */
	Adsr& adsr();

	/**
	 * Set the state of the envelope
	 *
	 * @param state The new state of the envelope
	 */
	void setState(EnvelopeState_t state);

	/**
	 * Set the response of the envelope
	 *
	 * @param response The new response of the envelope
	 */
	void setResponse(EnvelopeResponse_t response);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/** Channel class can access to protected members */
	friend Channel;
};

}

#endif	/* ENVELOPE_H */

