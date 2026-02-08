#include "PiperMidiProcessor.h"

PiperHardware hardware;
PiperMidiProcessor midiProcessor;

void setup() { PiperHardware::initialize(); }

void loop() {
  PiperHardware::updateInputStates();
  PiperMidiProcessor::sendPiperMidiMessages();
}