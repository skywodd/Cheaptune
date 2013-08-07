/**
 * @brief Waveform generation routines
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
#ifndef WAVEFORM_H
#define	WAVEFORM_H

/** CheapTune namespace */
namespace CheapTune {

/** Forward declaration of Oscillator class */
class Oscillator;

/**
 * Low level waveform generation class
 */
class Waveform {
private:
	/** Sinusoids values (256 points, 8 bits signed) */
	static const int8_t _sinusoids[];

public:
	/**
	 * Waveform types enumeration
	 */
	typedef enum {
		WAVE_NONE,     //!< No signal
		WAVE_DC,       //!< Constant signal
		WAVE_SINUS,    //!< Sinus wave
		WAVE_TRIANGLE, //!< Triangle wave
		WAVE_SQUARE,   //!< Square wave
		WAVE_SAWTOOTH, //!< Sawtooth wave
		WAVE_NOISE     //!< Noise
	} WaveformType_t;

protected:
	/** Waveform type */
	WaveformType_t _waveform;

	/** Duty value */
	uint8_t _duty;

	/** Noise seed */
	uint16_t _noise;

	/**
	 * Compute and return one sample from the waveform generator
	 *
	 * @param index The sample index in the waveform generator table
	 * @return The computed sample for the given index
	 */
	int8_t getSample(uint8_t index);

public:
	/**
	 * Instantiate a new Waveform generator
	 *
	 * @param waveform Waveform type to generate
	 * @param duty Duty value to use (if necessary)
	 */
	Waveform(WaveformType_t waveform = WAVE_NONE, uint8_t duty = 0);

	/**
	 * Set the duty value
	 *
	 * @param duty The new duty value
	 */
	void setDuty(uint8_t duty);

	/**
	 * Set the waveform type
	 *
	 * @param waveform The new waveform type
	 */
	void setWaveform(WaveformType_t waveform);

	/**
	 * Reset all parameters to their default values
	 */
	void reset();

	/** Oscillator class can access to protected members */
	friend Oscillator;
};

}

#endif	/* WAVEFORM_H */

