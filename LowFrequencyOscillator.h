/**
 * @brief High level waveform generation routine - low frequency variant
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
#ifndef LOWFREQUENCYOSCILLATOR_H
#define LOWFREQUENCYOSCILLATOR_H

/* Dependencies */
#include "StandardOscillator.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * High level waveform generation class - low frequency variant
 */
class LowFrequencyOscillator: public CheapTune::StandardOscillator {
protected:
	/** The generated and cached sample */
	Sample_t _sample;

	/** Prescaler divisor */
	Prescaler_t _prescaler;

	/** Prescaler counter */
	Prescaler_t _counter;

public:
	/**
	 * Instantiate a new low frequency oscillator
	 *
	 * @param waveform The waveform generator instance to use
	 * @param prescaler The sample rate frequency divisor to use
	 * @param frequency The frequency of the oscillator
	 */
	LowFrequencyOscillator(Waveform* waveform, Prescaler_t prescaler = 1, Frequency_t frequency = 0);

	/**
	 * Set the sample rate frequency divisor
	 *
	 * @param prescaler The new sample rate frequency divisor to use
	 */
	void setPrescaler(Prescaler_t prescaler);

	void setFrequency(Frequency_t frequency);

	void restartCycle(WavetableIndex_t index = 0);

	Sample_t getSample();

	void reset();

};

}

#endif /* LOWFREQUENCYOSCILLATOR_H */
