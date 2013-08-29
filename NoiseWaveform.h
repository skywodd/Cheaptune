/**
 * @brief Waveform generation - Noise waveform
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
#ifndef NOISEWAVEFORM_H
#define NOISEWAVEFORM_H

/* Dependencies */
#include "Waveform.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Noise waveform generation class
 */
class NoiseWaveform: public CheapTune::Waveform {
protected:
	/** @see http://en.wikipedia.org/wiki/Linear_feedback_shift_register#Galois_LFSRs */
	uint32_t _lfsr;

public:

	/**
	 * Instantiate a new NoiseWaveform generator
	 *
	 * @param seed Seed for noise generator
	 */
	NoiseWaveform(uint32_t seed = 0xACE1u);

	/**
	 * Re-seed the noise generator
	 *
	 * @param seed The new seed for noise generator
	 */
	void reSeedNoise(uint32_t seed);

	Sample_t getSample(WavetableIndex_t index);

};

}

#endif /* NOISEWAVEFORM_H */
