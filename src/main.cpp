#include "PiperMidiProcessor.h"

PiperHardware hardware;
PiperMidiProcessor midiProcessor;

void setup() { PiperHardware::initialize(); }

void loop() {
  if (PiperHardware::updateInputStates()) {
    PiperMidiProcessor::processInputChanges();
    PiperMidiProcessor::sendPiperMidiMessages();
  }
  delayMicroseconds(100); // small delay to prevent max cpu usage
}