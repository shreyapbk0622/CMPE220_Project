# CMPE220 CPU Project - Video Recording Script

**Total Time: 8-10 minutes**

---

## BEFORE YOU START

1. **Start screen recording** (Cmd+Shift+5 on Mac, Windows+G on Windows)
2. **Select microphone** in recording options
3. **Open Terminal** - Make it full screen
4. **Increase font size** - Cmd/Ctrl + Plus (+) several times
5. **Clear screen** - Type `clear`
6. **Start recording!**

---

## 📝 PART 1: INTRODUCTION (30 seconds)

### SAY:
```
"Hello, I'm [Your Name] presenting the CMPE220 CPU Design project.
Today I'll demonstrate our 16-bit software CPU implementation in C.
I'll show you how to run the Fibonacci program and explain the
Fetch-Decode-Execute-Store cycle that powers our CPU."
```

### DO:
Nothing yet - just introduce yourself

---

## 📝 PART 2: CLONE & SETUP (1 minute)

### SAY:
```
"First, let me clone the repository from GitHub and navigate to the project."
```

### TYPE & RUN:
```bash
git clone https://github.com/shreyapbk0622/CMPE220_Project.git
cd CMPE220_Project
git checkout complete-cpu-implementation
```

### SAY:
```
"Let me show you the project structure."
```

### TYPE & RUN:
```bash
ls -la
```

### SAY:
```
"As you can see, we have:
- The CPU emulator in cpu.c
- An assembler in assembler.c  
- Example programs including fibonacci.asm
- Complete documentation in markdown files"
```

---

## 📝 PART 3: SHOW DOCUMENTATION (1 minute)

### SAY:
```
"Let me briefly show you our CPU architecture."
```

### TYPE & RUN:
```bash
cat ISA.md | head -50
```

### SAY (while scrolling slowly):
```
"Our CPU features:
- 8 general-purpose registers R0 through R7
- 16-bit instruction format
- 15 instructions including arithmetic, logic, and control flow
- An ALU with status flags for zero, negative, overflow, and carry"
```

### TYPE:
```bash
clear
```

---

## 📝 PART 4: SHOW FIBONACCI CODE (1 minute)

### SAY:
```
"Now let me show you the Fibonacci assembly program."
```

### TYPE & RUN:
```bash
cat fibonacci.asm | head -60
```

### SAY (point to screen):
```
"The Fibonacci program uses:
- Register R0 to store F(n-2)
- Register R1 to store F(n-1)
- Register R2 as a counter
- It loops to compute successive Fibonacci numbers
- Uses ADD instructions for arithmetic
- Uses conditional jumps for loop control"
```

### TYPE:
```bash
clear
```

---

## 📝 PART 5: COMPILE THE PROGRAM (30 seconds)

### SAY:
```
"Now I'll compile the Fibonacci demonstration program."
```

### TYPE & RUN:
```bash
gcc -std=c11 run_fibonacci.c -o fibonacci
```

### SAY:
```
"Compilation successful! This demo program shows detailed
CPU cycle information as the Fibonacci sequence executes."
```

---

## 📝 PART 6: RUN & EXPLAIN CYCLES (4-5 minutes) ⭐ MOST IMPORTANT

### SAY:
```
"Let's run the program and watch the CPU cycles."
```

### TYPE & RUN:
```bash
./fibonacci | head -80
```

### PAUSE - Let output show, then explain:

---

### 🔵 EXPLAIN CYCLE 0 (First instruction)

**POINT TO THIS LINE:**
```
[Cycle 0] FETCH: IP=0, IR=0x1001
```

### SAY:
```
"Let's look at Cycle 0 - the first instruction.

In the FETCH phase:
- The CPU reads from memory at address 0 (that's the IP - Instruction Pointer)
- The instruction is loaded into the IR - Instruction Register
- The value 0x1001 is our encoded instruction
- The IP automatically increments to 1 for the next instruction"
```

---

**POINT TO THIS LINE:**
```
DECODE: OP=MOV, R1=0, R2=0, IMM=1
```

### SAY:
```
"In the DECODE phase:
- The CPU extracts the opcode - which is MOV
- It extracts R1 which is register 0
- And the immediate value which is 1
- This instruction means: Move value 1 into Register 0"
```

---

**POINT TO THIS LINE:**
```
EXECUTE: R0 = 1
```

### SAY:
```
"In the EXECUTE phase:
- The MOV operation happens
- Register 0 gets the value 1
- No ALU computation needed for a simple MOV"
```

---

**POINT TO THIS LINE:**
```
STORE: Registers: R0=1 R1=0 R2=0 R3=0...
```

### SAY:
```
"In the STORE phase:
- We can see the updated register state
- R0 now contains 1
- All other registers are still 0
- The IP has moved to 1, ready for the next instruction

This is one complete CPU cycle: Fetch, Decode, Execute, Store."
```

---

### 🟢 EXPLAIN AN ADD INSTRUCTION

**SCROLL DOWN to find an ADD instruction, POINT TO IT:**
```
[Cycle 5] FETCH: IP=5, IR=0x2802
          DECODE: OP=ADD, R1=4, R2=0, IMM=2
          EXECUTE: R4 = 0 + 2 = 2
          STORE: Registers: R0=1 R1=1 R2=0 R3=8 R4=2...
```

