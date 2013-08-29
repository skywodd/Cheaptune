/**
 * @brief Amplitude modulation routines
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
#ifndef AMPLITUDEMODULATOR_H
#define	AMPLITUDEMODULATOR_H

/* Dependencies */
#include "defines.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Amplitude modulation routines bundle
 */
class AmplitudeModulator {
public:

	/**
	 * Modulate the amplitude of a sample
	 *
	 * @param sample The sample to modulate
	 * @param amplitude The amplitude to apply on the sample
	 * @return The amplitude modulated sample
	 */
	static Sample_t compute(Sample_t sample, Amplitude_t amplitude) {
		return ((int32_t) sample) * amplitude / 255;
	}

	/**
	 * Turn a percent based volume into an absolute amplitude value
	 *
	 * @param percent The volume in percent
	 * @return The computed amplitude value
	 */
	static Amplitude_t percentToAmplitude(uint8_t percent) {
		return ((uint16_t) percent) * 255 / 100;
	}

};

}

#endif	/* AMPLITUDEMODULATOR_H */

