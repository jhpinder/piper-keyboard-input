#include "PiperMidiProcessor.h"

// initialize static members of PiperMidiProcessor
PiperMidi::PiperMidiMessage* PiperMidiProcessor::messageBuffer[NUM_INPUTS];
uint16_t PiperMidiProcessor::numMessagesInBuffer = 0;

void PiperMidiProcessor::processInputChanges() {
  // detect changes in input states using XOR and populate messageBuffer
  numMessagesInBuffer = 0;
  for (int i = 0; i < NUM_32_BIT_BUFFERS; i++) {
    uint32_t changed = PiperHardware::prevInputStates[i] ^ PiperHardware::currInputStates[i];

    while (changed) {
      uint8_t bitIndex = __builtin_ctz(changed);
      uint16_t inputNumber = (i << 5) | bitIndex; // 32 bit offset plus bit index

      if (inputNumber < NUM_INPUTS) {
        bool newState = (PiperHardware::currInputStates[i] >> bitIndex) & 1;
        messageBuffer[numMessagesInBuffer++] =
            &midiMap[inputNumber][newState]; // store pointer in next available slot in message buffer
      }

      changed &= changed - 1;
    }
  }
}

void PiperMidiProcessor::sendPiperMidiMessages() {
  for (uint16_t i = 0; i < numMessagesInBuffer; i++) {
    PiperMidi::PiperMidiMessage* message = messageBuffer[i];
    uint8_t buffer[2];
    message->pack(buffer);
    Serial1.write(buffer, 2);
  }
  numMessagesInBuffer = 0;
}
