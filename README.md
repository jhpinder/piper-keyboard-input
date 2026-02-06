# piper-keyboard-input

### Shift Register Parallel Input Scanning for Piper

- Three manuals 61 notes each
- One 32 note pedalboard
- Pedal pistons: 24
- Manual pistons: Total 61 pistons
    - Top manual: 15 pistons
    - Middle manual: 20 pistons
    - Bottom manual: 26 pistons

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
- Chain 1: Bottom Manual (61 notes + 3 padding)
- Chain 2: Middle Manual (61 notes + 3 padding)
- Chain 3: Top Manual (61 notes + 3 padding)
- Chain 4: Pedalboard + Pedal pistons (32 notes + 24 pistons + 8 extra inputs)
- Chain 5: Manual pistons + extra inputs (61 pistons + 3 extra inputs)