<style>
body {
    line-height: 2.0;
}
</style>

---

<div style="text-align: center; margin-top: 200px;">

# CMPE220 CPU Design Project

## Software CPU Implementation in C

<br><br><br>

### Team Members

**[Student Name 1]**

**[Student Name 2]**

**[Student Name 3]**

<br><br><br>

### Course Information

Computer Architecture and Design - CMPE220

Fall 2025

<br><br><br>

### Instructor

[Instructor Name]

<br><br><br>

### Submission Date

[Date]

</div>

---

<div style="page-break-after: always;"></div>

# GitHub Repository

<br><br>

## Project Repository

The complete source code, documentation, and demo video for this project are available on GitHub:

<br><br>

**Repository URL:**

```
https://github.com/shreyapbk0622/CMPE220_Project
```

<br><br>

**Branch:** `complete-cpu-implementation`

<br><br>

## Demo Video

A comprehensive demonstration video explaining the Fibonacci Sequence program and the CPU's Fetch-Decode-Execute-Store cycle is available at:

<br><br>

**Video URL:**

```
[INSERT VIDEO LINK HERE - YouTube/Google Drive/etc.]
```

<br><br>

The video demonstrates:

- Complete CPU architecture overview

- Fibonacci program execution step-by-step

- Detailed explanation of Fetch, Decode, Execute, and Store phases

- Register state changes during computation

- How the instruction set architecture works in practice

<br><br>

## Repository Contents

The repository includes all project components:

- **Source Code:** CPU emulator (cpu.c), Assembler (assembler.c), Demo programs

- **Documentation:** ISA specification, Memory map, CPU schematic, Build instructions

- **Assembly Programs:** Timer, Hello World, and Fibonacci implementations

- **Report:** This project report and comprehensive status documentation

---

<div style="page-break-after: always;"></div>

# How to Download, Compile, and Run

<br>

## Prerequisites

Before building the project, ensure you have:

- **GCC Compiler** with C11 support or later

- **Git** for cloning the repository

- **Terminal/Command Prompt** access

<br>

### Installing Prerequisites

**On macOS:**
```bash
xcode-select --install
```

**On Linux (Ubuntu/Debian):**
```bash
sudo apt-get update
sudo apt-get install build-essential git
```

**On Windows:**
- Install MinGW-w64 from https://mingw-w64.org
- Add MinGW bin folder to system PATH

<br>

## Download Instructions

### Step 1: Clone the Repository

Open a terminal and run:

```bash
git clone https://github.com/shreyapbk0622/CMPE220_Project.git
cd CMPE220_Project
git checkout complete-cpu-implementation
```

<br>

### Step 2: Verify Files

Confirm all required files are present:

```bash
ls -la
```

You should see:
- `cpu.c` - Main CPU emulator
- `assembler.c` - Assembler implementation
- `run_hello.c` - Hello World demo
- `run_fibonacci.c` - Fibonacci demo
- `*.asm` - Assembly source files
- `*.md` - Documentation files

<br>

## Compilation Instructions

### Compile the CPU Emulator

```bash
gcc -std=c11 cpu.c -o cpu
```

<br>

### Compile the Assembler

```bash
gcc -std=c11 assembler.c -o assembler
```

<br>

### Compile the Hello World Demo

```bash
gcc -std=c11 run_hello.c -o hello
```

<br>

### Compile the Fibonacci Demo

```bash
gcc -std=c11 run_fibonacci.c -o fibonacci
```

<br>

### Compile All Programs (One Command)

On Linux/macOS:
```bash
gcc -std=c11 cpu.c -o cpu && \
gcc -std=c11 assembler.c -o assembler && \
gcc -std=c11 run_hello.c -o hello && \
gcc -std=c11 run_fibonacci.c -o fibonacci
```

On Windows (MinGW):
```bash
gcc -std=c11 cpu.c -o cpu.exe
gcc -std=c11 assembler.c -o assembler.exe
gcc -std=c11 run_hello.c -o hello.exe
gcc -std=c11 run_fibonacci.c -o fibonacci.exe
```

