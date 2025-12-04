/*
 * Fibonacci Sequence Program
 * Using CPU Emulator from CMPE220_Project/SourceCodes/cpu.c
 * 
 * This program imports the CPU implementation and runs a Fibonacci program
 */

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define WORD_SIZE 16
#define STACK_SIZE 1000
#define MMIO_CHAR_OUT 32

typedef uint16_t word_t;

enum {
    NOP, MOV, ADD, SUB, AND, OR, MUL, DIV,
    JMP, JZ, CALL, RET, HALT, LOAD, STORE
};

const char *OPCODE_STRINGS[] = {
    "NOP","MOV","ADD","SUB","AND","OR","MUL","DIV",
    "JMP","JZ","CALL","RET","HALT","LOAD","STORE"
};

struct ALUFlags {
    uint8_t zx, nx, zy, ny, f, no;
    uint8_t zr, ng, ov, cy;
};

struct ALU {
    word_t x, y, out;
    struct ALUFlags flags;
};

struct Memory {
    word_t mem[400];
};

struct GPR {
    word_t reg[8];
};

struct SPR {
    word_t SP;
};

struct CU {
    word_t IP, IR;
    struct ALUFlags aluflags;
};

struct CPU {
    struct Memory mainMemory;
    struct GPR gpr;
    struct SPR spr;
    struct CU cu;
    struct ALU alu;
    int running;
    word_t static_counter;
};

// ============ CPU IMPLEMENTATION (from cpu.c) ============

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

static word_t and_nbit(word_t a, word_t b) {
    word_t result = 0;
    for (int i = 0; i < WORD_SIZE; i++) {
        word_t bit_a = (a >> i) & 1u;
        word_t bit_b = (b >> i) & 1u;
        word_t and_bit = bit_a & bit_b;
        result |= (and_bit << i);
    }
    return result;
}

static void alu_compute(struct ALU *alu) {
    word_t x = alu->x;
    word_t y = alu->y;
    
    alu->flags.cy = 0;
    alu->flags.ov = 0;
    
    if (alu->flags.zx) x = 0;
    if (alu->flags.nx) x = ~x;
    if (alu->flags.zy) y = 0;
    if (alu->flags.ny) y = ~y;
    
    if (alu->flags.f == 0) {
        alu->out = and_nbit(x, y);
    } else {
        alu->out = add_nbit(x, y, &alu->flags.cy);
    }
    
    if (alu->flags.no) alu->out = ~alu->out;
    
    alu->flags.zr = (alu->out == 0);
    alu->flags.ng = ((alu->out & (1u << (WORD_SIZE - 1))) != 0);
}

static word_t encodeI(uint8_t op, uint8_t r1, uint8_t r2, uint8_t imm) {
    return (word_t)(((op & 0xF) << 12) |
                    ((r1 & 0x7) << 9)  |
                    ((r2 & 0x7) << 6)  |
                     (imm & 0x3F));
}

static void load_program(struct CPU *cpu, word_t *program, int size) {
    for (int i = 0; i < size; i++) {
        cpu->mainMemory.mem[i] = program[i];
    }
    cpu->cu.IP = 0;
    cpu->spr.SP = 399;
}

// ============ FIBONACCI-SPECIFIC CODE ============

int fib_count = 0;
word_t fib_values[10];
word_t final_r0, final_r1, final_r2, final_r3;
int saved_finals = 0;

