/**
 * @brief Digital filter implementation
 * @author SkyWodd
 * @version 1.0
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
#ifndef FILTER_H
#define	FILTER_H

/** CheapTune namespace */
namespace CheapTune {

/** Forward declaration of the Mixer class */
class Mixer;

/**
 * Digital filter implementation class
 */
class Filter {
public:
	/**
	 * Filter modes enumeration
	 */
	typedef enum {
		FILTER_PASSTHROUGH, //!< No filter, pass-through
		FILTER_LOWPASS,     //!< Low pass filter
		FILTER_HIGHPASS,    //!< High pass filter
		FILTER_BANDPASS,    //!< Band pass filter
		FILTER_NOTCH        //!< Notch filter
	} FilterMode_t;

protected:
	/** Filter mode */
	FilterMode_t _mode;

	/** Old raw sample */
	uint8_t _oldRaw;

	/** Old processed sample */
	uint8_t _oldProcessed;

	/** High and low frequency coefficient */
	float _coeffLow, _coeffHigh;

	/**
	 * Apply the selected filter on the given sample
	 *
	 * @param sample The sample to process
	 * @return The filter result sample
	 */
	int8_t computeSample(int8_t sample);

	/**
	 * Apply a low pass filter
	 *
	 * @param sample Input sample
	 * @param alpha Input coefficient
	 * @return Output sample
	 */
	float computeLowPass(int8_t sample, float alpha);

	/**
	 * Apply a high pass filter
	 *
	 * @param sample Input sample
	 * @param alpha Input coefficient
	 * @return Output sample
	 */
	float computeHighPass(int8_t sample, float alpha);

public:
	/**
	 * Instantiate a new filter
	 *
	 * @param mode The filter mode to use
	 * @param coeffA The low frequency coefficient
	 * @param coeffB The high frequency coefficient
	 */
	Filter(FilterMode_t mode = FILTER_PASSTHROUGH, float coeffLow = 0,
			float coeffHigh = 0);

	/**
	 * Set the filter mode
	 *
	 * @param mode The new filter mode
	 */
	void setMode(FilterMode_t mode);

	/**
	 * Set the low frequency coefficient
	 * @param coeffLow The new low frequency coefficient
	 */
	void setCoeffLow(float coeffLow);

	/**
	 * Set the high frequency coefficient
	 *
	 * @param coeffHigh The new high frequency coefficient
	 */
	void setCoeffHigh(float coeffHigh);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/**
	 * Turn a frequency into a low-pass filter coefficient
	 *
	 * @param frequency The frequency to be converted
	 * @return The resulting coefficient
	 */
	static float computeFrequencyLowPass(uint16_t frequency);

	/**
	 * Turn a frequency into a high-pass filter coefficient
	 *
	 * @param frequency The frequency to be converted
	 * @return The resulting coefficient
	 */
	static float computeFrequencyHighPass(uint16_t frequency);

	/** Mixer class can access to protected members */
	friend Mixer;

};

}

#endif	/* FILTER_H */

