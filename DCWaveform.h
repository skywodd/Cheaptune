/**
 * @brief Waveform generation - DC waveform
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
#ifndef DCWAVEFORM_H
#define DCWAVEFORM_H

/* Dependencies */
#include "Waveform.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * DC waveform generation class
 */
class DCWaveform: public CheapTune::Waveform {
protected:
	/** DC signal level */
	Sample_t _level;

public:
	/**
	 * Instantiate a new DCWaveform generator
	 *
	 * @param level DC signal level
	 */
	DCWaveform(Sample_t level = 0);

	/**
	 * Set the DC signal level
	 *
	 * @param level The new DC signal level
	 */
	void setDcLevel(Sample_t level);

	void reset();

	Sample_t getSample(WavetableIndex_t index);

};

}

#endif /* DCWAVEFORM_H */