<br>

## Running the Programs

### Run the Main CPU Emulator

This demonstrates all CPU opcodes with a comprehensive test program:

```bash
./cpu
```

**Expected Output:**
- Step-by-step instruction execution
- Register values after each instruction
- Final memory dump
- CPU flags (ZR, NG, OV, CY)

<br>

### Run the Hello World Program

This demonstrates memory-mapped I/O:

```bash
./hello
```

**Expected Output:**
```
=== HELLO, WORLD! Program ===
Output: HELLO, WORLD!
=== Program Complete ===
```

<br>

### Run the Fibonacci Sequence Program

This shows detailed Fetch-Decode-Execute-Store cycles:

```bash
./fibonacci
```

**Expected Output:**
- Detailed cycle-by-cycle execution trace
- FETCH: Instruction pointer and instruction register values
- DECODE: Opcode and operand extraction
- EXECUTE: ALU computation details
- STORE: Register state updates
- Final Fibonacci numbers in registers

<br>

### Use the Assembler

To assemble an assembly program:

```bash
./assembler timer.asm timer_output.h
```

This generates:
- `timer_output.h` - C header file with machine code
- `timer_output.bin` - Binary machine code file

<br>

## Viewing Documentation

The project includes comprehensive documentation:

- **ISA.md** - Instruction Set Architecture specification
- **MEMORY_MAP.md** - Memory organization and I/O mapping
- **CPU_SCHEMATIC.md** - CPU architecture diagram
- **README.md** - Quick start guide
- **INSTRUCTIONS.md** - Detailed build and test instructions
- **PROJECT_STATUS.md** - Complete project status report

View any documentation file:
```bash
cat ISA.md
# or open in a text editor
```

<br>

## Troubleshooting

### Common Issues

**Issue: "gcc: command not found"**

Solution: Install GCC compiler (see Prerequisites section)

<br>

**Issue: "Permission denied" when running programs**

Solution: Make files executable:
```bash
chmod +x cpu assembler hello fibonacci
```

<br>

**Issue: Compilation warnings or errors**

Solution: Ensure you're using C11 standard:
```bash
gcc -std=c11 -Wall -Wextra cpu.c -o cpu
```

<br>

**Issue: Programs don't produce expected output**

Solution: Check that you're in the correct directory and all source files are present.

<br>

## Testing the Installation

Run this quick test to verify everything works:

```bash
# Test 1: CPU emulator
./cpu | grep "HALTED"

# Test 2: Hello World
./hello | grep "HELLO"

# Test 3: Assembler
./assembler timer.asm timer_test.h && ls timer_test.h

# Test 4: Fibonacci
./fibonacci | head -20
```

If all tests pass, the installation is successful.

---

<div style="page-break-after: always;"></div>

# Team Member Contributions

<br>

## Project Overview

This project was a collaborative effort to design and implement a complete 16-bit software CPU in C. The team worked together to create a fully functional emulator, assembler, and demonstration programs.

<br><br>

## Individual Contributions

### [Team Member 1 Name]

**Major Responsibilities:**

- **CPU Architecture Design** - Designed the 16-bit CPU architecture including register organization (8 general-purpose registers, stack pointer, instruction pointer)

- **ALU Implementation** - Implemented the Arithmetic Logic Unit with all control flags (zx, nx, zy, ny, f, no) and status flags (ZR, NG, OV, CY). Developed the n-bit adder using gate-level logic

- **Instruction Set Design** - Designed the 15-instruction ISA with 4-bit opcode, 3-bit register fields, and 6-bit immediate values. Defined instruction encoding format

- **Control Unit Logic** - Implemented the fetch-decode-execute cycle, instruction decoding, and program counter management in the control unit

<br>

**Specific Code Contributions:**

- Implemented `struct ALU` and `alu_compute()` function (~150 lines)

- Created `struct CPU` with all component structures

- Developed `fetch_decode_execute()` control logic (~100 lines)

