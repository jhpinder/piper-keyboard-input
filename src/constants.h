#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>
#include <piper-midi.h>

/// TODO: Update pin numbers
const uint8_t DIP_PINS[8] = {2, 3, 4, 5, 6, 7, 8, 9};
#define MIDI_CH_MASK 0x0F
#define OCTAVE_MASK 0xF0

/**
 * Octave lookup table
 * Maps 4-bit DIP switch values to octave startng midi notes
 *
 * DIP Value : Base MIDI Note
 * 1000 : 36
 * 1100 : 48
 * 1110 : 60
 * 0100 : 24
 * 0110 : 12
 * 0111 : 0
 * All other values default to 36
 */
const uint8_t OCTAVE_LUT[16] = {36, 36, 36, 36, 24, 36, 12, 0, 36, 36, 36, 36, 48, 36, 60, 36};

// Communication
#define RS485_BAUDRATE 1000000
/// TODO: Update pin number
#define RS485_DE_PIN 10

// SPI constants
#define PIN_PL 17
#define SPI_SCK_PIN 18
#define SPI_RX_PIN 16
#define SPI_BAUDRATE 2000000
#define READ_INTERVAL 1

// Shift register constants
#define POINTS_PER_COLUMN 64
#define NUM_COLUMNS 8
#define SHIFT_REGISTER_COUNT 64
#define SHIFT_REGISTER_SIZE 8
#define NUM_INPUTS (SHIFT_REGISTER_COUNT * SHIFT_REGISTER_SIZE)
constexpr uint8_t NUM_32_BIT_BUFFERS((NUM_INPUTS + 31) / 32);

// MIDI constants
#define MIDI_NOTE_MIN 0
#define MIDI_NOTE_MAX 127

// NeoPixel constants
#define NEOPIXEL_PIN 14
#define NEOPIXEL_COUNT 1

#endif