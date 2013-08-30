/**
 * @brief High level waveform generation routine - PCM playback oscillator
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
#ifndef PCMPLAYBACKOSCILLATOR_H
#define PCMPLAYBACKOSCILLATOR_H

/* Dependencies */
#include "Oscillator.h"

/** CheapTune namespace */
namespace CheapTune {

/**
 * PCM playback oscillator class
 */
class PcmPlaybackOscillator: public CheapTune::Oscillator {
protected:
	/** Audio buffer  */
	Sample_t _buffer[PCM_SAMPLES_COUNT];

	/** Audio buffer index */
	SampleCount_t _index;

	/** Audio buffer logical limit */
	SampleCount_t _limit;

public:

	/**
	 * Default constructor
	 */
	PcmPlaybackOscillator();

	/**
	 * Write some data to the audio buffer
	 *
	 * @param src Source data buffer
	 * @param count Number of sample cell to copy
	 * @return The number of buffer cell written
	 */
	SampleCount_t writeBufferData(Sample_t* src, SampleCount_t count =
			PCM_SAMPLES_COUNT, SampleCount_t offset = 0);

	/**
	 * Fill the audio buffer with the same value
	 *
	 * @param value Value to fill the buffer with
	 * @param count Number of buffer cell to fill
	 * @return The number of buffer cell written
	 */
	SampleCount_t fillBuffer(Sample_t value, SampleCount_t count =
			PCM_SAMPLES_COUNT, SampleCount_t offset = 0);

	/**
	 * Set the logical size of the audio buffer
	 *
	 * @param size The new logical size
	 */
	void setLogicalBufferSize(SampleCount_t size);

	/**
	 * Synchronize the oscillator (restart the sample cycle)
	 */
	void restartCycle();

	void reset();

	Sample_t getSample();
};

}

#endif /* PCMPLAYBACKOSCILLATOR_H */
