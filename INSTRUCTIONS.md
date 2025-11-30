# Build and Run Instructions

## Quick Setup

### Step 1: Verify Files
Ensure all files are present in the project directory:
```bash
ls -la
```

You should see:
- cpu.c
- assembler.c
- run_hello.c
- run_fibonacci.c
- timer.asm, hello.asm, fibonacci.asm
- ISA.md, MEMORY_MAP.md, CPU_SCHEMATIC.md
- README.md

### Step 2: Compile All Programs

**Compile main CPU emulator:**
```bash
gcc -std=c11 cpu.c -o cpu
```

**Compile assembler:**
```bash
gcc -std=c11 assembler.c -o assembler
```

**Compile Hello World demo:**
```bash
gcc -std=c11 run_hello.c -o hello
```

**Compile Fibonacci demo:**
```bash
gcc -std=c11 run_fibonacci.c -o fibonacci
```

### Step 3: Run Programs

**1. Run the main CPU test program:**
```bash
./cpu
```
This demonstrates all opcodes including arithmetic, logic, jumps, and subroutine calls.

**2. Run Hello World:**
```bash
./hello
```
Expected output: `HELLO, WORLD!`

**3. Run Fibonacci with detailed execution trace:**
```bash
./fibonacci
```
This shows Fetch-Decode-Execute-Store cycles and computes Fibonacci numbers.

**4. Use the assembler:**
```bash
./assembler hello.asm hello_out.h
./assembler fibonacci.asm fib_out.h
./assembler timer.asm timer_out.h
```

## Understanding the Output

### CPU Test Program
Shows execution of each instruction with:
- Register values after each instruction
- Stack pointer (SP) and instruction pointer (IP)
- CPU flags (ZR, NG, OV, CY)
- Final memory dump

### Hello World
Simply outputs the text using memory-mapped I/O.

### Fibonacci Program
Detailed trace showing:
- **FETCH**: Reading instruction from memory
- **DECODE**: Extracting opcode and operands
- **EXECUTE**: Computing the result
- **STORE**: Writing to registers/memory

## Troubleshooting

### Compilation Errors

**Error: "gcc not found"**
- Install GCC:
  - Mac: `xcode-select --install`
  - Linux: `sudo apt-get install gcc`
  - Windows: Install MinGW-w64

**Error: "cpu.c: No such file or directory"**
- Make sure you're in the correct directory
- Use `cd` to navigate to the project folder

### Runtime Errors

**Segmentation fault**
- Usually means array out of bounds
- Check that programs don't exceed 400 words of memory

**No output from Hello World**
- Check that memory-mapped I/O is implemented
- Verify MMIO_CHAR_OUT is defined as 32

## Testing Checklist

- [ ] cpu.c compiles without errors
- [ ] assembler.c compiles without errors  
- [ ] run_hello.c compiles without errors
- [ ] run_fibonacci.c compiles without errors
- [ ] ./cpu runs and shows register/memory dump
- [ ] ./hello outputs "HELLO, WORLD!"
- [ ] ./fibonacci shows Fibonacci sequence computation
- [ ] ./assembler can parse .asm files

## Next Steps

1. **Create demo video:**
   - Record screen showing Fibonacci program execution
   - Explain Fetch-Decode-Execute-Store cycle
   - Show register values changing

2. **Update report:**
   - Add GitHub repository URL
   - Add video link
   - List team member contributions

3. **Push to GitHub:**
   ```bash
   git init
   git add .
   git commit -m "Complete CPU implementation"
   git remote add origin <your-repo-url>
   git push -u origin main
   ```

## For Grading

Instructor can verify:
1. Code compiles with single command
2. Programs run successfully
3. Output is correct
4. All required components present:
   - ✅ CPU Schematic (CPU_SCHEMATIC.md)
   - ✅ ISA Documentation (ISA.md)
   - ✅ Memory Map (MEMORY_MAP.md)
   - ✅ Emulator (cpu.c with registers, ALU, CU, memory, MMIO)
   - ✅ Assembler (assembler.c with labels and literals)
   - ✅ Timer Program (timer.asm)
   - ✅ Hello World (hello.asm, run_hello.c)
   - ✅ Fibonacci (fibonacci.asm, run_fibonacci.c)
   - ✅ Report (220 project report.pdf)
