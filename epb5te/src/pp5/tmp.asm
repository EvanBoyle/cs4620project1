	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  _foo:
	# BeginFunc 12
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 12	# decrement sp to make space for locals/temps
	# IfZ c Goto _L0
	  lw $t0, 8($fp)	# fill c to $t0 from $fp+8
	  beqz $t0, _L0	# branch if c is zero 
	# _tmp0 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -8($fp)	# spill _tmp0 from $t2 to $fp-8
	# _tmp1 = a + _tmp0
	  lw $t0, 4($fp)	# fill a to $t0 from $fp+4
	  lw $t1, -8($fp)	# fill _tmp0 to $t1 from $fp-8
	  add $t2, $t0, $t1	
	  sw $t2, -12($fp)	# spill _tmp1 from $t2 to $fp-12
	# Return _tmp1
	  lw $t2, -12($fp)	# fill _tmp1 to $t2 from $fp-12
	  move $v0, $t2		# assign return value into $v0
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# Goto _L1
	  b _L1		# unconditional branch
  _L0:
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, 4($fp)	# fill a to $t0 from $fp+4
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
  _L1:
	# _tmp2 = 18
	  li $t2, 18		# load constant value 18 into $t2
	  sw $t2, -16($fp)	# spill _tmp2 from $t2 to $fp-16
	# Return _tmp2
	  lw $t2, -16($fp)	# fill _tmp2 to $t2 from $fp-16
	  move $v0, $t2		# assign return value into $v0
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
	# EndFunc
	# (below handles reaching end of fn body with no explicit return)
	  move $sp, $fp		# pop callee frame off stack
	  lw $ra, -4($fp)	# restore saved ra
	  lw $fp, 0($fp)	# restore saved fp
	  jr $ra		# return from function
  main:
	# BeginFunc 92
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 92	# decrement sp to make space for locals/temps
	# _tmp3 = 10
	  li $t2, 10		# load constant value 10 into $t2
	  sw $t2, -20($fp)	# spill _tmp3 from $t2 to $fp-20
	# a = _tmp3
	  lw $t2, -20($fp)	# fill _tmp3 to $t2 from $fp-20
	  sw $t2, 4($fp)	# spill a from $t2 to $fp+4
	# _tmp4 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -28($fp)	# spill _tmp4 from $t2 to $fp-28
	# _tmp5 = a / _tmp4
	  lw $t0, 4($fp)	# fill a to $t0 from $fp+4
	  lw $t1, -28($fp)	# fill _tmp4 to $t1 from $fp-28
	  div $t2, $t0, $t1	
	  sw $t2, -32($fp)	# spill _tmp5 from $t2 to $fp-32
	# b = _tmp5
	  lw $t2, -32($fp)	# fill _tmp5 to $t2 from $fp-32
	  sw $t2, -24($fp)	# spill b from $t2 to $fp-24
	# PushParam a
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, 4($fp)	# fill a to $t0 from $fp+4
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp6 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -36($fp)	# spill _tmp6 from $t2 to $fp-36
	# PushParam _tmp6
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -36($fp)	# fill _tmp6 to $t0 from $fp-36
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp7 = LCall _foo
	  jal _foo           	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -40($fp)	# spill _tmp7 from $t2 to $fp-40
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# _tmp8 = 2
	  li $t2, 2		# load constant value 2 into $t2
	  sw $t2, -44($fp)	# spill _tmp8 from $t2 to $fp-44
	# _tmp9 = b + _tmp8
	  lw $t0, -24($fp)	# fill b to $t0 from $fp-24
	  lw $t1, -44($fp)	# fill _tmp8 to $t1 from $fp-44
	  add $t2, $t0, $t1	
	  sw $t2, -48($fp)	# spill _tmp9 from $t2 to $fp-48
	# PushParam _tmp9
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -48($fp)	# fill _tmp9 to $t0 from $fp-48
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp10 = a < b
	  lw $t0, 4($fp)	# fill a to $t0 from $fp+4
	  lw $t1, -24($fp)	# fill b to $t1 from $fp-24
	  slt $t2, $t0, $t1	
	  sw $t2, -52($fp)	# spill _tmp10 from $t2 to $fp-52
	# _tmp11 = b == a
	  lw $t0, -24($fp)	# fill b to $t0 from $fp-24
	  lw $t1, 4($fp)	# fill a to $t1 from $fp+4
	  seq $t2, $t0, $t1	
	  sw $t2, -56($fp)	# spill _tmp11 from $t2 to $fp-56
	# _tmp12 = _tmp10 || _tmp11
	  lw $t0, -52($fp)	# fill _tmp10 to $t0 from $fp-52
	  lw $t1, -56($fp)	# fill _tmp11 to $t1 from $fp-56
	  or $t2, $t0, $t1	
	  sw $t2, -60($fp)	# spill _tmp12 from $t2 to $fp-60
	# PushParam _tmp12
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -60($fp)	# fill _tmp12 to $t0 from $fp-60
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp13 = LCall _foo
	  jal _foo           	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -64($fp)	# spill _tmp13 from $t2 to $fp-64
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# _tmp14 = 3
	  li $t2, 3		# load constant value 3 into $t2
	  sw $t2, -68($fp)	# spill _tmp14 from $t2 to $fp-68
	# PushParam _tmp14
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -68($fp)	# fill _tmp14 to $t0 from $fp-68
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp15 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -72($fp)	# spill _tmp15 from $t2 to $fp-72
	# _tmp16 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -76($fp)	# spill _tmp16 from $t2 to $fp-76
	# _tmp17 = _tmp15 && _tmp16
	  lw $t0, -72($fp)	# fill _tmp15 to $t0 from $fp-72
	  lw $t1, -76($fp)	# fill _tmp16 to $t1 from $fp-76
	  and $t2, $t0, $t1	
	  sw $t2, -80($fp)	# spill _tmp17 from $t2 to $fp-80
	# PushParam _tmp17
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -80($fp)	# fill _tmp17 to $t0 from $fp-80
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp18 = LCall _foo
	  jal _foo           	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -84($fp)	# spill _tmp18 from $t2 to $fp-84
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
	# PushParam _tmp18
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -84($fp)	# fill _tmp18 to $t0 from $fp-84
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp19 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -88($fp)	# spill _tmp19 from $t2 to $fp-88
	# _tmp20 = -1
	  li $t2, -1		# load constant value -1 into $t2
	  sw $t2, -92($fp)	# spill _tmp20 from $t2 to $fp-92
	# _tmp21 = _tmp20 * _tmp19
	  lw $t0, -92($fp)	# fill _tmp20 to $t0 from $fp-92
	  lw $t1, -88($fp)	# fill _tmp19 to $t1 from $fp-88
	  mul $t2, $t0, $t1	
	  sw $t2, -96($fp)	# spill _tmp21 from $t2 to $fp-96
	# _tmp22 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -100($fp)	# spill _tmp22 from $t2 to $fp-100
	# _tmp23 = _tmp21 + _tmp22
	  lw $t0, -96($fp)	# fill _tmp21 to $t0 from $fp-96
	  lw $t1, -100($fp)	# fill _tmp22 to $t1 from $fp-100
	  add $t2, $t0, $t1	
	  sw $t2, -104($fp)	# spill _tmp23 from $t2 to $fp-104
	# PushParam _tmp23
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -104($fp)	# fill _tmp23 to $t0 from $fp-104
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp24 = LCall _foo
	  jal _foo           	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -108($fp)	# spill _tmp24 from $t2 to $fp-108
	# PopParams 8
	  add $sp, $sp, 8	# pop params off stack
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
