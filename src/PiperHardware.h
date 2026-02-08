#include "constants.h"
#include "hardware/dma.h"
#include "hardware/spi.h"
#include "hardware/gpio.h"
#include <SPI.h>
#include <pico/time.h>

class PiperHardware {
public:
  static void initialize();
  static void initDips();
  static void readDips();
  static void initRS485();
  static void initSPI();
  static void initDMA();

  static void updateInputStates();
  static void startInputPolling();
  static uint8_t getPiperMidiChannelFromDips();
  static uint8_t getOctaveFromDips();

  static void initNeoPixel();
  static void setGreen();
  static void setRed();
  static void setYellow();
  static void setOff();

  static uint8_t dipStates;
  static int dmaChannel;

  // Store current and previous input states as 32 bit buffers for __builtin_ctzll
  // Once pio/dma is implemented, these can be moved to PIO memory
  static uint32_t* prevInputStates;
  static uint32_t* currInputStates;

private:
  static repeating_timer_t inputTimer;
  static volatile bool dmaInProgress;
  static bool timerCallback(repeating_timer_t* rt);
};