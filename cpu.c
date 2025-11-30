#include <stdio.h>
#include <stdint.h>

#define WORD_SIZE 16
#define STACK_SIZE 1000

typedef uint16_t word_t;

enum {
    NOP, MOV, ADD, SUB, AND, OR, MUL, DIV,
    JMP, JZ, CALL, RET, HALT
};

const char *OPCODE_STRINGS[] = {
    "NOP","MOV","ADD","SUB","AND","OR","MUL","DIV",
    "JMP","JZ","CALL","RET","HALT"
};

struct ALUFlags {
    uint8_t zx, nx, zy, ny, f, no;   // control flags
    uint8_t zr, ng, ov, cy;          // status flags
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
    word_t static_counter;   // recursion depth tracker
};

/* ---------------- N-bit helpers ---------------- */

// N-bit adder implementation
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

// N-bit OR implementation
static word_t or_nbit(word_t a, word_t b) {
    word_t result = 0;

    for (int i = 0; i < WORD_SIZE; i++) {
        word_t bit_a = (a >> i) & 1u;
        word_t bit_b = (b >> i) & 1u;

        word_t or_bit = bit_a | bit_b;
        result |= (or_bit << i);
    }

    return result;
}

/* ---------------- ALU core ---------------- */

static void alu_compute(struct ALU *alu) {
    word_t x = alu->x;
    word_t y = alu->y;

    alu->flags.cy = 0;
    alu->flags.ov = 0;

    if (alu->flags.zx) x = 0;
    if (alu->flags.zy) y = 0;
    if (alu->flags.nx) x = (word_t)~x;
    if (alu->flags.ny) y = (word_t)~y;

    uint8_t d = (uint8_t)((alu->flags.zx << 5) |
                          (alu->flags.nx << 4) |
                          (alu->flags.zy << 3) |
                          (alu->flags.ny << 2) |
                          (alu->flags.f  << 1) |
                           alu->flags.no);

    if (d == 0b101010) {
        alu->out = 0;
    } else if (d == 0b111111) {
        alu->out = 1;
    } else if (d == 0b111010) {
        alu->out = (word_t)-1;
    } else if (d == 0b001100) {
        alu->out = x;
    } else if (d == 0b110000) {
        alu->out = y;
    } else if (d == 0b001101) {
        alu->out = (word_t)~x;
    } else if (d == 0b110001) {
        alu->out = (word_t)~y;
    } else if (d == 0b001111) {
        alu->out = (word_t)(-((int16_t)x));
    } else if (d == 0b110011) {
        alu->out = (word_t)(-((int16_t)y));
    } else if (d == 0b011111) {
        uint8_t carry;
        alu->out = add_nbit(x, 1, &carry);
        alu->flags.cy = carry;
    } else if (d == 0b110111) {
        uint8_t carry;
        alu->out = add_nbit(y, 1, &carry);
        alu->flags.cy = carry;
    } else if (d == 0b001110) {
        alu->out = (word_t)(x - 1);
    } else if (d == 0b110010) {
        alu->out = (word_t)(y - 1);
    } else if (d == 0b000010) { // Addition (x + y)
        uint8_t carry;
        alu->out = add_nbit(x, y, &carry);
        alu->flags.cy = carry;

        int16_t sx   = (int16_t)x;
        int16_t sy   = (int16_t)y;
        int16_t sres = (int16_t)alu->out;

        alu->flags.ov = ((sx > 0 && sy > 0 && sres < 0) ||
                         (sx < 0 && sy < 0 && sres > 0));
    } else if (d == 0b010011) { // Subtraction x - y
        int16_t sx   = (int16_t)x;
        int16_t sy   = (int16_t)y;
        int16_t sres = (int16_t)(sx - sy);

        alu->out = (word_t)sres;
        alu->flags.cy = (sx < sy);
        alu->flags.ov = ((sx > 0 && sy < 0 && sres < 0) ||
                         (sx < 0 && sy > 0 && sres > 0));
    } else if (d == 0b000111) { // Subtraction y - x
        int16_t sx   = (int16_t)x;
        int16_t sy   = (int16_t)y;
        int16_t sres = (int16_t)(sy - sx);

        alu->out = (word_t)sres;
        alu->flags.cy = (sy < sx);
        alu->flags.ov = ((sy > 0 && sx < 0 && sres < 0) ||
                         (sy < 0 && sx > 0 && sres > 0));
    } else if (d == 0b000000) { // AND
        alu->out = x & y;
        alu->flags.cy = 0;
        alu->flags.ov = 0;
    } else if (d == 0b010101) { // OR
        alu->out = or_nbit(x, y);
        alu->flags.cy = 0;
        alu->flags.ov = 0;
    } else if (d == 0b111100) { // Multiplication
        uint32_t prod = (uint32_t)x * (uint32_t)y;
        alu->out = (word_t)prod;
        alu->flags.cy = (prod > 0xFFFFu);
        alu->flags.ov = alu->flags.cy;
    } else if (d == 0b111101) { // Division
        if (y == 0) {
            printf("Error: Division by zero. CPU Halting.\n");
            alu->out = 0;
            alu->flags.cy = 0;
            alu->flags.ov = 1;
        } else {
            alu->out = (word_t)(x / y);
            alu->flags.cy = 0;
            alu->flags.ov = 0;
        }
    } else {
        alu->out = 0;
        printf("Not a defined instruction in ISA\n");
    }

    // Update zero and negative flags for all operations
    alu->flags.zr = (alu->out == 0);
    alu->flags.ng = ((alu->out & (1u << (WORD_SIZE - 1))) != 0);
}

