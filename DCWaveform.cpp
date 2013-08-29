/* Dependencies */
#include "DCWaveform.h"

namespace CheapTune {

CheapTune::DCWaveform::DCWaveform(Sample_t level) :
	_level(level) {
}

void CheapTune::DCWaveform::setDcLevel(Sample_t level) {
	_level = level;
}

void CheapTune::DCWaveform::reset() {
	_level = 0;
}

Sample_t CheapTune::DCWaveform::getSample(WavetableIndex_t) {
	return _level;
}

}