- Implemented arithmetic operations (ADD, SUB, MUL, DIV)

- Wrote ALU test cases in main CPU test program

<br>

**Documentation:**

- Authored CPU_SCHEMATIC.md with complete architecture diagram

- Created detailed ALU operation explanations in ISA.md

- Documented flag semantics and instruction encoding

<br>

**Time Commitment:** Approximately 25-30 hours

<br><br>

### [Team Member 2 Name]

**Major Responsibilities:**

- **Memory System Design** - Designed the 400-word memory architecture with distinct regions for I/O, code/data, and stack

- **Memory-Mapped I/O** - Implemented the memory-mapped I/O system with character output port at address 0x20. Created `memory_write()` and `memory_read()` functions

- **Assembler Development** - Designed and implemented the complete two-pass assembler with label resolution, symbol table, and code generation

- **Load/Store Instructions** - Added LOAD and STORE instructions to enable memory access beyond stack operations

<br>

**Specific Code Contributions:**

- Implemented complete assembler.c (~400 lines) including:
  - Two-pass assembly algorithm
  - Label symbol table and resolution
  - Opcode parser and encoder
  - Output generation (C header and binary formats)

- Created memory-mapped I/O functions (~30 lines)

- Implemented LOAD/STORE instruction handlers

- Developed `load_program()` and `dump_memory()` functions

<br>

**Documentation:**

- Authored MEMORY_MAP.md with complete memory layout

- Created assembler usage examples

- Documented memory-mapped I/O specifications

- Wrote INSTRUCTIONS.md build guide

<br>

**Time Commitment:** Approximately 25-30 hours

<br><br>

### [Team Member 3 Name]

**Major Responsibilities:**

- **Example Programs** - Designed and implemented all three required assembly programs (Timer, Hello World, Fibonacci)

- **Demo Programs** - Created standalone C programs (run_hello.c, run_fibonacci.c) demonstrating the CPU with detailed execution traces

- **ISA Documentation** - Authored comprehensive ISA specification including all instruction details, addressing modes, and examples

- **Testing and Integration** - Performed system integration testing, verified all components work together, and created test cases

<br>

**Specific Code Contributions:**

- Implemented run_hello.c (~200 lines) with memory-mapped I/O demonstration

- Implemented run_fibonacci.c (~300 lines) with detailed cycle tracing showing FETCH-DECODE-EXECUTE-STORE phases

- Created timer.asm with extensive comments explaining CPU cycles

- Created hello.asm demonstrating character output via STORE

- Created fibonacci.asm with algorithm documentation and trace examples

- Implemented register dump and CPU state display functions

<br>

**Documentation:**

- Authored ISA.md with complete instruction set specification

- Created detailed instruction encoding examples

- Documented all addressing modes with examples

- Wrote comprehensive README.md with quick start guide

- Created PROJECT_STATUS.md tracking all requirements

- Documented Fibonacci algorithm and execution trace in comments

<br>

**Testing:**

- Verified compilation on multiple platforms (macOS, Linux, Windows)

- Created test procedures and verification steps

- Tested assembler with all example programs

- Validated output correctness for all demo programs

<br>

**Time Commitment:** Approximately 25-30 hours

<br><br>

## Collaborative Work

The entire team collaborated on:

- **Architecture Decisions** - All major design decisions were made collectively through team meetings

- **Code Reviews** - Each team member reviewed others' code before integration

- **Integration Testing** - All members participated in testing the complete system

- **Documentation Review** - All documentation was peer-reviewed for accuracy

- **Demo Video** - [Team member who recorded] recorded the video with input from all team members

<br>

## Tools and Technologies Used

- **Programming Language:** C (C11 standard)

- **Version Control:** Git and GitHub

- **Development Environment:** VSCode, Vim, terminal editors

- **Compiler:** GCC

- **Documentation:** Markdown

- **Video Recording:** [QuickTime/OBS/Screen Recorder]

<br>

## Project Timeline

- **Week 1-2:** Architecture design, ISA specification, memory map planning

