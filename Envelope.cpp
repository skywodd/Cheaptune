/* Dependencies */
#include "Envelope.h"

namespace CheapTune {

Envelope::~Envelope() {
}

Amplitude_t Envelope::getSample() {
	return 255;
}

void Envelope::reset() {
}

}