/* ---------------- Encoding & debug helpers ---------------- */

static word_t encodeI(uint8_t op, uint8_t r1, uint8_t r2, uint8_t imm) {
    return (word_t)(((op & 0xF) << 12) |
                    ((r1 & 0x7) << 9)  |
                    ((r2 & 0x7) << 6)  |
                     (imm & 0x3F));
}

static void dump_memory(struct CPU *cpu) {
    printf("Memory Dump:\n");
    for (int j = 0; j < 32; j++) {
        printf("%02X: %04X\n", j, cpu->mainMemory.mem[j]);
    }
    printf("Recursion depth: %d\n", cpu->static_counter);
}

static void dump_registers(struct CPU *cpu) {
    for (int j = 0; j < 8; j++) {
        printf("R%d=%d ", j, cpu->gpr.reg[j]);
    }
    printf("\nSP=%d IP=%d\n", cpu->spr.SP, cpu->cu.IP);
    printf("Flags: ZR=%d NG=%d OV=%d CY=%d\n",
           cpu->cu.aluflags.zr,
           cpu->cu.aluflags.ng,
           cpu->cu.aluflags.ov,
           cpu->cu.aluflags.cy);
}

/* ---------------- CPU core helpers ---------------- */

static void load_program(struct CPU *cpu, word_t *program, int size) {
    for (int i = 0; i < size; i++) {
        cpu->mainMemory.mem[i] = program[i];
    }
    cpu->cu.IP = 0;
    cpu->spr.SP = 399;   // top of stack
}

