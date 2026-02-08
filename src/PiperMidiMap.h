#pragma once
#include "constants.h"

// this is a 2d array, first dimension is input number 0-511, second dimension is the new state
static PiperMidi::PiperMidiMessage midiMap[512][2];

// this function creates a 512 entry map from input number to a PiperMidiMessage
// eventually this will be configured using a csv file but for now we will hardcode the following:
// inputs    0-63: column 0, note on/off, note number starts at 36 and increments by 1 for each input
// inputs  64-127: column 1, note on/off, note number starts at 36 and increments by 1 for each input
// inputs 128-191: column 2, note on/off, note number starts at 36 and increments by 1 for each input
// inputs 192-255: column 3, note on/off, note number starts at 36 and increments by 1 for each input
// inputs 256-319: column 4, piston press, note number starts at 0 and increments by 1 for each input
// inputs 320-383: column 5, piston press, note number starts at 0 and increments by 1 for each input
// inputs 384-447: column 6, piston press, note number starts at 0 and increments by 1 for each input
// inputs 448-511: column 7, piston press, note number starts at 0 and increments by 1 for each input

inline void initializeDefaultPiperMidiMap() {
  for (int i = 0; i < 512; i++) {
    int column = i >> 6;
    int noteNumber = (i & 0x3F) + 36;

    PiperMidi::PiperMidiMessage* mapEntry = &midiMap[i][0];
    uint8_t col = static_cast<uint8_t>(column);

    if (column < 4) {
      mapEntry[0] = {col, PiperMidi::PiperMidiMessageType::NoteOn, static_cast<uint8_t>(noteNumber)};
      mapEntry[1] = {col, PiperMidi::PiperMidiMessageType::NoteOff, static_cast<uint8_t>(noteNumber)};
    } else {
      uint8_t noteNum = static_cast<uint8_t>(i - 256);
      mapEntry[0] = {col, PiperMidi::PiperMidiMessageType::PistonPress, noteNum};
      mapEntry[1] = {}; // no note off for pistons
    }
  }
}