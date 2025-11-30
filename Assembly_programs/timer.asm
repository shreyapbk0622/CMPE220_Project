; ========================================
; TIMER PROGRAM
; Demonstrates Fetch/Compute/Store Cycles
; ========================================
; This program counts from 0 to 10 with visible output
; Each iteration shows the complete CPU cycle

; Initialize counter to 0
MOV R0, 0        ; R0 = 0 (counter)
MOV R1, 10       ; R1 = 10 (limit)
MOV R2, 32       ; R2 = 32 (I/O port address for character output)

; ========================================
; FETCH-COMPUTE-STORE CYCLE DEMONSTRATION:
;
; FETCH PHASE:
;   1. Read instruction from memory[IP]
;   2. Store in IR (Instruction Register)
;   3. Increment IP
;
; DECODE PHASE:
;   4. Extract opcode from bits [15:12]
;   5. Extract R1 from bits [11:9]
;   6. Extract R2 from bits [8:6]
;   7. Extract immediate from bits [5:0]
;
; EXECUTE (COMPUTE) PHASE:
;   8. Perform operation in ALU
;   9. Update flags (ZR, NG, OV, CY)
;
; STORE PHASE:
;   10. Write result to destination register
;   11. Update special registers if needed
; ========================================

loop:
    ; Convert counter to ASCII digit ('0' = 48 + digit)
    MOV R3, 48       ; R3 = ASCII '0' (48)
    ADD R3, R0       ; R3 = R3 + R0 (compute ASCII character)
    
    ; Output the digit (would use memory write in full implementation)
    ; In this simplified version, the digit is in R3
    
    ; Increment counter
    ADD R0, 1        ; R0 = R0 + 1
    
    ; Check if we've reached the limit
    SUB R4, R0       ; R4 = R0 (copy for comparison)
    SUB R4, R1       ; R4 = R0 - R1
    
    ; If R4 == 0, we've counted to 10
    JZ done          ; Jump if zero flag is set
    
    ; Otherwise, continue looping
    JMP loop

done:
    HALT             ; Stop execution

; ========================================
; EXPECTED EXECUTION TRACE:
; ========================================
; Cycle 1:  FETCH: IR = MOV R0, 0      IP: 0→1
;           DECODE: OP=MOV, R1=0, IMM=0
;           EXECUTE: (no computation)
;           STORE: R0 = 0
;
; Cycle 2:  FETCH: IR = MOV R1, 10     IP: 1→2
;           DECODE: OP=MOV, R1=1, IMM=10
;           EXECUTE: (no computation)
;           STORE: R1 = 10
;
; Cycle 3:  FETCH: IR = MOV R2, 32     IP: 2→3
;           DECODE: OP=MOV, R1=2, IMM=32
;           EXECUTE: (no computation)
;           STORE: R2 = 32
;
; Cycle 4:  FETCH: IR = MOV R3, 48     IP: 3→4
;           DECODE: OP=MOV, R1=3, IMM=48
;           EXECUTE: (no computation)
;           STORE: R3 = 48
;
; Cycle 5:  FETCH: IR = ADD R3, R0     IP: 4→5
;           DECODE: OP=ADD, R1=3, IMM=0
;           EXECUTE: ALU.X=48, ALU.Y=0, OUT=48
;                    Flags: ZR=0, NG=0
;           STORE: R3 = 48
;
; Cycle 6:  FETCH: IR = ADD R0, 1      IP: 5→6
;           DECODE: OP=ADD, R1=0, IMM=1
;           EXECUTE: ALU.X=0, ALU.Y=1, OUT=1
;                    Flags: ZR=0, NG=0
;           STORE: R0 = 1
;
; ... (loop continues) ...
;
; Final:    FETCH: IR = HALT           IP: N→N
;           DECODE: OP=HALT
;           EXECUTE: Set running=0
;           STORE: (none)
; ========================================
