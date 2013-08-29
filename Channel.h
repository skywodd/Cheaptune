/**
 * @brief Channel wrapper
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
#ifndef CHANNEL_H
#define	CHANNEL_H

/* Dependencies */
#include "defines.h"

/* CheapTune namespace */
namespace CheapTune {

/** Forward declaration of the Oscillator and Envelope class */
class Oscillator;
class Envelope;

/**
 * Channel instance class
 */
class Channel {
protected:
	/** Oscillator instance */
	Oscillator* _oscillator;

	/** Envelope instance */
	Envelope* _envelope;

	/** Amplitude of the channel */
	Amplitude_t _amplitude;

public:
	/**
	 * Instantiate a new channel
	 *
	 * @param oscillator Oscillator instance to use
	 * @param envelope Envelope instance to use
	 * @param amplitude The amplitude of this channel
	 */
	Channel(Oscillator* oscillator = 0, Envelope* envelope = 0, Amplitude_t amplitude = 255);

	/**
	 * Set the oscillator instance
	 *
	 * @param oscillator The new oscillator instance to use
	 */
	void setOscillator(Oscillator* oscillator);

	/**
	 * Set the envelope instance
	 *
	 * @param envelope The new envelope instance to use
	 */
	void setEnvelope(Envelope* envelope);

	/**
	 * Set the amplitude of this channel
	 *
	 * @param amplitude The new amplitude of this channel
	 */
	void setAmplitude(Amplitude_t amplitude);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/**
	 * Compute and return a sample for this channel
	 *
	 * @return The computed sample
	 */
	Sample_t getSample();

	/**
	 * Get a pointer to the oscillator instance of this channel
	 *
	 * @return A pointer to the oscillator instance of this channel
	 */
	Oscillator* oscillator();

	/**
	 * Get a pointer to the envelope instance of this channel
	 *
	 * @return A pointer to the envelope instance of this channel
	 */
	Envelope* envelope();

};

}

#endif	/* CHANNEL_H */

