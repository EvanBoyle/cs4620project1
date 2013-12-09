	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  main:
	# BeginFunc 56
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 56	# decrement sp to make space for locals/temps
	# _tmp0 = 10
	  li $t2, 10		# load constant value 10 into $t2
	  sw $t2, -12($fp)	# spill _tmp0 from $t2 to $fp-12
	# _tmp1 = -1
	  li $t2, -1		# load constant value -1 into $t2
	  sw $t2, -16($fp)	# spill _tmp1 from $t2 to $fp-16
	# _tmp2 = _tmp1 * _tmp0
	  lw $t0, -16($fp)	# fill _tmp1 to $t0 from $fp-16
	  lw $t1, -12($fp)	# fill _tmp0 to $t1 from $fp-12
	  mul $t2, $t0, $t1	
	  sw $t2, -20($fp)	# spill _tmp2 from $t2 to $fp-20
	# _tmp3 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -24($fp)	# spill _tmp3 from $t2 to $fp-24
	# _tmp4 = _tmp3 == _tmp2
	  lw $t0, -24($fp)	# fill _tmp3 to $t0 from $fp-24
	  lw $t1, -20($fp)	# fill _tmp2 to $t1 from $fp-20
	  seq $t2, $t0, $t1	
	  sw $t2, -28($fp)	# spill _tmp4 from $t2 to $fp-28
	# _tmp5 = _tmp2 < _tmp3
	  lw $t0, -20($fp)	# fill _tmp2 to $t0 from $fp-20
	  lw $t1, -24($fp)	# fill _tmp3 to $t1 from $fp-24
	  slt $t2, $t0, $t1	
	  sw $t2, -32($fp)	# spill _tmp5 from $t2 to $fp-32
	# _tmp6 = _tmp5 || _tmp4
	  lw $t0, -32($fp)	# fill _tmp5 to $t0 from $fp-32
	  lw $t1, -28($fp)	# fill _tmp4 to $t1 from $fp-28
	  or $t2, $t0, $t1	
	  sw $t2, -36($fp)	# spill _tmp6 from $t2 to $fp-36
	# IfZ _tmp6 Goto _L0
	  lw $t0, -36($fp)	# fill _tmp6 to $t0 from $fp-36
	  beqz $t0, _L0	# branch if _tmp6 is zero 
	# _tmp7 = "Decaf runtime error: Array size is <= 0\n"
	  .data			# create string constant marked with label
	  _string1: .asciiz "Decaf runtime error: Array size is <= 0\n"
	  .text
	  la $t2, _string1	# load label
	  sw $t2, -40($fp)	# spill _tmp7 from $t2 to $fp-40
	# PushParam _tmp7
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -40($fp)	# fill _tmp7 to $t0 from $fp-40
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L0:
	# _tmp8 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -44($fp)	# spill _tmp8 from $t2 to $fp-44
	# _tmp9 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -48($fp)	# spill _tmp9 from $t2 to $fp-48
	# _tmp10 = _tmp8 + _tmp2
	  lw $t0, -44($fp)	# fill _tmp8 to $t0 from $fp-44
	  lw $t1, -20($fp)	# fill _tmp2 to $t1 from $fp-20
	  add $t2, $t0, $t1	
	  sw $t2, -52($fp)	# spill _tmp10 from $t2 to $fp-52
	# _tmp11 = _tmp10 * _tmp9
	  lw $t0, -52($fp)	# fill _tmp10 to $t0 from $fp-52
	  lw $t1, -48($fp)	# fill _tmp9 to $t1 from $fp-48
	  mul $t2, $t0, $t1	
	  sw $t2, -56($fp)	# spill _tmp11 from $t2 to $fp-56
	# PushParam _tmp11
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -56($fp)	# fill _tmp11 to $t0 from $fp-56
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp12 = LCall _Alloc
	  jal _Alloc         	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -60($fp)	# spill _tmp12 from $t2 to $fp-60
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# *(_tmp12) = _tmp2
	  lw $t0, -20($fp)	# fill _tmp2 to $t0 from $fp-20
	  lw $t2, -60($fp)	# fill _tmp12 to $t2 from $fp-60
	  sw $t0, 0($t2) 	# store with offset
	# c = _tmp12
	  lw $t2, -60($fp)	# fill _tmp12 to $t2 from $fp-60
	  sw $t2, -8($fp)	# spill c from $t2 to $fp-8
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
_PrintInt:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 1
        lw   $a0, 4($fp)
        syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp)
        jr $ra
                                
_PrintString:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 4
        lw $a0, 4($fp)
        syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp)
        jr $ra
        
_PrintBool:
	subu $sp, $sp, 8
	sw $fp, 8($sp)
	sw $ra, 4($sp)
        addiu $fp, $sp, 8
	lw $t1, 4($fp)
	blez $t1, fbr
	li   $v0, 4		# system call for print_str
	la   $a0, TRUE		# address of str to print
	syscall			
	b end
fbr:	li   $v0, 4		# system call for print_str
	la   $a0, FALSE		# address of str to print
	syscall				
end:	move $sp, $fp
	lw $ra, -4($fp)
	lw $fp, 0($fp)
	jr $ra

_Alloc:
        subu $sp, $sp, 8
        sw $fp, 8($sp)
        sw $ra, 4($sp)
        addiu $fp, $sp, 8
        li   $v0, 9
        lw $a0, 4($fp)
	syscall
        move $sp, $fp
        lw $ra, -4($fp)
        lw $fp, 0($fp) 
        jr $ra


_StringEqual:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps

	li $v0,0

	#Determine length string 1
	lw $t0, 4($fp)       
	li $t3,0
bloop1: 
	lb $t5, ($t0) 
	beqz $t5, eloop1	
	addi $t0, 1
	addi $t3, 1
	b bloop1
eloop1:

	#Determine length string 2
	lw $t1, 8($fp)
	li $t4,0
bloop2: 
	lb $t5, ($t1) 
	beqz $t5, eloop2	
	addi $t1, 1
	addi $t4, 1
	b bloop2
eloop2:
	bne $t3,$t4,end1       #Check String Lengths Same

	lw $t0, 4($fp)       
	lw $t1, 8($fp)
	li $t3, 0     		
bloop3:	
	lb $t5, ($t0) 
	lb $t6, ($t1) 
	bne $t5, $t6, end1
	addi $t3, 1
	addi $t0, 1
	addi $t1, 1
	bne $t3,$t4,bloop3
eloop3:	li $v0,1

end1:	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra                # return from function

_Halt:
        li $v0, 10
        syscall

_ReadInteger:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps
	li $v0, 5
	syscall
	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra
        

_ReadLine:
	subu $sp, $sp, 8      # decrement sp to make space to save ra, fp
	sw $fp, 8($sp)        # save fp
	sw $ra, 4($sp)        # save ra
	addiu $fp, $sp, 8     # set up new fp
	subu $sp, $sp, 4      # decrement sp to make space for locals/temps
	li $a1, 40
	la $a0, SPACE
	li $v0, 8
	syscall

	la $t1, SPACE
bloop4: 
	lb $t5, ($t1) 
	beqz $t5, eloop4	
	addi $t1, 1
	b bloop4
eloop4:
	addi $t1,-1
	li $t6,0
        sb $t6, ($t1)

	la $v0, SPACE
	move $sp, $fp         # pop callee frame off stack
	lw $ra, -4($fp)       # restore saved ra
	lw $fp, 0($fp)        # restore saved fp
	jr $ra
	

	.data
TRUE:.asciiz "true"
FALSE:.asciiz "false"
SPACE:.asciiz "Making Space For Inputed Values Is Fun."