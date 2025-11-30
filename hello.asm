; ========================================
; HELLO WORLD PROGRAM
; Outputs "HELLO, WORLD!" to console
; Uses memory-mapped I/O at address 32 (0x20)
; ========================================

; Initialize I/O port address
MOV R7, 32       ; R7 = 32 (Character output port at 0x20)

; Output 'H' (ASCII 72)
MOV R0, 72
STORE R0, R7     ; memory[R7] = R0

; Output 'E' (ASCII 69)
MOV R0, 69
STORE R0, R7     ; memory[R7] = R0

; Output 'L' (ASCII 76)
MOV R0, 76
STORE R0, R7     ; memory[R7] = R0

; Output 'L' (ASCII 76)
MOV R0, 76
STORE R0, R7     ; memory[R7] = R0

; Output 'O' (ASCII 79)
MOV R0, 79
STORE R0, R7     ; memory[R7] = R0

; Output ',' (ASCII 44)
MOV R0, 44
STORE R0, R7     ; memory[R7] = R0

; Output ' ' (ASCII 32)
MOV R0, 32
STORE R0, R7     ; memory[R7] = R0

; Output 'W' (ASCII 87)
MOV R0, 87
STORE R0, R7     ; memory[R7] = R0

; Output 'O' (ASCII 79)
MOV R0, 79
STORE R0, R7     ; memory[R7] = R0

; Output 'R' (ASCII 82)
MOV R0, 82
STORE R0, R7     ; memory[R7] = R0

; Output 'L' (ASCII 76)
MOV R0, 76
STORE R0, R7     ; memory[R7] = R0

; Output 'D' (ASCII 68)
MOV R0, 68
STORE R0, R7     ; memory[R7] = R0

; Output '!' (ASCII 33)
MOV R0, 33
STORE R0, R7     ; memory[R7] = R0

; Output newline (ASCII 10)
MOV R0, 10
STORE R0, R7     ; memory[R7] = R0

; Program complete
HALT

; ========================================
; MEMORY-MAPPED I/O EXPLANATION:
; ========================================
; Address 0x20 (32 decimal) is designated as the
; character output port. When a value is written
; to this memory location, it is interpreted as
; an ASCII character and displayed on the console.
;
; To extend the CPU to support this:
; 1. Add a check in the memory write operation
; 2. If address == 32, output the character
; 3. Example in C:
;    if (address == 32) {
;        printf("%c", value);
;    }
; ========================================

; ========================================
; EXPECTED OUTPUT:
; ========================================
; HELLO, WORLD!
; ========================================

; ========================================
; ASCII CHARACTER REFERENCE:
; ========================================
; 'H' = 72    'E' = 69    'L' = 76    'O' = 79
; ',' = 44    ' ' = 32    'W' = 87    'R' = 82
; 'D' = 68    '!' = 33    '\n'= 10
; ========================================
