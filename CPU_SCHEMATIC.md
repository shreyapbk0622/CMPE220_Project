# CMPE220 CPU Architecture Schematic

## Block Diagram

```
┌─────────────────────────────────────────────────────────────────────────────┐
│                              CMPE220 CPU                                     │
│                                                                              │
│  ┌──────────────────────────────────────────────────────────────────────┐  │
│  │                         Control Unit (CU)                             │  │
│  │  ┌──────────┐  ┌──────────┐  ┌────────────────────────────┐         │  │
│  │  │    IP    │  │    IR    │  │      ALU Flags             │         │  │
│  │  │(16 bits) │  │(16 bits) │  │  ZR  NG  OV  CY            │         │  │
│  │  └──────────┘  └──────────┘  └────────────────────────────┘         │  │
│  │                                                                        │  │
│  │  Fetch → Decode → Execute Control Logic                               │  │
│  └───────────────────────────┬──────────────────────────────────────────┘  │
│                              │                                              │
│                    Control Signals                                          │
│                              │                                              │
│  ┌───────────────────────────┼──────────────────────────────────────────┐  │
│  │                           ▼                                           │  │
│  │                     System Bus (16-bit)                               │  │
│  │                                                                        │  │
│  └──┬─────────┬──────────┬──────────┬──────────┬───────────────────────┘  │
│     │         │          │          │          │                           │
│     │         │          │          │          │                           │
│  ┌──▼─────┐ ┌─▼──────┐ ┌─▼──────┐ ┌─▼──────┐ ┌▼────────────────────────┐  │
│  │  GPR   │ │  SPR   │ │  ALU   │ │ Memory │ │   Memory-Mapped I/O     │  │
│  │ (GPR)  │ │        │ │        │ │        │ │                         │  │
│  ├────────┤ ├────────┤ ├────────┤ ├────────┤ │  Address 0x020:         │  │
│  │   R0   │ │   SP   │ │  X(16) │ │  400   │ │  Character Output       │  │
│  │   R1   │ │        │ │  Y(16) │ │  words │ │                         │  │
│  │   R2   │ └────────┘ │ Out(16)│ │ (16bit)│ │  Writes to console      │  │
│  │   R3   │            │        │ │        │ │                         │  │
│  │   R4   │            │ Flags: │ │ Layout:│ └─────────────────────────┘  │
│  │   R5   │            │ zx nx  │ │ 0-19:  │                              │
│  │   R6   │            │ zy ny  │ │  I/O   │                              │
│  │   R7   │            │  f no  │ │ 20-389:│                              │
│  │        │            │        │ │ Code/  │                              │
│  │(8 regs)│            │ Status:│ │ Data   │                              │
│  │ 16-bit │            │ ZR NG  │ │ 390-399│                              │
│  │  each  │            │ OV CY  │ │ Stack  │                              │
│  └────────┘            └────────┘ └────────┘                              │
│                                                                             │
└─────────────────────────────────────────────────────────────────────────────┘
```

## Component Details

### 1. Control Unit (CU)
**Purpose:** Manages the fetch-decode-execute cycle

**Components:**
- **IP (Instruction Pointer)**: 16-bit register pointing to next instruction
- **IR (Instruction Register)**: 16-bit register holding current instruction
- **ALU Flags**: Status flags from last ALU operation
  - ZR (Zero)
  - NG (Negative)
  - OV (Overflow)
  - CY (Carry)

**Operations:**
1. **Fetch**: Read instruction from memory[IP] into IR, increment IP
2. **Decode**: Extract opcode, register numbers, immediate value from IR
3. **Execute**: Perform operation, update registers/memory/flags

### 2. General Purpose Registers (GPR)
**Purpose:** Fast data storage and manipulation

**Specifications:**
- 8 registers (R0-R7)
- Each register is 16 bits wide
- Can store data or addresses
- Used by all arithmetic and logic operations

### 3. Special Purpose Registers (SPR)
**Purpose:** Special functions

**Registers:**
- **SP (Stack Pointer)**: Points to top of stack (initialized to 399)
- Used by CALL and RET instructions

