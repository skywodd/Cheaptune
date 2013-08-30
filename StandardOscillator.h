/**
 * @brief High level waveform generation routine - standard version
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
#ifndef STANDARDOSCILLATOR_H
#define	STANDARDOSCILLATOR_H

/* Dependencies */
#include "Oscillator.h"

/** CheapTune namespace */
namespace CheapTune {

/* Forward declaration of Waveform class */
class Waveform;

/**
 * High level waveform generation class - standard version
 * (based on Digital Direct Synthesis algorithm)
 */
class StandardOscillator: public CheapTune::Oscillator {
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
	StandardOscillator(Waveform* waveform, Frequency_t frequency = 0);

	/**
	 * Set the frequency of the oscillator
	 *
	 * @param frequency The new frequency of the oscillator
	 */
	void setFrequency(Frequency_t frequency);

	/**
	 * Set the waveform generator instance
	 *
	 * @param waveform A pointer to the new waveform generator
	 */
	void setWaveform(Waveform* waveform);

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
	void restartCycle(WavetableIndex_t index = 0);

	/**
	 * Get a pointer to the waveform generator
	 *
	 * @return A pointer to the waveform generator of this oscillator
	 */
	Waveform* waveform();

	void reset();

	Sample_t getSample();

};

}

#endif	/* STANDARDOSCILLATOR_H */

