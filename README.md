# CMPE220 CPU Project

A complete 16-bit software CPU implementation in C featuring:
- Custom instruction set architecture (ISA)
- ALU with arithmetic and logic operations
- Control unit with fetch-decode-execute cycle
- Memory-mapped I/O for character output
- Assembler for assembly language programs
- Example programs: Timer, Hello World, Fibonacci

## Repository Contents

### Documentation
- **ISA.md** - Complete instruction set architecture specification
- **MEMORY_MAP.md** - Memory organization and I/O mapping
- **CPU_SCHEMATIC.md** - CPU architecture block diagram
- **220 project report.pdf** - Full project report

### Source Code
- **cpu.c** - Main CPU emulator with all components
- **assembler.c** - Assembler for converting .asm to machine code
- **run_hello.c** - Hello World program demonstration
- **run_fibonacci.c** - Fibonacci sequence with detailed cycle tracing

### Assembly Programs
- **timer.asm** - Timer program showing Fetch/Compute/Store cycles
- **hello.asm** - Hello World program using memory-mapped I/O
- **fibonacci.asm** - Fibonacci sequence implementation

## Quick Start

### 1. Compile the Main CPU Emulator

**On Linux or Mac:**
```bash
gcc -std=c11 cpu.c -o cpu
./cpu
```

**On Windows (MinGW-w64):**
```bash
gcc -std=c11 cpu.c -o cpu.exe
cpu.exe
```

### 2. Run Hello World Program

```bash
gcc -std=c11 run_hello.c -o hello
./hello
```

Expected output: `HELLO, WORLD!`

### 3. Run Fibonacci Program with Cycle Trace

```bash
gcc -std=c11 run_fibonacci.c -o fibonacci
./fibonacci
```

This shows detailed Fetch-Decode-Execute-Store cycles for the Fibonacci sequence.

### 4. Use the Assembler

Compile the assembler:
```bash
gcc -std=c11 assembler.c -o assembler
```

Assemble a program:
```bash
./assembler timer.asm timer.h
```

This generates:
- **timer.h** - C header file with machine code
- **timer.bin** - Binary machine code file

## Project Structure

```
CMPE220_Project/
├── Documentation/
│   ├── ISA.md                 # Instruction set specification
│   ├── MEMORY_MAP.md          # Memory organization
│   ├── CPU_SCHEMATIC.md       # Architecture diagram
│   └── 220 project report.pdf # Project report
├── Source Code/
│   ├── cpu.c                  # CPU emulator
│   ├── assembler.c            # Assembler
│   ├── run_hello.c            # Hello World demo
│   └── run_fibonacci.c        # Fibonacci demo
├── Assembly Programs/
│   ├── timer.asm              # Timer program
│   ├── hello.asm              # Hello World
│   └── fibonacci.asm          # Fibonacci sequence
└── README.md                  # This file
```

## CPU Architecture

### Components
- **8 General Purpose Registers** (R0-R7, 16-bit each)
- **ALU** with arithmetic, logic, and special operations
- **Control Unit** with IP, IR, and status flags
- **400 words of memory** (16-bit words)
- **Stack** for function calls
- **Memory-Mapped I/O** at address 0x20 for character output

### Instruction Set
13 core instructions:
- **Data**: NOP, MOV, LOAD, STORE
- **Arithmetic**: ADD, SUB, MUL, DIV
- **Logic**: AND, OR
- **Control**: JMP, JZ, CALL, RET, HALT

See **ISA.md** for complete specification.

## Example Programs

### Timer Program
Demonstrates CPU cycles with a counting loop:
```bash
./assembler timer.asm
# Include generated timer.h in a loader program
```

### Hello World
Outputs "HELLO, WORLD!" using memory-mapped I/O:
```bash
./hello
```

### Fibonacci Sequence
Computes first 10 Fibonacci numbers with detailed execution trace:
```bash
./fibonacci
```

## Development Environment

### Requirements
- GCC compiler with C11 support
- Standard C library

### Tested On
- macOS with Xcode Command Line Tools
- Linux with GCC
- Windows with MinGW-w64

## Video Demonstration

[Link to demo video explaining Fibonacci program]

## GitHub Repository

[https://github.com/YOUR_USERNAME/CMPE220_Project](https://github.com/YOUR_USERNAME/CMPE220_Project)

## Team Members

[Add team member names and contributions here]

## License

This project is for educational purposes as part of CMPE220 course.
