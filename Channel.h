/**
 * @brief Channel instance object
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
#ifndef CHANNEL_H
#define	CHANNEL_H

/* Dependencies */
#include "Oscillator.h"
#include "Envelope.h"

/* CheapTune namespace */
namespace CheapTune {

/** Forward declaration of the Mixer class */
class Mixer;

/**
 * Channel instance class
 */
class Channel {
protected:
	/** Oscillator instance of the channel */
	Oscillator _oscillator;

	/** Envelope instance of the channel */
	Envelope _envelope;

	/** Amplitude of the channel */
	uint8_t _amplitude;

	/**
	 * Compute and return a sample for this channel
	 *
	 * @return The computed sample
	 */
	int8_t getSample();

public:
	/**
	 * Instantiate a new channel
	 *
	 * @param amplitude The amplitude of this channel
	 */
	Channel(uint8_t amplitude = 255);

	/**
	 * Set the amplitude of this channel
	 *
	 * @param amplitude The new amplitude of this channel
	 */
	void setAmplitude(uint8_t amplitude);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/**
	 * Get a reference to the oscillator instance of this channel
	 *
	 * @return A reference to the oscillator instance of this channel
	 */
	Oscillator& oscillator();

	/**
	 * Get a reference to the envelope instance of this channel
	 *
	 * @return A reference to the envelope instance of this channel
	 */
	Envelope& envelope();

	/** Mixer class can access to protected members */
	friend Mixer;

};

}

#endif	/* CHANNEL_H */

