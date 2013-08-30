/**
 * @brief Waveform generation - common base API
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
#ifndef WAVEFORM_H
#define	WAVEFORM_H

/* Dependencies */
#include "defines.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Low level waveform generation base class
 */
class Waveform {
public:
	/**
	 * Virtual destructor
	 */
	virtual ~Waveform();

	/**
	 * Reset all parameters to their default values
	 */
	virtual void reset();

	/**
	 * Compute and return one sample from the waveform generator
	 *
	 * @param index The sample index in the waveform generator table
	 * @return The computed sample for the given index
	 */
	virtual Sample_t getSample(WavetableIndex_t index) = 0;

};

}

#endif	/* WAVEFORM_H */