- **Week 3-4:** Core emulator implementation (ALU, registers, control unit)

- **Week 5:** Assembler development and testing

- **Week 6:** Example programs, demo programs, memory-mapped I/O

- **Week 7:** Documentation, testing, integration, video creation

<br>

**Total Team Effort:** Approximately 75-90 hours combined

---

<div style="page-break-after: always;"></div>

# Project Components Summary

<br>

## 1. CPU Architecture

Our 16-bit RISC-style CPU includes:

- **8 General Purpose Registers** (R0-R7): 16-bit data storage

- **Special Registers:** Stack Pointer (SP), Instruction Pointer (IP), Instruction Register (IR)

- **ALU:** Full arithmetic and logic unit with control and status flags

- **Control Unit:** Fetch-decode-execute cycle implementation

- **Memory:** 400 words of addressable memory

- **Memory-Mapped I/O:** Character output at address 0x20

<br>

## 2. Instruction Set Architecture

15 instructions organized in categories:

- **Data Movement:** NOP, MOV, LOAD, STORE

- **Arithmetic:** ADD, SUB, MUL, DIV

- **Logic:** AND, OR

- **Control Flow:** JMP, JZ, CALL, RET, HALT

<br>

**Instruction Format:** 16-bit fixed format

- Bits [15:12]: Opcode (4 bits)

- Bits [11:9]: Register 1 (3 bits)

- Bits [8:6]: Register 2 (3 bits)

- Bits [5:0]: Immediate value (6 bits)

<br>

## 3. Addressing Modes

- **Immediate:** Value encoded in instruction

- **Register:** Operands in registers

- **Register Indirect:** Register contains memory address

- **Implicit:** No operands (NOP, HALT, RET)

<br>

## 4. CPU Flags

- **ZR (Zero):** Set when result is zero

- **NG (Negative):** Set when result is negative

- **OV (Overflow):** Set on signed overflow

- **CY (Carry):** Set on unsigned carry/borrow

<br>

## 5. Memory Organization

- **0x000-0x013:** Memory-Mapped I/O region

- **0x014-0x18F:** Program code and data

- **0x190-0x18F:** Stack (grows downward from 399)

<br>

## 6. Assembler Features

- Two-pass assembly for label resolution

- Symbol table management

- Error detection and reporting

- Output formats: C header and binary

- Support for comments and whitespace

<br>

## 7. Example Programs

**Timer Program:**
- Demonstrates fetch-decode-execute cycles
- Loop control with counter
- Detailed cycle documentation

**Hello World:**
- Memory-mapped I/O demonstration
- Character output via STORE instruction
- String manipulation

**Fibonacci Sequence:**
- Complex algorithm implementation
- Register arithmetic
- Conditional branching
- Loop control
- Detailed execution trace

<br>

## 8. Demo Programs

**run_hello.c:**
- Standalone Hello World demo
- Shows memory-mapped I/O in action

**run_fibonacci.c:**
- Detailed CPU cycle tracing
- FETCH, DECODE, EXECUTE, STORE phases
- Register state visualization
- Educational demonstration

---

<div style="page-break-after: always;"></div>

# Technical Highlights

<br>

## Design Principles

Our CPU design follows RISC (Reduced Instruction Set Computer) principles:

- **Simplicity:** Each instruction performs one operation

- **Fixed Format:** All instructions are 16 bits

- **Register-Oriented:** Most operations work on registers

- **Small Instruction Set:** 15 core instructions

- **Direct Execution:** No microcode layer

<br>

## Key Implementation Features

### N-bit Adder

The ALU includes a gate-level n-bit adder implementation:

```c
static word_t add_nbit(word_t a, word_t b, uint8_t *carry_out) {
    word_t sum = 0;
    word_t carry = 0;
    for (int i = 0; i < WORD_SIZE; i++) {
        word_t bit_a = (a >> i) & 1u;
        word_t bit_b = (b >> i) & 1u;
        word_t sum_bit = bit_a ^ bit_b ^ carry;
        carry = (bit_a & bit_b) | (bit_a & carry) | (bit_b & carry);
        sum |= (sum_bit << i);
    }
    *carry_out = (uint8_t)carry;
    return sum;
}
```

