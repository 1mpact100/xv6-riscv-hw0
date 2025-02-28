.data                                      

fmt_int: .asciz "%d\n"
err_fmt: .asciz "Incorrect format\n"
check_str: .asciz "Check\n"
empty_str: .asciz "Empty input\n"
one_number: .asciz "Only one number\n"
correct_str: .asciz "Correct\n"
buf: .space 50

#define BUF_SIZE 50

.text                                   
.global main                               

main:
    la a0, buf
    li a1, BUF_SIZE
    call gets

    li s8, 1
    li s9, 1
    li t1, '\n'
    li t2, '0'
    li t3, '9'
    li t4, ' '
    li t5, '-'

    j check_first_sym

check_first_sym:
    la s0, buf
    lb s1, 0(s0)

    beq s1, t1, emp_err
    beqz s1, emp_err

    beq s1, t5, first_minus

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_first

first_minus:
    li s8, -1
    addi s0, s0, 1

    lb s1, 0(s0)

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_first

check_first:
    lb s1, 0(s0)

    beq s1, t4, correct_check_first

    beq s1, t1, one_number_error
    beqz s1, one_number_error

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_first

correct_check_first:
    addi s0, s0, 1
    lb s1, 0(s0)

    beq s1, t5, second_minus

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_second

second_minus:
    li s9, -1
    addi s0, s0, 1

    lb s1, 0(s0)

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_second

check_second:
    lb s1, 0(s0)

    beq s1, t1, correct_check_second
    beqz s1, correct_check_second

    blt s1, t2, inc_fmt
    bgt s1, t3, inc_fmt

    addi s0, s0, 1

    j check_second

correct_check_second:
    la s10, buf

    lb s1, 0(s10)

    bne s1, t5, first_number

    addi s10, s10, 1

    j first_number

first_number:
    mv a0, s10
    call atoi

    mv s11, a0
    mul s11, s11, s8 

    la s10, buf

    j get_second_number

get_second_number:
    lb s1, 0(s10)

    beq s1, t4, helper

    addi s10, s10, 1

    j get_second_number

helper:
    addi s10, s10, 1

    lb s1, 0(s10)

    bne s1, t5, second_number

    addi s10, s10, 1

    j second_number

second_number:
    mv a0, s10
    call atoi 

    mv s7, a0 
    mul s7, s7, s9 

    j output

output:
    la a0, fmt_int
    add a1, s7, s11

    call printf

    li a0, 0
    j exit

inc_fmt:
    li a0, 2
    la a1, err_fmt
    call fprintf
    
    li a0, 1
    j exit

emp_err:
    li a0, 2
    la a1, empty_str
    call fprintf

    li a0, 1
    j exit

one_number_error:
    li a0, 2
    la a1, one_number
    call fprintf

    li a0, 1
    j exit

exit: 
    li a7, 2
    ecall
