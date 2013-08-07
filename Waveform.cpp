/* Dependencies */
#include <stdint.h>
#include "Waveform.h"

namespace CheapTune {

const int8_t Waveform::_sinusoids[] = { 0, 3, 6, 9, 12, 16, 19, 22, 25, 28, 31,
		34, 37, 40, 43, 46, 49, 51, 54, 57, 60, 63, 65, 68, 71, 73, 76, 78, 81,
		83, 85, 88, 90, 92, 94, 96, 98, 100, 102, 104, 106, 107, 109, 111, 112,
		113, 115, 116, 117, 118, 120, 121, 122, 122, 123, 124, 125, 125, 126,
		126, 126, 127, 127, 127, 127, 127, 127, 127, 126, 126, 126, 125, 125,
		124, 123, 122, 122, 121, 120, 118, 117, 116, 115, 113, 112, 111, 109,
		107, 106, 104, 102, 100, 98, 96, 94, 92, 90, 88, 85, 83, 81, 78, 76, 73,
		71, 68, 65, 63, 60, 57, 54, 51, 49, 46, 43, 40, 37, 34, 31, 28, 25, 22,
		19, 16, 12, 9, 6, 3, 0, -3, -6, -9, -12, -16, -19, -22, -25, -28, -31,
		-34, -37, -40, -43, -46, -49, -51, -54, -57, -60, -63, -65, -68, -71,
		-73, -76, -78, -81, -83, -85, -88, -90, -92, -94, -96, -98, -100, -102,
		-104, -106, -107, -109, -111, -112, -113, -115, -116, -117, -118, -120,
		-121, -122, -122, -123, -124, -125, -125, -126, -126, -126, -127, -127,
		-127, -127, -127, -127, -127, -126, -126, -126, -125, -125, -124, -123,
		-122, -122, -121, -120, -118, -117, -116, -115, -113, -112, -111, -109,
		-107, -106, -104, -102, -100, -98, -96, -94, -92, -90, -88, -85, -83,
		-81, -78, -76, -73, -71, -68, -65, -63, -60, -57, -54, -51, -49, -46,
		-43, -40, -37, -34, -31, -28, -25, -22, -19, -16, -12, -9, -6, -3 };

Waveform::Waveform(WaveformType_t waveform, uint8_t duty) :
		_waveform(waveform), _duty(duty), _noise(0xACE1) {
}

void Waveform::setDuty(uint8_t duty) {
	_duty = duty;
}

void Waveform::setWaveform(WaveformType_t waveform) {
	_waveform = waveform;
}

void Waveform::reset() {
	_waveform = WAVE_NONE;
	_duty = 0;
}

int8_t Waveform::getSample(uint8_t index) {

	/* Noise generator based on Galois LFSR */
	_noise = (_noise >> 1) ^ (-(_noise & 1) & 0xB400U);

	/* Switch to the required generation algorithm */
	switch (_waveform) {

	case WAVE_NONE: /* No signal */
		return 0;
		break;

	case WAVE_DC: /* Constant signal */
		return _duty - ((_duty > 127) ? 128 : 127);
		break;

	case WAVE_SINUS: /* Sinus wave */
		return _sinusoids[index]; /* Use pre-computed wave table */
		break;

	case WAVE_TRIANGLE: /* Triangle wave */

		/* Triangle wave generation algorithm */
		if (index < 64) { // I: 0 ~ 63
			return ((int16_t) index) * 127 / 63; // O: 0 ~ 127
		} else if (index >= 64 && index < 128) { // I: 64 ~ 127
			return ((int16_t) index - 64) * -127 / 63 + 127; // O: 127 ~ 0
		} else if (index >= 128 && index < 192) { // I: 128 ~ 191
			return ((int16_t) index - 128) * -127 / 63; // O: 0 ~ -127
		} else { // I: 192 ~ 255
			return ((int16_t) index - 192) * 127 / 63 - 127; // O: -127 ~ 0
		}
		break;

	case WAVE_SQUARE: /* Square wave */
		return (index >= _duty) ? 127 : -127;
		break;

	case WAVE_SAWTOOTH: /* Sawtooth wave */

		/* Sawtooth wave generation algorithm */
		if (index < 128) { // I: 0 ~ 127
			return index;  // O: 0 ~ 127
		} else { // I: 128 ~ 255
			return index - 255;  // O: -127 ~ 0
		}
		break;

	case WAVE_NOISE: /* Noise */
		return _noise & 0xFF;
		break;
	}

	/* Warning fix */
	return 0;
}

}
