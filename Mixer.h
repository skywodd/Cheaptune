/**
 * @brief Mixer class
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
#ifndef MIXER_H
#define	MIXER_H

/* Dependencies */
#include "Channel.h"
//#include "Filter.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * Mixer class
 */
class Mixer {
protected:
	/** Channels instances */
	Channel _channels[CHANNELS_COUNT];

	/*/* Filter instance */
	//Filter _filter;

	/** Global amplitude */
	Amplitude_t _globalAmplitude;

public:
	/**
	 * Instantiate a new mixer
	 *
	 * @param globalAmplitude The global amplitude of the mixer
	 */
	Mixer(Amplitude_t globalAmplitude = 255);

	/**
	 * Set the global amplitude of the mixer
	 *
	 * @param globalAmplitude The new global amplitude of the mixer
	 */
	void setGlobalAmplitude(Amplitude_t globalAmplitude);

	/**
	 * Get a sample from all channels, mix them, pass through the filter and return it !
	 *
	 * @return The final output sample
	 */
	Sample_t getSample();

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/**
	 * Get a reference to the specified channel
	 *
	 * @param index The channel index to access
	 * @return A reference to the specified channel
	 */
	Channel& channel(unsigned char index);

	/*/*
	 * Get a reference to the filter instance of the mixer
	 *
	 * @return A reference to the filter instance of the mixer
	 */
	//Filter& filter();

	/**
	 * Mix two samples together
	 *
	 * @param A The first sample
	 * @param B The second sample
	 * @return The two samples mixed together
	 */
	static Sample_t mixTwoSamples(Sample_t A, Sample_t B);

};

}

#endif	/* MIXER_H */

