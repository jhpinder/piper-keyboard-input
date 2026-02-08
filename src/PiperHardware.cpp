#include "PiperHardware.h"

uint8_t PiperHardware::dipStates = 0;
uint32_t* PiperHardware::prevInputStates = new uint32_t[NUM_32_BIT_BUFFERS]();
uint32_t* PiperHardware::currInputStates = new uint32_t[NUM_32_BIT_BUFFERS]();
int PiperHardware::dmaChannel = -1;
repeating_timer_t PiperHardware::inputTimer;
volatile bool PiperHardware::dmaInProgress = false;

void PiperHardware::initialize() {
  initDips();
  initRS485();
  initNeoPixel();
  initSPI();
  initDMA();
  startInputPolling();
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

void PiperHardware::initSPI() {
  SPI.setSCK(SPI_SCK_PIN);
  SPI.setRX(SPI_RX_PIN);
  SPI.begin();
  spi_set_baudrate(spi0, SPI_BAUDRATE);

  // Use GPIO functions for fast access in ISR
  gpio_init(PIN_PL);
  gpio_set_dir(PIN_PL, GPIO_OUT);
  gpio_put(PIN_PL, 1);  // Start HIGH
}

void PiperHardware::initDMA() {
  dmaChannel = dma_claim_unused_channel(true);
  dma_channel_config c = dma_channel_get_default_config(dmaChannel);
  channel_config_set_transfer_data_size(&c, DMA_SIZE_8);
  channel_config_set_read_increment(&c, false);   // Read from single SPI FIFO
  channel_config_set_write_increment(&c, true);   // Write to sequential buffer
  channel_config_set_dreq(&c, spi_get_dreq(spi0, false));
  dma_channel_configure(dmaChannel, &c, PiperHardware::currInputStates, &spi_get_hw(spi0)->dr, SHIFT_REGISTER_COUNT,
                        false);
}

void PiperHardware::startInputPolling() {
  // Start 1ms repeating timer (-1 = delay before first call)
  add_repeating_timer_ms(-READ_INTERVAL, timerCallback, NULL, &inputTimer);
}

bool PiperHardware::timerCallback(repeating_timer_t* rt) {
  // Safety check: skip if previous DMA still running
  if (dmaInProgress && dma_channel_is_busy(dmaChannel)) {
    return true;  // Continue timer
  }

  // Pulse PIN_PL to latch 74HC165 inputs (LOW then HIGH)
  gpio_put(PIN_PL, 0);
  busy_wait_us_32(1);  // 1μs pulse width
  gpio_put(PIN_PL, 1);

  // Start DMA transfer to read 64 bytes from SPI
  dmaInProgress = true;
  dma_channel_set_write_addr(dmaChannel, currInputStates, true);

  return true;  // Continue timer
}

void PiperHardware::updateInputStates() {
  // Check if DMA transfer is complete
  if (dmaInProgress && !dma_channel_is_busy(dmaChannel)) {
    dmaInProgress = false;

    // Swap buffer pointers (zero-copy)
    uint32_t* temp = prevInputStates;
    prevInputStates = currInputStates;
    currInputStates = temp;
  }
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