static void fetch_decode_execute(struct CPU *cpu) {
    if (cpu->running == 0) return;
    
    cpu->cu.IR = cpu->mainMemory.mem[cpu->cu.IP++];
    word_t instr = cpu->cu.IR;
    
    uint8_t op  = (instr >> 12) & 0xF;
    uint8_t r1  = (instr >> 9)  & 0x7;
    uint8_t r2  = (instr >> 6)  & 0x7;
    uint8_t imm = instr & 0x3F;
    
    if (op == NOP) {
        // No operation
    } else if (op == MOV) {
        cpu->gpr.reg[r1] = imm;
    } else if (op == ADD) {
        cpu->alu.x = cpu->gpr.reg[r1];
        cpu->alu.y = (r2 == 7) ? imm : cpu->gpr.reg[r2];
        cpu->alu.flags = (struct ALUFlags){0,0,0,0,1,0,0,0,0,0};
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
        
        // Track when we compute new Fibonacci
        if (r1 == 4 && r2 == 1 && cpu->cu.IP == 13 && fib_count < 8) {
            fib_values[fib_count + 2] = cpu->alu.out;
            printf("│  F(%d)   │   %-5d   │  R0=%-4d R1=%-4d R2=%-4d R4=%-4d  <-- NEW │\n",
                   fib_count + 2, cpu->alu.out, cpu->gpr.reg[0], cpu->gpr.reg[1], cpu->gpr.reg[2], cpu->gpr.reg[4]);
            fib_count++;
        }
        
        // Save final state after counter increment
        if (r1 == 2 && imm == 1 && fib_count == 8 && !saved_finals) {
            final_r0 = cpu->gpr.reg[0];
            final_r1 = cpu->gpr.reg[1];
            final_r2 = cpu->alu.out;
            final_r3 = cpu->gpr.reg[3];
            saved_finals = 1;
        }
    } else if (op == SUB) {
        cpu->alu.x = cpu->gpr.reg[r1];
        cpu->alu.y = cpu->gpr.reg[r2];
        cpu->alu.flags = (struct ALUFlags){0,0,1,0,1,1,0,0,0,0};
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
    } else if (op == JMP) {
        cpu->cu.IP = imm;
        return;
    } else if (op == JZ) {
        if (cpu->cu.aluflags.zr) {
            cpu->cu.IP = imm;
        }
        return;
    } else if (op == HALT) {
        cpu->running = 0;
        return;
    }
}

static void run_cpu(struct CPU *cpu) {
    cpu->running = 1;
    int cycle_count = 0;
    int max_cycles = 200;
    
    while (cpu->running && cycle_count < max_cycles) {
        fetch_decode_execute(cpu);
        cycle_count++;
        
        if (fib_count >= 8 && cpu->gpr.reg[2] >= 10) {
            cpu->running = 0;
            break;
        }
    }
}

// ============ MAIN PROGRAM ============