### 4. Arithmetic Logic Unit (ALU)
**Purpose:** Perform arithmetic and logical operations

**Inputs:**
- X: First operand (16 bits)
- Y: Second operand (16 bits)
- Control flags: zx, nx, zy, ny, f, no (6 bits)

**Outputs:**
- Out: Result (16 bits)
- Status flags: ZR, NG, OV, CY

**Operations:**
- Arithmetic: Addition, Subtraction, Multiplication, Division
- Logical: AND, OR, NOT
- Special: Increment, Decrement, Negate, Constants (0, 1, -1)

**ALU Control Flags:**
- zx: Zero X input
- nx: Negate X input
- zy: Zero Y input
- ny: Negate Y input
- f: Function (0=AND, 1=ADD)
- no: Negate output

### 5. Memory
**Purpose:** Store program instructions and data

**Specifications:**
- Size: 400 words × 16 bits
- Organization:
  - 0-19: Memory-mapped I/O
  - 20-389: Code and data
  - 390-399: Stack (grows downward)
- Access: Single-cycle read/write

### 6. System Bus
**Purpose:** Connect all components for data transfer

**Specifications:**
- Width: 16 bits
- Connects: CU, GPR, SPR, ALU, Memory, I/O
- Transfers: Instructions, data, addresses, control signals

### 7. Memory-Mapped I/O
**Purpose:** Interface with external devices

**Ports:**
- **0x020 (32)**: Character output
  - Write ASCII character value
  - Displays to console

## Data Flow Examples

### Example 1: MOV R0, 10
```
1. Fetch: IR ← memory[IP], IP ← IP + 1
2. Decode: OP=MOV, R1=0, IMM=10
3. Execute: GPR[0] ← 10
```

### Example 2: ADD R2, 5
```
1. Fetch: IR ← memory[IP], IP ← IP + 1
2. Decode: OP=ADD, R1=2, IMM=5
3. Execute:
   - ALU.X ← GPR[2]
   - ALU.Y ← 5
   - ALU.compute()
   - GPR[2] ← ALU.out
   - Update flags (ZR, NG, OV, CY)
```

### Example 3: CALL subroutine
```
1. Fetch: IR ← memory[IP], IP ← IP + 1
2. Decode: OP=CALL, IMM=target_address
3. Execute:
   - memory[SP] ← IP    (push return address)
   - SP ← SP - 1        (decrement stack)
   - IP ← target_address (jump to subroutine)
```

### Example 4: Character Output
```
1. MOV R0, 65           ; Load 'A' (ASCII 65)
2. Write to mem[32]:    ; Address 0x020
   - memory[32] ← 65
   - I/O controller detects write
   - Outputs 'A' to console
```

## Timing Diagram

```
Clock Cycle:    1         2         3         4         5
              ┌───┐     ┌───┐     ┌───┐     ┌───┐     ┌───┐
CLK           │   │     │   │     │   │     │   │     │   │
            ──┘   └─────┘   └─────┘   └─────┘   └─────┘   └──

Phase         Fetch     Decode    Execute   Fetch     Decode

IP            0 → 1     1         1         1 → 2     2

IR            ─────     Load      MOV       ─────     Load
                        0x100A    R0,10               0x2403

ALU           ─────     ─────     ─────     ─────     ─────

GPR[R0]       0         0         10        10        10

Flags         ────      ────      ────      ────      ────
```

## Design Philosophy

This CPU design follows RISC principles:
- **Simple instructions**: Each instruction performs one operation
- **Load/store architecture**: Arithmetic operations work on registers
- **Fixed instruction format**: All instructions are 16 bits
- **Small instruction set**: 13 core instructions
- **Direct execution**: No microcode, hardware control

## Future Enhancements

Possible extensions:
1. Add load/store instructions for memory access
2. Implement interrupt system
3. Add more addressing modes (indirect, indexed)
4. Expand I/O capabilities (keyboard input, display)
5. Add cache memory
6. Implement pipelining
7. Add floating-point unit