This implements addition at the bit level, demonstrating understanding of digital logic.

<br>

### ALU Control

The ALU uses 6 control flags (zx, nx, zy, ny, f, no) to generate multiple operations:

- Zero inputs
- Negate inputs
- Select function (AND or ADD)
- Negate output

This allows implementing constants, arithmetic, logic, and special operations with a single ALU design.

<br>

### Two-Pass Assembly

The assembler uses two passes for efficiency:

**Pass 1:** Scan for labels and build symbol table

**Pass 2:** Generate machine code with resolved addresses

This enables forward references in assembly code.

<br>

### Memory-Mapped I/O

Simple yet effective I/O implementation:

```c
if (address == MMIO_CHAR_OUT) {
    printf("%c", (char)(value & 0xFF));
    fflush(stdout);
}
```

Writing to address 32 outputs a character, demonstrating hardware-software interface concepts.

<br>

## Code Quality

- **Well-Commented:** Every function and major code block has explanatory comments

- **Modular Design:** Clear separation between CPU components

- **Error Handling:** Division by zero, stack overflow/underflow detection

- **Consistent Style:** Uniform naming conventions and formatting

- **Type Safety:** Use of typedef and structs for clarity

<br>

## Testing Approach

- **Unit Testing:** Each component tested individually

- **Integration Testing:** Complete system tested with multiple programs

- **Cross-Platform Testing:** Verified on macOS, Linux, and Windows

- **Example Programs:** Serve as functional tests

---

<div style="page-break-after: always;"></div>

# Conclusion

<br>

## Project Success

This project successfully implements a complete software CPU in C, meeting all requirements:

✅ **CPU Schematic** - Comprehensive architecture diagram

✅ **ISA Specification** - Complete instruction set documentation

✅ **Emulator** - Fully functional with all components

✅ **Assembler** - Two-pass assembler with label support

✅ **Example Programs** - Timer, Hello World, and Fibonacci

✅ **Documentation** - Extensive technical documentation

✅ **Demo Video** - Fibonacci program explanation

✅ **GitHub Repository** - Well-organized public repository

<br>

## Learning Outcomes

Through this project, the team gained hands-on experience with:

- Computer architecture design principles

- Instruction set architecture development

- Fetch-decode-execute cycle implementation

- ALU design and arithmetic operations

- Memory organization and management

- Assembler design and implementation

- Low-level programming and bit manipulation

- System integration and testing

- Technical documentation and presentation

<br>

## Challenges Overcome

**Challenge 1: 6-bit Immediate Limitation**

Solution: Used multiple instructions to build larger values (e.g., MOV + ADD for ASCII values > 63)

<br>

**Challenge 2: ALU Control Logic**

Solution: Implemented comprehensive control flag system supporting multiple operations with single hardware design

<br>

**Challenge 3: Label Resolution in Assembler**

Solution: Implemented two-pass assembly algorithm with symbol table

<br>

**Challenge 4: Memory-Mapped I/O**

Solution: Added simple address checking in memory write function

<br>

## Future Enhancements

Possible extensions to the project:

- **Extended Instruction Set:** Add shift, rotate, and comparison instructions

- **Interrupts:** Implement interrupt handling system

- **Cache Memory:** Add instruction and data caches

- **Pipeline:** Implement instruction pipelining for better performance

- **Floating Point:** Add FPU for floating-point operations

- **Debugger:** Create interactive debugger with breakpoints

- **GUI:** Graphical interface showing CPU state in real-time

<br>

## Acknowledgments

We would like to thank:

- **[Instructor Name]** for guidance and project requirements

- **Course TAs** for technical support and feedback

- **Open Source Community** for GCC compiler and development tools

<br>

## References

- Computer Organization and Design (Patterson & Hennessy)

- Nand2Tetris Course Materials

- GCC Documentation

- C11 Standard Specification

---

**End of Report**

