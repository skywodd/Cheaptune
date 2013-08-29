/**
 * @brief Waveform generation - Square waveform
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
#ifndef SQUAREWAVEFORM_H
#define SQUAREWAVEFORM_H

/* Dependencies */
#include "Waveform.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Square waveform generation class
 */
class SquareWaveform: public CheapTune::Waveform {
protected:
	/** PWM duty */
	uint8_t _duty;

public:

	/**
	 * Instantiate a new SquareWaveform generator
	 *
	 * @param duty The PWM duty
	 */
	SquareWaveform(uint8_t duty = 127);

	/**
	 * Set the PWM duty
	 *
	 * @param duty The new PWM duty
	 */
	void setDuty(uint8_t duty);

	void reset();

	Sample_t getSample(WavetableIndex_t index);

};

}

#endif /* SQUAREWAVEFORM_H */
