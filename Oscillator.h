/**
 * @brief High level waveform generation routine
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
#ifndef OSCILLATOR_H
#define	OSCILLATOR_H

/* Dependencies */
#include "defines.h"

/** CheapTune namespace */
namespace CheapTune {

/* Forward declaration of Waveform class */
class Waveform;

/**
 * High level waveform generation class
 * (based on Digital Direct Synthesis algorithm)
 */
class Oscillator {
protected:
	/** Waveform generator instance */
	Waveform* _waveform;

	/** Tuning word for DDS */
	WavetableIndex_t _tuningWord;

	/** Phase accumulator for DDS */
	WavetableIndex_t _phaseAccumulator;

	/**	Sync flag */
	bool _syncFlag;

public:
	/**
	 * Instantiate a new oscillator
	 *
	 * @param waveform The waveform generator instance to use
	 * @param frequency The frequency of the oscillator
	 */
	Oscillator(Waveform* waveform, Frequency_t frequency = 0);

	/**
	 * Default destructor
	 */
	virtual ~Oscillator();

	/**
	 * Set the frequency of the oscillator
	 *
	 * @param frequency The new frequency of the oscillator
	 */
	virtual void setFrequency(Frequency_t frequency);

	/**
	 * Set the waveform generator instance
	 *
	 * @param waveform A pointer to the new waveform generator
	 */
	void setWaveform(Waveform* waveform);

	/**
	 * Reset all parameters to their default values
	 */
	virtual void reset();

	/**
	 * Get the sync flag (set if the waveform cycle is done)
	 *
	 * @return True if the current waveform cycle is done
	 */
	bool isCycleFinished() const;

	/**
	 * Synchronize the oscillator (restart the waveform cycle)
	 *
	 * @param index Optional index for re-sync
	 */
	virtual void restartCycle(WavetableIndex_t index = 0);

	/**
	 * Get a sample from the oscillator
	 *
	 * @return The generated sample
	 */
	virtual Sample_t getSample();

	/**
	 * Get a pointer to the waveform generator
	 *
	 * @return A pointer to the waveform generator of this oscillator
	 */
	Waveform* waveform();

};

}

#endif	/* OSCILLATOR_H */

