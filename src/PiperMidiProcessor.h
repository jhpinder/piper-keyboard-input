#include "PiperHardware.h"
#include "PiperMidiMap.h"

class PiperMidiProcessor {

public:
  static void processInputChanges();
  static void sendPiperMidiMessages();

  static PiperMidi::PiperMidiMessage* messageBuffer[NUM_INPUTS];
  static uint16_t numMessagesInBuffer;
};