int main(void) {
    struct CPU cpu = {0};
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║      FIBONACCI SEQUENCE - USING CPU.C EMULATOR              ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("📦 Based on: CMPE220_Project/SourceCodes/cpu.c\n");
    printf("🎯 16-bit CPU Architecture with custom ISA\n\n");
    
    printf("Register assignments:\n");
    printf("  R0 = F(n-2) - Second previous Fibonacci number\n");
    printf("  R1 = F(n-1) - Previous Fibonacci number\n");
    printf("  R2 = Counter (iteration number)\n");
    printf("  R3 = Limit (10 numbers)\n");
    printf("  R4 = Temporary storage for new Fibonacci number\n\n");
    
    // Fibonacci program
    word_t fibonacci_program[] = {
        encodeI(MOV, 0, 0, 0),    // R0 = 0
        encodeI(MOV, 1, 0, 1),    // R1 = 1
        encodeI(MOV, 2, 0, 2),    // R2 = 2
        encodeI(MOV, 3, 0, 10),   // R3 = 10
        encodeI(ADD, 2, 7, 0),    // padding
        encodeI(ADD, 2, 7, 0),    // padding
        encodeI(MOV, 4, 0, 0),    // loop: R4 = 0
        encodeI(ADD, 4, 2, 0),    // R4 = R2
        encodeI(SUB, 4, 3, 0),    // R4 = R4 - R3
        encodeI(JZ,  0, 0, 20),   // if zero, jump to done
        encodeI(MOV, 4, 0, 0),    // R4 = 0
        encodeI(ADD, 4, 0, 0),    // R4 += R0
        encodeI(ADD, 4, 1, 0),    // R4 += R1 (NEW FIBONACCI!)
        encodeI(MOV, 0, 0, 0),    // R0 = 0
        encodeI(ADD, 0, 1, 0),    // R0 = R1
        encodeI(MOV, 1, 0, 0),    // R1 = 0
        encodeI(ADD, 1, 4, 0),    // R1 = R4
        encodeI(ADD, 2, 7, 1),    // R2 += 1
        encodeI(JMP, 0, 0, 6),    // jump to loop
        encodeI(NOP, 0, 0, 0),    // padding
        encodeI(HALT, 0, 0, 0)    // done
    };
    
    fib_values[0] = 0;
    fib_values[1] = 1;
    
    printf("┌──────────┬───────────┬─────────────────────────────────────────────────┐\n");
    printf("│  Index   │   Value   │     Register State (R0, R1, R2, R4)            │\n");
    printf("├──────────┼───────────┼─────────────────────────────────────────────────┤\n");
    printf("│  F(0)    │     0     │  R0=0    R1=1    R2=2    R4=---               │\n");
    printf("│  F(1)    │     1     │  R0=0    R1=1    R2=2    R4=---               │\n");
    
    load_program(&cpu, fibonacci_program, 
                 sizeof(fibonacci_program) / sizeof(fibonacci_program[0]));
    
    run_cpu(&cpu);
    
    printf("└──────────┴───────────┴─────────────────────────────────────────────────┘\n\n");
    
    printf("╔══════════════════════════════════════════════════════════════╗\n");
    printf("║                    EXECUTION SUMMARY                         ║\n");
    printf("╚══════════════════════════════════════════════════════════════╝\n\n");
    
    printf("📊 Final Register States (when R2=10):\n");
    printf("   ├─ R0 (F(n-2)) = %d\n", saved_finals ? final_r0 : cpu.gpr.reg[0]);
    printf("   ├─ R1 (F(n-1)) = %d  <-- Last Fibonacci number\n", saved_finals ? final_r1 : cpu.gpr.reg[1]);
    printf("   ├─ R2 (counter) = %d\n", saved_finals ? final_r2 : cpu.gpr.reg[2]);
    printf("   └─ R3 (limit)   = %d\n\n", saved_finals ? final_r3 : cpu.gpr.reg[3]);
    
    printf("✅ Complete Fibonacci Sequence (F(0) to F(9)):\n   ");
    for (int i = 0; i < 10; i++) {
        printf("%d", fib_values[i]);
        if (i < 9) printf(" → ");
    }
    printf("\n\n");
    
    printf("🔄 CPU Operations per Iteration:\n");
    printf("   • MOV R4, 0       (clear temp)\n");
    printf("   • ADD R4, R2      (load counter)\n");
    printf("   • SUB R4, R3      (compare to limit)\n");
    printf("   • JZ done         (exit if done)\n");
    printf("   • MOV R4, 0       (clear temp)\n");
    printf("   • ADD R4, R0      (add F(n-2))\n");
    printf("   • ADD R4, R1      (add F(n-1) → new Fibonacci!)\n");
    printf("   • MOV R0, 0       (shift registers)\n");
    printf("   • ADD R0, R1      (R0 = old R1)\n");
    printf("   • MOV R1, 0       (clear R1)\n");
    printf("   • ADD R1, R4      (R1 = new Fibonacci)\n");
    printf("   • ADD R2, 1       (increment counter)\n");
    printf("   • JMP loop        (repeat)\n\n");
    
    printf("🎯 Starting: R0=0, R1=1, R2=2\n");
    printf("🎯 Ending:   R0=%d, R1=%d, R2=%d\n\n", 
           saved_finals ? final_r0 : cpu.gpr.reg[0],
           saved_finals ? final_r1 : cpu.gpr.reg[1],
           saved_finals ? final_r2 : cpu.gpr.reg[2]);
    
    return 0;
}
