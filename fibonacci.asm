; ========================================
; FIBONACCI SEQUENCE PROGRAM
; Computes first 10 Fibonacci numbers
; F(0)=0, F(1)=1, F(n)=F(n-1)+F(n-2)
; ========================================
; This program demonstrates:
; - Loop control
; - Register arithmetic
; - Conditional branching
; - Register management
; ========================================

; Initialize Fibonacci sequence
MOV R0, 0        ; R0 = F(n-2) = 0 (first Fibonacci number)
MOV R1, 1        ; R1 = F(n-1) = 1 (second Fibonacci number)
MOV R2, 0        ; R2 = counter (starts at 0)
MOV R3, 10       ; R3 = limit (compute 10 numbers)

; ========================================
; ALGORITHM:
; ========================================
; 1. Start with F(0)=0, F(1)=1
; 2. For i=2 to N:
;    a. F(i) = F(i-1) + F(i-2)
;    b. Shift: F(i-2) = F(i-1), F(i-1) = F(i)
; 3. Repeat until counter reaches limit
; ========================================

; Output first number (0)
; R0 currently holds 0

; Output second number (1)
; R1 currently holds 1

; Increment counter twice (we've done F(0) and F(1))
ADD R2, 1        ; counter = 1
ADD R2, 1        ; counter = 2

; ========================================
; MAIN FIBONACCI LOOP
; ========================================
fib_loop:
    ; Check if we've reached the limit
    MOV R4, 0        ; R4 = 0 (temp for comparison)
    ADD R4, R2       ; R4 = counter
    SUB R4, R3       ; R4 = counter - limit
    JZ done          ; If R4 == 0, we're done
    
    ; Compute next Fibonacci number
    ; F(n) = F(n-1) + F(n-2)
    MOV R4, 0        ; R4 = 0 (will hold F(n))
    ADD R4, R0       ; R4 = R0 (F(n-2))
    ADD R4, R1       ; R4 = R0 + R1 (F(n) = F(n-2) + F(n-1))
    
    ; The new Fibonacci number is now in R4
    ; Output R4 here (in full implementation)
    
    ; Shift values for next iteration
    ; F(n-2) = F(n-1)
    ; F(n-1) = F(n)
    MOV R0, 0        ; Clear R0
    ADD R0, R1       ; R0 = R1 (old F(n-1) becomes new F(n-2))
    MOV R1, 0        ; Clear R1
    ADD R1, R4       ; R1 = R4 (F(n) becomes new F(n-1))
    
    ; Increment counter
    ADD R2, 1        ; counter++
    
    ; Loop back
    JMP fib_loop

done:
    HALT             ; Stop execution

; ========================================
; EXECUTION TRACE (First Few Iterations):
; ========================================
; 
; INITIALIZATION:
; R0 = 0  (F(0))
; R1 = 1  (F(1))
; R2 = 2  (counter)
; R3 = 10 (limit)
;
; ITERATION 1 (Compute F(2)):
; - Check: R2 (2) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 0 + 1 = 1
; - Output: 1 (F(2) = 1)
; - Shift: R0=1, R1=1
; - Increment: R2=3
;
; ITERATION 2 (Compute F(3)):
; - Check: R2 (3) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 1 + 1 = 2
; - Output: 2 (F(3) = 2)
; - Shift: R0=1, R1=2
; - Increment: R2=4
;
; ITERATION 3 (Compute F(4)):
; - Check: R2 (4) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 1 + 2 = 3
; - Output: 3 (F(4) = 3)
; - Shift: R0=2, R1=3
; - Increment: R2=5
;
; ITERATION 4 (Compute F(5)):
; - Check: R2 (5) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 2 + 3 = 5
; - Output: 5 (F(5) = 5)
; - Shift: R0=3, R1=5
; - Increment: R2=6
;
; ITERATION 5 (Compute F(6)):
; - Check: R2 (6) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 3 + 5 = 8
; - Output: 8 (F(6) = 8)
; - Shift: R0=5, R1=8
; - Increment: R2=7
;
; ITERATION 6 (Compute F(7)):
; - Check: R2 (7) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 5 + 8 = 13
; - Output: 13 (F(7) = 13)
; - Shift: R0=8, R1=13
; - Increment: R2=8
;
; ITERATION 7 (Compute F(8)):
; - Check: R2 (8) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 8 + 13 = 21
; - Output: 21 (F(8) = 21)
; - Shift: R0=13, R1=21
; - Increment: R2=9
;
; ITERATION 8 (Compute F(9)):
; - Check: R2 (9) < R3 (10) ? Yes, continue
; - Compute: R4 = R0 + R1 = 13 + 21 = 34
; - Output: 34 (F(9) = 34)
; - Shift: R0=21, R1=34
; - Increment: R2=10
;
; FINAL CHECK:
; - Check: R2 (10) < R3 (10) ? No (equal)
; - Jump to done
; - HALT
;
; ========================================
; FIBONACCI SEQUENCE OUTPUT:
; ========================================
; F(0) = 0
; F(1) = 1
; F(2) = 1
; F(3) = 2
; F(4) = 3
; F(5) = 5
; F(6) = 8
; F(7) = 13
; F(8) = 21
; F(9) = 34
; ========================================

; ========================================
; REGISTER USAGE SUMMARY:
; ========================================
; R0: F(n-2) - Second previous Fibonacci number
; R1: F(n-1) - Previous Fibonacci number
; R2: counter - Loop iteration counter
; R3: limit - Maximum iterations (10)
; R4: temp - Temporary storage for F(n) and comparisons
; R5-R7: unused - Available for future enhancements
; ========================================

; ========================================
; CPU CYCLES PER ITERATION:
; ========================================
; Each loop iteration performs:
; - 4 MOV operations
; - 4 ADD operations
; - 1 SUB operation
; - 1 JZ operation (not taken)
; - 1 JMP operation (taken)
; Total: ~11 instructions per iteration
; For 8 iterations: ~88 instructions
; Plus initialization: ~6 instructions
; Total program: ~94 instructions executed
; ========================================
