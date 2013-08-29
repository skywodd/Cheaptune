/* Dependencies */
#include "NoiseWaveform.h"

namespace CheapTune {

NoiseWaveform::NoiseWaveform(uint32_t seed) :
	_lfsr(seed) {
}

void NoiseWaveform::reSeedNoise(uint32_t seed) {
	_lfsr = seed;
}

Sample_t NoiseWaveform::getSample(WavetableIndex_t index) {

	/* Compute Galois LFSR */
	/* taps: 32 31 29 1; feedback polynomial: x^32 + x^31 + x^29 + x + 1 */
	_lfsr = (_lfsr >> 1) ^ (-(_lfsr & 1u) & 0xD0000001u);

	/* Return the sample */
	return (Sample_t) _lfsr;
}

}
