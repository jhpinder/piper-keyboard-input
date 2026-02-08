#include "PiperHardware.h"

class PiperMidiProcessor {

public:
  static uint8_t getPiperMidiNoteForInput(uint8_t inputNumber);
  static void sendPiperMidiMessages();
};