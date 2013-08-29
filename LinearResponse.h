/**
 * @brief Envelope response - linear response
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
#ifndef LINEARRESPONSE_H
#define LINEARRESPONSE_H

/* Dependencies */
#include "Response.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Linear envelope response class
 */
class LinearResponse: public CheapTune::Response {
public:

	Amplitude_t getResponse(WavetableIndex_t t, WavetableIndex_t T,
				Amplitude_t MIN, Amplitude_t MAX);

};

}

#endif /* LINEARRESPONSE_H */
