/**
 * @brief Envelope response - base class
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
#ifndef RESPONSE_H
#define RESPONSE_H

/* Dependencies */
#include "defines.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Base class for envelope response
 */
class Response {
public:
	/**
	 * Default destructor
	 */
	virtual ~Response();

	/**
	 * Get the response sample
	 *
	 * @param t Current time tick
	 * @param T Target time tick
	 * @param MIN Lower amplitude limit
	 * @param MAX Higher amplitude limit
	 * @return The amplitude response sample
	 */
	virtual Amplitude_t getResponse(WavetableIndex_t t, WavetableIndex_t T,
			Amplitude_t MIN, Amplitude_t MAX) = 0;

};

}

#endif /* RESPONSE_H */
