/**
 * @brief High level waveform generation routine - base API
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
#ifndef OSCILLATOR_H_
#define OSCILLATOR_H_

/* Dependencies */
#include "defines.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * High level waveform generation routine - base API
 */
class Oscillator {
public:
	/**
	 * Default destructor
	 */
	virtual ~Oscillator();

	/**
	 * Reset all parameters to their default values
	 */
	virtual void reset();

	/**
	 * Get a sample from the oscillator
	 *
	 * @return The generated sample
	 */
	virtual Sample_t getSample() = 0;

};

}

#endif /* OSCILLATOR_H_ */
