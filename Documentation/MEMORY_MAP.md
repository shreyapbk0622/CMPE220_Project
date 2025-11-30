# CMPE220 CPU - Memory Map

## Overview
The CPU has 400 words (16-bit) of addressable memory. Memory is organized into distinct regions for code, data, I/O, and stack.

## Memory Layout

```
Address Range    | Size   | Purpose
-----------------|--------|----------------------------------
0x000 - 0x013    | 20     | Memory-Mapped I/O Region
0x014 - 0x18F    | 380    | Program Code and Data Region
0x190 - 0x18F    | 10     | Stack Region (grows downward)
```

## Detailed Memory Regions

### 1. Memory-Mapped I/O Region (0x000 - 0x013)
This region is reserved for input/output operations.

| Address | Purpose | Access | Description |
|---------|---------|--------|-------------|
| 0x020   | CHAR_OUT | Write | Character output port. Write ASCII value to display character |

**Usage Example:**
```asm
MOV R0, 72      ; ASCII 'H'
MOV R1, 32      ; Store address 32 (0x20)
; Write R0 value to memory[R1] to output 'H'
```

### 2. Program Code and Data Region (0x014 - 0x18F)
This is the main region for storing:
- Program instructions
- Static data
- Global variables
- Constants

**Characteristics:**
- Read/Write access
- Programs are loaded starting at address 0
- Data can be stored anywhere in this region
- Total size: 380 words

**Organization:**
- Addresses 0-N: Program instructions (loaded by `load_program`)
- Addresses N+1 onwards: Available for data storage

### 3. Stack Region (0x190 - 0x18F)
The stack is used for:
- Function call return addresses
- Local variables (if extended)
- Temporary storage

**Characteristics:**
- Grows downward (from high addresses to low)
- Stack Pointer (SP) initialized to 399 (0x18F)
- CALL instruction pushes return address
- RET instruction pops return address
- Stack overflow occurs when SP reaches 0x18F
- Stack underflow occurs when SP exceeds 399

**Stack Operations:**
```
Initial state: SP = 399

CALL subroutine:
  memory[SP] = IP    ; Push return address
  SP = SP - 1        ; Decrement stack pointer
  IP = target        ; Jump to subroutine

RET:
  SP = SP + 1        ; Increment stack pointer
  IP = memory[SP]    ; Pop return address
```

## Memory Access Patterns

### Sequential Instruction Fetch
```
IP = 0
Loop:
  IR = memory[IP]
  IP = IP + 1
  Execute instruction
  If not HALT, goto Loop
```

### Stack Frame Example
```
Before CALL (SP=399):
  [399] = (empty/previous data)

After CALL to address 50 (from IP=20):
  [399] = 20        ; Return address
  SP = 398
  IP = 50

After RET:
  SP = 399
  IP = 20           ; Restored from stack
```

## Memory Protection

Currently, the CPU does not implement memory protection. Programs can access any memory location.

**Potential Issues:**
- Programs can overwrite their own code
- Stack can overflow into code/data region
- No protection against invalid memory access

**Future Enhancements:**
- Add memory protection boundaries
- Separate code and data segments
- Add hardware memory management unit (MMU)

## I/O Port Details

### Character Output Port (0x020)

**Purpose:** Write characters to console output

**Operation:**
1. Write ASCII value to memory address 0x020
2. Character is immediately displayed
3. No buffering - direct output

**Supported Characters:**
- ASCII printable characters (32-126)
- Newline (10)
- Carriage return (13)

**Example Programs:**

**Print 'A':**
```asm
MOV R0, 65      ; ASCII 'A'
MOV R1, 32      ; Address of CHAR_OUT
; Store R0 at address in R1
```

**Print "HELLO":**
```asm
MOV R0, 72      ; 'H'
; Output R0
MOV R0, 69      ; 'E'
; Output R0
MOV R0, 76      ; 'L'
; Output R0
MOV R0, 76      ; 'L'
; Output R0
MOV R0, 79      ; 'O'
; Output R0
```

## Memory Timing

All memory operations complete in a single cycle:
- Instruction fetch: 1 cycle
- Memory read: 1 cycle (if implemented)
- Memory write: 1 cycle (if implemented)

## Memory Initialization

On CPU reset/initialization:
- All memory locations set to 0
- SP set to 399
- IP set to 0
- Program loaded into memory starting at address 0