### SAY:
```
"Here's an ADD instruction - this is where Fibonacci computation happens.

FETCH: Read instruction from address 5
DECODE: It's an ADD operation - add 2 to register R4
EXECUTE: The ALU performs addition - R4 = 0 + 2 = 2
STORE: R4 now contains 2

The ALU also updates flags like the Zero flag and Carry flag
based on the result of the addition."
```

---

### 🟡 EXPLAIN A CONDITIONAL JUMP

**SCROLL to find JZ instruction, POINT TO IT:**
```
DECODE: OP=JZ, R1=0, R2=0, IMM=15
EXECUTE: No jump (ZR=0)
```

### SAY:
```
"This is a conditional jump - JZ means Jump if Zero.

The CPU checks the Zero flag from the previous operation.
If ZR is 1, it jumps to address 15.
If ZR is 0, like here, it continues to the next instruction.

This is how we implement loops and conditional logic."
```

---

### 🔴 EXPLAIN THE LOOP

### SAY:
```
"As you can see, the program keeps looping through these instructions:
- Initialize values
- Add to compute next Fibonacci number
- Check if we're done
- If not, jump back and repeat

Each iteration computes the next number in the Fibonacci sequence.
You can see R0 and R1 changing with each loop iteration."
```

---

**SCROLL TO THE END:**

### SAY:
```
"At the end, we see the HALT instruction which stops the CPU.
The final register state shows the computed Fibonacci numbers.

This demonstrates all the key features:
- Fetch-Decode-Execute-Store cycle
- Register operations
- ALU arithmetic
- Conditional branching
- Loop control"
```

---

## 📝 PART 7: SHOW HELLO WORLD (OPTIONAL - 1 minute)

### TYPE:
```bash
clear
gcc -std=c11 run_hello.c -o hello
./hello
```

### SAY:
```
"Here's another example - our Hello World program using memory-mapped I/O.
When we write to memory address 32, the character is output to the console.
This demonstrates how our CPU interfaces with I/O devices."
```

---

## 📝 PART 8: SHOW ASSEMBLER (OPTIONAL - 1 minute)

### TYPE:
```bash
gcc -std=c11 assembler.c -o assembler
./assembler fibonacci.asm fib_output.h
cat fib_output.h | head -20
```

### SAY:
```
"We also built an assembler that converts assembly language
into machine code that our CPU can execute.
Here you can see the assembled instructions in hexadecimal format."
```

---

## 📝 PART 9: CONCLUSION (30 seconds)

### SAY:
```
"To summarize, our CMPE220 project includes:

1. A complete 16-bit CPU emulator with:
   - 8 registers
   - A full ALU with arithmetic and logic operations
   - A control unit implementing the Fetch-Decode-Execute-Store cycle
   - 400 words of memory
   - Memory-mapped I/O

2. An assembler with label support and symbol table

3. Example programs: Timer, Hello World, and Fibonacci

All source code, documentation, and this video are available
on our GitHub repository.

Thank you for watching!"
```

---

## 🛑 STOP RECORDING

Press the stop button in your screen recorder.

---

## ✅ REVIEW CHECKLIST

After recording, verify you showed:

- [x] Repository cloning
- [x] Project structure (ls command)
- [x] ISA documentation
- [x] Fibonacci assembly code
- [x] Compilation (gcc command)
- [x] Program execution
- [x] FETCH phase explanation
- [x] DECODE phase explanation
- [x] EXECUTE phase explanation  
- [x] STORE phase explanation
- [x] At least 2-3 different instruction types (MOV, ADD, JZ/JMP)
- [x] Register state changes
- [x] Flags being updated
- [x] Loop iteration
- [x] Final results

---

## 📤 AFTER RECORDING

1. **Save video** to Desktop/Videos folder

2. **Upload to YouTube:**
   - Go to youtube.com
   - Click camera icon → "Upload video"
   - Title: "CMPE220 CPU Project - Fibonacci Demonstration"
   - Description: "Software CPU implementation with detailed cycle explanation"
   - Visibility: **Unlisted** (only people with link can view)
   - Publish

3. **Copy the YouTube link**

4. **Add to your project:**
   ```bash
   cd CMPE220_Project
   # Edit PROJECT_REPORT.md
   # Replace [INSERT VIDEO LINK HERE] with your YouTube URL
   
   git add PROJECT_REPORT.md
   git commit -m "Add demo video link"
   git push origin complete-cpu-implementation
   ```

---

## 💡 TIPS FOR RECORDING

**DO:**
- Speak slowly and clearly
- Pause between commands to let output display
- Point out specific lines on screen ("as you can see here...")
- Explain what each phase does
- Show enthusiasm!

**DON'T:**
- Rush through explanations
- Mumble or speak too quietly
- Skip the Fetch-Decode-Execute-Store explanation
- Forget to show the program actually running
- Go over 10 minutes (aim for 8-9 minutes)

---

## 🎯 KEY PHRASES TO USE

- "In the FETCH phase, the CPU reads..."
- "During DECODE, we extract..."
- "The EXECUTE phase performs..."
- "Finally, STORE updates the registers..."
- "Notice how the IP increments..."
- "The ALU computes..."
- "The Zero flag is set when..."
- "This loop continues until..."
- "You can see register R0 changing from..."

---

**YOU'RE READY! Just follow this script and you'll have a great demo video! 🎥**
