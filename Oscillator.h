/**
 * @brief High level waveform generation routine
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
#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

/* Dependencies */
#include "Waveform.h"

/** CheapTune namespace */
namespace CheapTune {

/** Forward declaration of Channel class */
class Channel;

/**
 * High level waveform generation class
 * (based on Digital Direct Synthesis algorithm)
 */
class Oscillator {
protected:
	/** Waveform generator */
	Waveform _waveform;

	/** Tuning word for DDS */
	uint8_t _tuningWord;

	/** Phase accumulator for DDS */
	uint8_t _phaseAccumulator;

	/**	Sync flag */
	uint8_t _syncFlag;

	/**
	 * Get a sample from the oscillator
	 *
	 * @return The generated sample
	 */
	int8_t getSample();

public:
	/**
	 * Instantiate a new oscillator
	 *
	 * @param frequency The frequency of the oscillator
	 */
	Oscillator(uint16_t frequency = 0);

	/**
	 * Set the frequency of the oscillator
	 *
	 * @param frequency The new frequency of the oscillator
	 */
	void setFrequency(uint16_t frequency);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/**
	 * Get the sync flag (set if the waveform cycle is done)
	 *
	 * @return True if the current waveform cycle is done
	 */
	uint8_t isCycleFinished() const;

	/**
	 * Synchronize the oscillator (restart the waveform cycle)
	 */
	void restartCycle();

	/**
	 * Get a reference to the waveform generator
	 *
	 * @return A reference to the waveform generator of this oscillator
	 */
	Waveform& waveform();

	/** Channel class can access to protected members */
	friend Channel;

};

}

#endif	/* OSCILLATOR_H */

