# piper-keyboard-input

### Shift Register Parallel Input Scanning for Piper

- Three manuals 61 notes each
- One 32 note pedalboard
- Pedal pistons: 24
- Manual pistons: Total 61 pistons
    - Top manual: 15 pistons
    - Middle manual: 20 pistons
    - Bottom manual: 26 pistons including set piston, which needs to be a note on off instead of a piston press message

Total used inputs: 300 (61 * 3 + 32 + 24 + 61)<br>
Total inputs with padding to byte boundaries: 320 (40 shift registers of 8 bits each)

---
### Shift Register Configuration

#### 74HC165 Parallel-In Serial-Out Shift Registers

Each manual must start on a new byte boundary, so padding bits are added as necessary.
Pistons need not be byte-aligned.
- Top Manual: 8 shift registers (64 bits; 61 notes + 3 padding)
- Middle Manual: 8 shift registers (64 bits; 61 notes + 3 padding)
- Bottom Manual: 8 shift registers (64 bits; 61 notes + 3 padding)
- Pedalboard + pedal pistons: 8 shift registers (64 bits; 32 notes + 24 pistons + 8 extra inputs)
- Manual pistons: 8 shift registers (64 bits; 61 pistons + 3 extra inputs)

#### Total Shift Registers: 39
---
### PCB Inputs

64-pin columns, each with their own shift register chain:
- Column 1: Bottom Manual (61 notes + set piston + 2 padding)
- Column 2: Middle Manual (61 notes + 3 padding)
- Column 3: Top Manual (61 notes + 3 padding)
- Column 4: Pedalboard (32 notes + 32 extra inputs)
- Column 5: Manual non-setter pistons + extra piston inputs (60 non-setter pistons + 5 extra piston inputs)
- Column 6: Pedal pistons (24 pistons + 40 extra piston inputs)
- Columns 7-8: Reserved for future expansion or additional controls

### Usage of SPI

The 74HC165 shift registers will be connected in series for each column, allowing us to read all inputs using a single SPI interface. The microcontroller will use the SPI protocol to clock in the data from the shift registers, which will then be processed to determine the state of each input.