static void fetch_decode_execute(struct CPU *cpu) {
    if (cpu->running == 0) return;

    cpu->cu.IR = cpu->mainMemory.mem[cpu->cu.IP++];
    word_t instr = cpu->cu.IR;

    uint8_t op  = (instr >> 12) & 0xF;
    uint8_t r1  = (instr >> 9)  & 0x7;
    uint8_t r2  = (instr >> 6)  & 0x7;
    uint8_t imm = instr & 0x3F;

    printf("Executing: %s r1=%d r2=%d imm=%d\n",
           OPCODE_STRINGS[op], r1, r2, imm);

    if (op == NOP) {
        // No operation
    } else if (op == MOV) {
        cpu->gpr.reg[r1] = imm;
    } else if (op == ADD) {
        cpu->alu.x = cpu->gpr.reg[r1];
        cpu->alu.y = imm;
        cpu->alu.flags = (struct ALUFlags){0,0,0,0,0,0,0,0,0,0};
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
    } else if (op == SUB) {
        cpu->alu.x = cpu->gpr.reg[r1];
        cpu->alu.y = imm;
        cpu->alu.flags = (struct ALUFlags){0,0,1,0,1,1,0,0,0,0};
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
    } else if (op == AND) {
        cpu->gpr.reg[r1] &= cpu->gpr.reg[r2];
        cpu->cu.aluflags.zr = (cpu->gpr.reg[r1] == 0);
        cpu->cu.aluflags.ng = ((cpu->gpr.reg[r1] & 0x8000u) != 0);
    } else if (op == OR) {
        cpu->gpr.reg[r1] |= cpu->gpr.reg[r2];
        cpu->cu.aluflags.zr = (cpu->gpr.reg[r1] == 0);
        cpu->cu.aluflags.ng = ((cpu->gpr.reg[r1] & 0x8000u) != 0);
    } else if (op == MUL) {
        cpu->alu.x = cpu->gpr.reg[r1];
        cpu->alu.y = cpu->gpr.reg[r2];
        cpu->alu.flags = (struct ALUFlags){0,0,0,0,0,0,0,0,0,0};
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
    } else if (op == DIV) {
        if (cpu->gpr.reg[r2] == 0) {
            printf("Division by zero!\n");
            cpu->running = 0;
            return;
        }
        cpu->gpr.reg[r1] = cpu->gpr.reg[r1] / cpu->gpr.reg[r2];
        cpu->cu.aluflags.zr = (cpu->gpr.reg[r1] == 0);
        cpu->cu.aluflags.ng = ((int16_t)cpu->gpr.reg[r1] < 0);
    } else if (op == JMP) {
        cpu->cu.IP = imm;
    } else if (op == JZ) {
        if (cpu->cu.aluflags.zr) {
            cpu->cu.IP = imm;
        }
    } else if (op == CALL) {
        if (cpu->spr.SP == 0) {
            printf("Stack overflow!\n");
            cpu->running = 0;
            return;
        }
        cpu->mainMemory.mem[cpu->spr.SP--] = cpu->cu.IP;
        cpu->cu.IP = imm;
        cpu->static_counter++;
        fetch_decode_execute(cpu);
        return;
    } else if (op == RET) {
        if (cpu->spr.SP >= 399) {
            printf("Stack underflow!\n");
            cpu->running = 0;
            return;
        }
        cpu->cu.IP = cpu->mainMemory.mem[++cpu->spr.SP];
        fetch_decode_execute(cpu);
        return;
    } else if (op == HALT) {
        cpu->running = 0;
        printf("[CPU] Program HALTED.\n");
        return;
    }

    dump_registers(cpu);
}

static void run_cpu(struct CPU *cpu) {
    cpu->running = 1;
    while (cpu->running) {
        fetch_decode_execute(cpu);
    }
    dump_memory(cpu);
}

/* ---------------- Test program ---------------- */

int main(void) {
    struct CPU cpu = {0};

    word_t test_program[] = {
        // Test all opcodes
        encodeI(NOP, 0, 0, 0),    // NOP
        encodeI(MOV, 0, 0, 10),   // R0 = 10
        encodeI(MOV, 1, 0, 5),    // R1 = 5
        encodeI(ADD, 2, 0, 3),    // R2 = R2 + 3
        encodeI(SUB, 0, 0, 2),    // R0 = R0 - 2
        encodeI(MOV, 3, 0, 12),   // R3 = 12 (for AND/OR test)
        encodeI(MOV, 4, 0, 9),    // R4 = 9 (for AND/OR test)
        encodeI(AND, 3, 4, 0),    // R3 = R3 & R4
        encodeI(OR,  4, 3, 0),    // R4 = R4 | R3
        encodeI(MUL, 1, 0, 0),    // R1 = R1 * R0
        encodeI(MOV, 5, 0, 100),  // R5 = 100
        encodeI(MOV, 6, 0, 5),    // R6 = 5
        encodeI(DIV, 5, 6, 0),    // R5 = R5 / R6
        encodeI(JMP, 0, 0, 15),   // Jump to position 15
        encodeI(HALT,0, 0, 0),    // This HALT will be skipped
        encodeI(SUB, 6, 0, 5),    // R6 = R6 - 5
        encodeI(JZ,  0, 0, 18),   // If ZR flag is set, jump to CALL
        encodeI(HALT,0, 0, 0),    // This HALT will be skipped if R6 == 0
        encodeI(CALL,0, 0, 20),   // Call subroutine
        encodeI(HALT,0, 0, 0),    // Final HALT
        // Subroutine
        encodeI(MOV, 7, 0, 42),   // R7 = 42
        encodeI(RET, 0, 0, 0)     // Return from subroutine
    };

    load_program(&cpu, test_program,
                 sizeof(test_program) / sizeof(test_program[0]));
    run_cpu(&cpu);

    return 0;
}
