#include "PiperMidiProcessor.h"

uint8_t PiperMidiProcessor::getPiperMidiNoteForInput(uint8_t inputNumber) {
  uint8_t octaveBase = PiperHardware::getOctaveFromDips();
  return octaveBase + inputNumber;
}

void PiperMidiProcessor::sendPiperMidiMessages() {
  auto i = 0;
  while (i < NUM_INPUTS) {
  }

  PiperHardware::currInputStates;
}
