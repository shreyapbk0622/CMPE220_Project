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
- **fib_using_cpu.c** - ✨ NEW: Fibonacci with clear output and register tracking
- **fib_simple.c** - Simple Fibonacci register simulation
- **timer.c** - Timer demonstration showing Fetch/Compute/Store cycles

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
### 2. Run Timer Program - to show how execution happens in Fetch/Compute/Store cycles

```bash
gcc -std=c11 timer.c -o timer
./timer
```

Expected output: `HELLO, WORLD!`

### 3. Run Hello World Program

```bash
gcc -std=c11 run_hello.c -o hello
./hello
```

Expected output: `HELLO, WORLD!`

### 4. Run Fibonacci Program with Clear Output ✨ NEW

```bash
gcc -std=c11 fib_using_cpu.c -o fib_using_cpu
./fib_using_cpu
```

This shows:
- Complete Fibonacci sequence: 0 → 1 → 1 → 2 → 3 → 5 → 8 → 13 → 21 → 34
- Register states (R0, R1, R2, R4) at each iteration
- CPU operations breakdown per iteration
- Final register values when computation completes

Expected output: Clean table showing each Fibonacci number with register tracking

### 5. Run Original Fibonacci Program (Detailed Cycles)

```bash
gcc -std=c11 run_fibonacci.c -o fibonacci
./fibonacci
```

This shows detailed Fetch-Decode-Execute-Store cycles for the Fibonacci sequence (verbose output).

### 6. Use the Assembler

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
│   ├── ISA.md                    # Instruction set specification
│   ├── MEMORY_MAP.md             # Memory organization
│   ├── CPU_SCHEMATIC.md          # Architecture diagram
│   └── 220 project report.pdf    # Project report
├── SourceCodes/
│   ├── cpu.c                     # CPU emulator
│   ├── assembler.c               # Assembler
│   ├── run_hello.c               # Hello World demo
│   ├── run_fibonacci.c           # Fibonacci with detailed cycles
│   ├── fib_using_cpu.c           # ✨ Fibonacci with clear output
│   ├── fib_simple.c              # Simple Fibonacci simulation
│   ├── timer.c                   # Timer demonstration
│   └── timer.h                   # Timer header
├── Assembly_programs/
│   ├── timer.asm                 # Timer program
│   ├── hello.asm                 # Hello World
│   ├── fibonacci.asm             # Fibonacci sequence
│   └── run_timer.c               # Timer runner
├── CMPE_220_Project_Report_Group_9.pdf  # Project report
├── demo_video_cmpe_220.mp4       # Demo video
└── README.md                     # This file
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

### Fibonacci Sequence (Recommended) ✨
**File**: `fib_using_cpu.c`

Computes first 10 Fibonacci numbers with clean, educational output:
```bash
cd SourceCodes
gcc -std=c11 fib_using_cpu.c -o fib_using_cpu
./fib_using_cpu
```

**Features**:
- Based on CPU emulator architecture from `cpu.c`
- Clear table showing each Fibonacci value and register states
- Step-by-step register updates (R0, R1, R2, R4)
- CPU operations breakdown per iteration
- Output: 0 → 1 → 1 → 2 → 3 → 5 → 8 → 13 → 21 → 34

**Register Usage**:
- R0 = F(n-2) - Second previous Fibonacci number
- R1 = F(n-1) - Previous Fibonacci number
- R2 = Counter (iteration number)
- R3 = Limit (10 numbers)
- R4 = Temporary storage for new Fibonacci number

### Timer Program
Demonstrates CPU cycles with a counting loop:
```bash
cd SourceCodes
gcc -std=c11 timer.c -o timer
./timer
```

### Hello World
Outputs "HELLO, WORLD!" using memory-mapped I/O:
```bash
cd SourceCodes
gcc -std=c11 run_hello.c -o hello
./hello
```

### Fibonacci (Verbose Cycle Trace)
**File**: `run_fibonacci.c`

Shows detailed Fetch-Decode-Execute-Store cycles:
```bash
cd SourceCodes
gcc -std=c11 run_fibonacci.c -o fibonacci
./fibonacci
```
This version shows every CPU cycle in detail (verbose output).

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

[https://github.com/shreyapbk0622/CMPE220_Project](https://github.com/shreyapbk0622/CMPE220_Project)

## Team Members

[Add team member names and contributions here]

## License

This project is for educational purposes as part of CMPE220 course.
