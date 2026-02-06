#include "constants.h"

class PiperHardware {
public:
  static void initialize();
  static void initDips();
  static void readDips();
  static void initRS485();
  static void initShiftRegisters();
  static void readShiftRegisters(uint8_t* buffer, size_t length);
  static uint8_t getPiperMidiChannelFromDips();
  static uint8_t getOctaveFromDips();

  static void initNeoPixel();
  static void setGreen();
  static void setRed();
  static void setYellow();
  static void setOff();

  static uint8_t dipStates;

  // Store current and previous input states as 32 bit buffers for __builtin_ctzll
  // Once pio/dma is implemented, these can be moved to PIO memory
  static uint32_t* prevInputStates;
  static uint32_t* currInputStates;
};