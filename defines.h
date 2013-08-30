/**
 * @brief Types and defines declaration file
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
#ifndef DEFINES_H
#define	DEFINES_H

/* Dependencies */
#include <stdint.h>

/** CheapTune namespace */
namespace CheapTune {

///TODO Move this defines to makefile
#define SAMPLE_RATE 8000
#define CHANNELS_COUNT 4
#define PCM_SAMPLES_COUNT 8192
#define WAVETABLE_BITSIZE 12
#define WAVETABLE_EXP_BITSIZE 12

/* ------ */

/** Compatibility helper for flash based devices */
#define PROGMEM

/** Compatibility helper for flash based devices */
#define PROGMEM_READBYTE(buffer, index) (buffer[index])

/** Compatibility helper for flash based devices */
#define PROGMEM_READWORD(buffer, index) (buffer[index])


/** Frequency (in hertz) type */
typedef uint16_t Frequency_t;


/** Prescaler type */
typedef uint8_t Prescaler_t;


/** Amplitude type */
typedef uint8_t Amplitude_t;

/** Amplitude type (bis) */
typedef uint16_t BigAmplitude_t;


/** Audio sample type */
typedef int16_t Sample_t;

/** Audio sample count type */
typedef uint16_t SampleCount_t;

/** Max sample value */
#define SAMPLE_VMAX (32767)

/** Min sample value */
#define SAMPLE_VMIN (-(SAMPLE_VMAX))


/** Wave table index type */
typedef uint16_t WavetableIndex_t;

/** Wave table samples count */
#define WAVETABLE_SAMPLES_COUNT (1 << (WAVETABLE_BITSIZE))

/** Wave table index bit mask */
#define WAVETABLE_INDEX_BITMASK ((WAVETABLE_SAMPLES_COUNT) - 1)

/** Exponential wave table samples count */
#define WAVETABLE_EXP_SAMPLES_COUNT (1 << (WAVETABLE_EXP_BITSIZE))

/** Exponential wave table index bit mask */
#define WAVETABLE_EXP_INDEX_BITMASK ((WAVETABLE_EXP_SAMPLES_COUNT) - 1)

}

#endif	/* DEFINES_H */

