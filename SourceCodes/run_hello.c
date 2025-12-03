#include <stdio.h>
#include <stdint.h>

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

static word_t encodeI(uint8_t op, uint8_t r1, uint8_t r2, uint8_t imm) {
    return (word_t)(((op & 0xF) << 12) |
                    ((r1 & 0x7) << 9)  |
                    ((r2 & 0x7) << 6)  |
                     (imm & 0x3F));
}

static void memory_write(struct CPU *cpu, word_t address, word_t value) {
    if (address == MMIO_CHAR_OUT) {
        printf("%c", (char)(value & 0xFF));
        fflush(stdout);
    }
    if (address < 400) {
        cpu->mainMemory.mem[address] = value;
    }
}

static word_t memory_read(struct CPU *cpu, word_t address) {
    if (address < 400) {
        return cpu->mainMemory.mem[address];
    }
    return 0;
}

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

static void alu_compute(struct ALU *alu) {
    word_t x = alu->x;
    word_t y = alu->y;
    alu->flags.cy = 0;
    alu->flags.ov = 0;
    
    uint8_t d = (uint8_t)((alu->flags.zx << 5) |
                          (alu->flags.nx << 4) |
                          (alu->flags.zy << 3) |
                          (alu->flags.ny << 2) |
                          (alu->flags.f  << 1) |
                           alu->flags.no);
    
    if (d == 0b000010) {
        uint8_t carry;
        alu->out = add_nbit(x, y, &carry);
        alu->flags.cy = carry;
    } else {
        alu->out = 0;
    }
    
    alu->flags.zr = (alu->out == 0);
    alu->flags.ng = ((alu->out & (1u << (WORD_SIZE - 1))) != 0);
}

static void load_program(struct CPU *cpu, word_t *program, int size) {
    for (int i = 0; i < size; i++) {
        cpu->mainMemory.mem[i] = program[i];
    }
    cpu->cu.IP = 0;
    cpu->spr.SP = 399;
}

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
        cpu->alu.y = imm;
        cpu->alu.flags = (struct ALUFlags){0,0,0,0,1,0,0,0,0,0}; // f=1 for addition
        alu_compute(&cpu->alu);
        cpu->gpr.reg[r1] = cpu->alu.out;
        cpu->cu.aluflags = cpu->alu.flags;
    } else if (op == HALT) {
        cpu->running = 0;
        return;
    } else if (op == STORE) {
        word_t address = cpu->gpr.reg[r2];
        memory_write(cpu, address, cpu->gpr.reg[r1]);
    }
}

static void run_cpu(struct CPU *cpu) {
    cpu->running = 1;
    while (cpu->running) {
        fetch_decode_execute(cpu);
    }
}

int main(void) {
    struct CPU cpu = {0};
    
    printf("=== HELLO, WORLD! Program ===\n");
    printf("Output: ");

    // HELLO, WORLD! program
    // Note: Immediate values are 6-bit (0-63), so we build larger values using ADD
    word_t hello_program[] = {
        encodeI(MOV, 7, 0, 32),   // MOV R7, 32 (I/O port address)
        
        // 'H' = 72 = 63 + 9
        encodeI(MOV, 0, 0, 63),   
        encodeI(ADD, 0, 0, 9),    // R0 = 72 ('H')
        encodeI(STORE, 0, 7, 0),
        
        // 'E' = 69 = 63 + 6
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 6),    // R0 = 69 ('E')
        encodeI(STORE, 0, 7, 0),
        
        // 'L' = 76 = 63 + 13
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 13),   // R0 = 76 ('L')
        encodeI(STORE, 0, 7, 0),
        
        // 'L' = 76
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 13),   // R0 = 76 ('L')
        encodeI(STORE, 0, 7, 0),
        
        // 'O' = 79 = 63 + 16
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 16),   // R0 = 79 ('O')
        encodeI(STORE, 0, 7, 0),
        
        // ',' = 44
        encodeI(MOV, 0, 0, 44),   // R0 = 44 (',')
        encodeI(STORE, 0, 7, 0),
        
        // ' ' = 32
        encodeI(MOV, 0, 0, 32),   // R0 = 32 (' ')
        encodeI(STORE, 0, 7, 0),
        
        // 'W' = 87 = 63 + 24
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 24),   // R0 = 87 ('W')
        encodeI(STORE, 0, 7, 0),
        
        // 'O' = 79
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 16),   // R0 = 79 ('O')
        encodeI(STORE, 0, 7, 0),
        
        // 'R' = 82 = 63 + 19
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 19),   // R0 = 82 ('R')
        encodeI(STORE, 0, 7, 0),
        
        // 'L' = 76
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 13),   // R0 = 76 ('L')
        encodeI(STORE, 0, 7, 0),
        
        // 'D' = 68 = 63 + 5
        encodeI(MOV, 0, 0, 63),
        encodeI(ADD, 0, 0, 5),    // R0 = 68 ('D')
        encodeI(STORE, 0, 7, 0),
        
        // '!' = 33
        encodeI(MOV, 0, 0, 33),   // R0 = 33 ('!')
        encodeI(STORE, 0, 7, 0),
        
        // '\n' = 10
        encodeI(MOV, 0, 0, 10),   // R0 = 10 ('\n')
        encodeI(STORE, 0, 7, 0),
        
        encodeI(HALT, 0, 0, 0)    // HALT
    };

    load_program(&cpu, hello_program, sizeof(hello_program) / sizeof(hello_program[0]));
    run_cpu(&cpu);
    
    printf("\n=== Program Complete ===\n");
    return 0;
}
