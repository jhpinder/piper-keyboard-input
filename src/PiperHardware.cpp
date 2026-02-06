#include "PiperHardware.h"

uint8_t PiperHardware::dipStates = 0;
uint32_t* PiperHardware::prevInputStates = new uint32_t[NUM_32_BIT_BUFFERS]();
uint32_t* PiperHardware::currInputStates = new uint32_t[NUM_32_BIT_BUFFERS]();

void PiperHardware::initialize() {
  initDips();
  initRS485();
  initShiftRegisters();
}

void PiperHardware::initDips() {
  for (uint8_t i = 0; i < 8; i++) {
    pinMode(DIP_PINS[i], INPUT_PULLUP);
  }
  readDips();
}

void PiperHardware::readDips() {
  uint32_t reg = gpio_get_all();
  dipStates = (uint8_t)(((reg >> DIP_PINS[0]) & 0x01) << 0 | ((reg >> DIP_PINS[1]) & 0x01) << 1 |
                        ((reg >> DIP_PINS[2]) & 0x01) << 2 | ((reg >> DIP_PINS[3]) & 0x01) << 3 |
                        ((reg >> DIP_PINS[4]) & 0x01) << 4 | ((reg >> DIP_PINS[5]) & 0x01) << 5 |
                        ((reg >> DIP_PINS[6]) & 0x01) << 6 | ((reg >> DIP_PINS[7]) & 0x01) << 7) ^
              0xFF; // Invert because of pull-up resistors
}

void PiperHardware::initRS485() {
  pinMode(RS485_DE_PIN, OUTPUT);
  digitalWrite(RS485_DE_PIN, HIGH); // Set to HIGH for transmit mode
  Serial1.begin(RS485_BAUDRATE);
}

void PiperHardware::initShiftRegisters() {
  pinMode(PIN_DATA, INPUT);
  pinMode(PIN_CLOCK, OUTPUT);
  pinMode(PIN_LATCH, OUTPUT);
  digitalWrite(PIN_CLOCK, LOW);
  digitalWrite(PIN_LATCH, LOW);
}

void PiperHardware::readShiftRegisters(uint8_t* buffer, size_t length) {
  /// TODO: Implement PIO/DMA for more efficient reading
}

uint8_t PiperHardware::getPiperMidiChannelFromDips() { return (dipStates & MIDI_CH_MASK); }
uint8_t PiperHardware::getOctaveFromDips() { return OCTAVE_LUT[(dipStates & OCTAVE_MASK) >> 4]; }

void PiperHardware::initNeoPixel() {
  /// TODO: Implement NeoPixel initialization
}

void PiperHardware::setGreen() {
  /// TODO: Implement setting NeoPixel to green
}

void PiperHardware::setRed() {
  /// TODO: Implement setting NeoPixel to red
}

void PiperHardware::setYellow() {
  /// TODO: Implement setting NeoPixel to yellow
}

void PiperHardware::setOff() {
  /// TODO: Implement turning off NeoPixel
}