/**
 * @brief Tiny but strong chiptune generator
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

/* Dependencies */
#include <iostream>
#include <cstdio>
#include <stdint.h>

/* Cheaptune runtime */
#include "defines.h"
#include "AmplitudeModulator.h"
#include "StandardOscillator.h"
#include "LowFrequencyOscillator.h"
#include "Channel.h"
#include "Mixer.h"

/* Dependencies - waveforms */
#include "DCWaveform.h"
#include "NoiseWaveform.h"
#include "SawtoothWaveform.h"
#include "SinusWaveform.h"
#include "SquareWaveform.h"
#include "TriangleWaveform.h"

/* Dependencies - ADSR envelope */
#include "AdsrEnvelope.h"
#include "ExponentialResponse.h"
#include "LinearResponse.h"

/** Number of second of sound to be generated */
#define NB_SECONDS_RUN 5

/** Output filename */
#define OUTPUT_FILENAME "output.wav"

/**
 * Wave file header
 */
typedef struct {
	char RIFF[4];           // RIFF Header Magic header
	uint32_t ChunkSize;     // RIFF Chunk Size
	char WAVE[4];           // WAVE Header
	char fmt[4];            // FMT header
	uint32_t Subchunk1Size; // Size of the fmt chunk
	uint16_t AudioFormat; // Audio format 1=PCM,6=mulaw,7=alaw, 257=IBM Mu-Law, 258=IBM A-Law, 259=ADPCM
	uint16_t NumOfChan;     // Number of channels 1=Mono 2=Sterio
	uint32_t SamplesPerSec; // Sampling Frequency in Hz
	uint32_t bytesPerSec;   // bytes per second
	uint16_t blockAlign;    // 2=16-bit mono, 4=16-bit stereo
	uint16_t bitsPerSample; // Number of bits per sample
	char Subchunk2ID[4];    // "data"  string
	uint32_t Subchunk2Size; // Sampled data length
} WavHeader_t;

/**
 * Main function
 *
 * @param argc CLI arguments count
 * @param argv CLI arguments array
 * @return Return code
 */
int main(int argc, char** argv) {

	/* Mixer instance */
	CheapTune::Mixer mixer;

	std::cout << "Cheaptune starting ..." << std::endl;

	/* Mixer setup */
	std::cout << "Mixer setup ..." << std::endl;
	mixer.setGlobalAmplitude(255);

	/* Common setup */
	CheapTune::LinearResponse rl;
	CheapTune::ExponentialResponse re;
	CheapTune::AdsrEnvelope::AdsrTiming_t a;
	a.attack_time = CheapTune::AdsrEnvelope::msToTick(100);
	a.decay_time = CheapTune::AdsrEnvelope::msToTick(50);
	a.sustain_level = 127;
	a.release_time = CheapTune::AdsrEnvelope::msToTick(100);

	/* Channels setup */
	CheapTune::SinusWaveform w2;
	CheapTune::AdsrEnvelope e2(&re, a);
	CheapTune::StandardOscillator o2(&w2, 440);
	mixer.channel(1).setAmplitude(255);
	mixer.channel(1).setOscillator(&o2);
	mixer.channel(1).setEnvelope(&e2);

	/* Create output file */
	std::cout << "Creating output file " << OUTPUT_FILENAME << std::endl;
	FILE* fo = fopen(OUTPUT_FILENAME, "wb");
	if (fo == NULL) {
		std::cout << "Cannot create output file !" << std::endl;
		return 1;
	}

	/* Fill wave file header */
	WavHeader_t whead;
	whead.RIFF[0] = 'R';
	whead.RIFF[1] = 'I';
	whead.RIFF[2] = 'F';
	whead.RIFF[3] = 'F';
	whead.ChunkSize = 36 + (SAMPLE_RATE * NB_SECONDS_RUN * 2);
	whead.WAVE[0] = 'W';
	whead.WAVE[1] = 'A';
	whead.WAVE[2] = 'V';
	whead.WAVE[3] = 'E';
	whead.fmt[0] = 'f';
	whead.fmt[1] = 'm';
	whead.fmt[2] = 't';
	whead.fmt[3] = ' ';
	whead.Subchunk1Size = 16;
	whead.AudioFormat = 1;
	whead.NumOfChan = 1;
	whead.SamplesPerSec = SAMPLE_RATE;
	whead.bytesPerSec = SAMPLE_RATE * 2;
	whead.blockAlign = 2;
	whead.bitsPerSample = 16;
	whead.Subchunk2ID[0] = 'd';
	whead.Subchunk2ID[1] = 'a';
	whead.Subchunk2ID[2] = 't';
	whead.Subchunk2ID[3] = 'a';
	whead.Subchunk2Size = SAMPLE_RATE * NB_SECONDS_RUN * 2;

	/* Write file header */
	std::cout << "Writing WAVE header ..." << std::endl;
	fwrite(&whead, sizeof(WavHeader_t), 1, fo);

	/* Run sound generator for N seconds */
	for (uint16_t i = 0; i < NB_SECONDS_RUN; ++i) {

		/* Samples buffer */
		CheapTune::Sample_t buffer[SAMPLE_RATE];

		/* Run the sound generator for one second */
		std::cout << "Sound generation " << i + 1 << " of " << NB_SECONDS_RUN
				<< std::endl;

		((CheapTune::AdsrEnvelope*) mixer.channel(1).envelope())->noteOn();
		for (uint16_t j = 0; j < SAMPLE_RATE; ++j) {
			buffer[j] = mixer.getSample();

			if (j == (SAMPLE_RATE / 2))
				((CheapTune::AdsrEnvelope*) mixer.channel(1).envelope())->noteOff();
		}

		/* Write the buffer */
		std::cout << "Writing sound buffer ..." << std::endl;
		fwrite(buffer, sizeof(CheapTune::Sample_t), SAMPLE_RATE, fo);
	}

	/* No error */
	std::cout << "Cheaptune exiting ..." << std::endl;
	return 0;
}

