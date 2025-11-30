# CMPE220 CPU - Instruction Set Architecture (ISA)

## Overview
This is a 16-bit RISC-style CPU with a custom instruction set. The CPU operates on 16-bit words and supports 8 general-purpose registers.

## Instruction Format

### Standard Format (16 bits)
```
| 15-12 | 11-9 | 8-6 | 5-0 |
|-------|------|-----|-----|
|  OP   |  R1  | R2  | IMM |
```

- **OP (4 bits)**: Operation code (0-15)
- **R1 (3 bits)**: First register operand (0-7)
- **R2 (3 bits)**: Second register operand (0-7)
- **IMM (6 bits)**: Immediate value (0-63)

## Registers

### General Purpose Registers (GPR)
- **R0-R7**: 8 general-purpose 16-bit registers
- Can hold data or addresses
- Used for arithmetic, logic, and temporary storage

### Special Purpose Registers (SPR)
- **SP (Stack Pointer)**: Points to the top of the stack
- **IP (Instruction Pointer)**: Points to the next instruction to execute
- **IR (Instruction Register)**: Holds the current instruction being executed

### ALU Flags
- **ZR (Zero)**: Set when result is zero
- **NG (Negative)**: Set when result is negative (bit 15 = 1)
- **OV (Overflow)**: Set on signed arithmetic overflow
- **CY (Carry)**: Set on unsigned arithmetic carry

## Instruction Set

### Data Movement
| Mnemonic | Opcode | Format | Description |
|----------|--------|--------|-------------|
| **NOP**  | 0x0    | `NOP` | No operation |
| **MOV**  | 0x1    | `MOV R1, IMM` | R1 = IMM (immediate to register) |
| **LOAD** | 0xD    | `LOAD R1, R2` | R1 = memory[R2] (load from memory) |
| **STORE**| 0xE    | `STORE R1, R2` | memory[R2] = R1 (store to memory) |

### Arithmetic Operations
| Mnemonic | Opcode | Format | Description |
|----------|--------|--------|-------------|
| **ADD**  | 0x2    | `ADD R1, IMM` | R1 = R1 + IMM |
| **SUB**  | 0x3    | `SUB R1, IMM` | R1 = R1 - IMM |
| **MUL**  | 0x6    | `MUL R1, R2` | R1 = R1 * R2 |
| **DIV**  | 0x7    | `DIV R1, R2` | R1 = R1 / R2 |

### Logical Operations
| Mnemonic | Opcode | Format | Description |
|----------|--------|--------|-------------|
| **AND**  | 0x4    | `AND R1, R2` | R1 = R1 & R2 (bitwise AND) |
| **OR**   | 0x5    | `OR R1, R2` | R1 = R1 \| R2 (bitwise OR) |

### Control Flow
| Mnemonic | Opcode | Format | Description |
|----------|--------|--------|-------------|
| **JMP**  | 0x8    | `JMP IMM` | IP = IMM (unconditional jump) |
| **JZ**   | 0x9    | `JZ IMM` | Jump to IMM if ZR flag is set |
| **CALL** | 0xA    | `CALL IMM` | Push IP to stack, jump to IMM |
| **RET**  | 0xB    | `RET` | Pop IP from stack, return |
| **HALT** | 0xC    | `HALT` | Stop execution |

## Addressing Modes

### 1. Immediate Addressing
- Value is encoded directly in the instruction
- Example: `MOV R0, 10` - Load 10 into R0
- Used by: MOV, ADD, SUB, JMP, JZ, CALL

### 2. Register Addressing
- Operands are in registers
- Example: `MUL R1, R2` - Multiply R1 by R2, store in R1
- Used by: AND, OR, MUL, DIV

### 3. Register Indirect Addressing
- Register contains memory address
- Example: `LOAD R0, R1` - Load from memory[R1] into R0
- Example: `STORE R0, R1` - Store R0 into memory[R1]
- Used by: LOAD, STORE

### 4. Implicit Addressing
- Operands are implied by the instruction
- Example: `HALT` - No operands needed
- Used by: NOP, RET, HALT

## Flag Semantics

### Zero Flag (ZR)
- **Set to 1** when an operation result equals zero
- **Set to 0** when an operation result is non-zero
- Affected by: All arithmetic and logic operations
- Used by: JZ instruction

### Negative Flag (NG)
- **Set to 1** when bit 15 of the result is 1 (negative in two's complement)
- **Set to 0** when bit 15 of the result is 0 (positive)
- Affected by: All arithmetic and logic operations

### Overflow Flag (OV)
- **Set to 1** when signed arithmetic overflow occurs:
  - Adding two positive numbers results in negative
  - Adding two negative numbers results in positive
  - Subtracting positive from negative results in positive
  - Subtracting negative from positive results in negative
- **Set to 0** otherwise
- Affected by: ADD, SUB, MUL, DIV

### Carry Flag (CY)
- **Set to 1** when unsigned arithmetic produces carry/borrow
- For addition: carry out of bit 15
- For subtraction: borrow required
- For multiplication: result exceeds 16 bits
- **Set to 0** otherwise
- Affected by: ADD, SUB, MUL

## Instruction Encoding Examples

```
MOV R0, 10:
  OP=1, R1=0, R2=0, IMM=10
  Binary: 0001 000 000 001010
  Hex: 0x100A

ADD R2, 3:
  OP=2, R1=2, R2=0, IMM=3
  Binary: 0010 010 000 000011
  Hex: 0x2403

JMP 15:
  OP=8, R1=0, R2=0, IMM=15
  Binary: 1000 000 000 001111
  Hex: 0x800F

CALL 20:
  OP=10, R1=0, R2=0, IMM=20
  Binary: 1010 000 000 010100
  Hex: 0xA014

HALT:
  OP=12, R1=0, R2=0, IMM=0
  Binary: 1100 000 000 000000
  Hex: 0xC000
```

## Fetch-Decode-Execute Cycle

### 1. Fetch Phase
- Read instruction from memory at address IP
- Store instruction in IR
- Increment IP

### 2. Decode Phase
- Extract opcode (bits 15-12)
- Extract R1 (bits 11-9)
- Extract R2 (bits 8-6)
- Extract IMM (bits 5-0)

### 3. Execute Phase
- Perform operation based on opcode
- Update destination register or memory
- Update flags (ZR, NG, OV, CY)
- Update IP if control flow instruction

## Special Behaviors

### Stack Operations
- Stack grows downward from address 399
- CALL pushes return address onto stack
- RET pops return address from stack
- Stack overflow detected when SP reaches 0
- Stack underflow detected when SP exceeds 399

### Division by Zero
- Division by zero halts the CPU
- Error message is printed
- CPU running flag is cleared

### Memory-Mapped I/O
- Address 0x20 (32): Character output port
- Writing a value to this address outputs the ASCII character
- Used for printing text to console
