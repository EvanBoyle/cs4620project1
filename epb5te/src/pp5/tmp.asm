	# standard Decaf preamble 
	  .text
	  .align 2
	  .globl main
  main:
	# BeginFunc 228
	  subu $sp, $sp, 8	# decrement sp to make space to save ra, fp
	  sw $fp, 8($sp)	# save fp
	  sw $ra, 4($sp)	# save ra
	  addiu $fp, $sp, 8	# set up new fp
	  subu $sp, $sp, 228	# decrement sp to make space for locals/temps
	# _tmp0 = 10
	  li $t2, 10		# load constant value 10 into $t2
	  sw $t2, -12($fp)	# spill _tmp0 from $t2 to $fp-12
	# _tmp1 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -16($fp)	# spill _tmp1 from $t2 to $fp-16
	# _tmp2 = _tmp1 == _tmp0
	  lw $t0, -16($fp)	# fill _tmp1 to $t0 from $fp-16
	  lw $t1, -12($fp)	# fill _tmp0 to $t1 from $fp-12
	  seq $t2, $t0, $t1	
	  sw $t2, -20($fp)	# spill _tmp2 from $t2 to $fp-20
	# _tmp3 = _tmp0 < _tmp1
	  lw $t0, -12($fp)	# fill _tmp0 to $t0 from $fp-12
	  lw $t1, -16($fp)	# fill _tmp1 to $t1 from $fp-16
	  slt $t2, $t0, $t1	
	  sw $t2, -24($fp)	# spill _tmp3 from $t2 to $fp-24
	# _tmp4 = _tmp3 || _tmp2
	  lw $t0, -24($fp)	# fill _tmp3 to $t0 from $fp-24
	  lw $t1, -20($fp)	# fill _tmp2 to $t1 from $fp-20
	  or $t2, $t0, $t1	
	  sw $t2, -28($fp)	# spill _tmp4 from $t2 to $fp-28
	# IfZ _tmp4 Goto _L0
	  lw $t0, -28($fp)	# fill _tmp4 to $t0 from $fp-28
	  beqz $t0, _L0	# branch if _tmp4 is zero 
	# _tmp5 = "Decaf runtime error: Array size is <= 0\n"
	  .data			# create string constant marked with label
	  _string1: .asciiz "Decaf runtime error: Array size is <= 0\n"
	  .text
	  la $t2, _string1	# load label
	  sw $t2, -32($fp)	# spill _tmp5 from $t2 to $fp-32
	# PushParam _tmp5
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -32($fp)	# fill _tmp5 to $t0 from $fp-32
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L0:
	# _tmp6 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -36($fp)	# spill _tmp6 from $t2 to $fp-36
	# _tmp7 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -40($fp)	# spill _tmp7 from $t2 to $fp-40
	# _tmp8 = _tmp6 + _tmp0
	  lw $t0, -36($fp)	# fill _tmp6 to $t0 from $fp-36
	  lw $t1, -12($fp)	# fill _tmp0 to $t1 from $fp-12
	  add $t2, $t0, $t1	
	  sw $t2, -44($fp)	# spill _tmp8 from $t2 to $fp-44
	# _tmp9 = _tmp8 * _tmp7
	  lw $t0, -44($fp)	# fill _tmp8 to $t0 from $fp-44
	  lw $t1, -40($fp)	# fill _tmp7 to $t1 from $fp-40
	  mul $t2, $t0, $t1	
	  sw $t2, -48($fp)	# spill _tmp9 from $t2 to $fp-48
	# PushParam _tmp9
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -48($fp)	# fill _tmp9 to $t0 from $fp-48
	  sw $t0, 4($sp)	# copy param value to stack
	# _tmp10 = LCall _Alloc
	  jal _Alloc         	# jump to function
	  move $t2, $v0		# copy function return value from $v0
	  sw $t2, -52($fp)	# spill _tmp10 from $t2 to $fp-52
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# *(_tmp10) = _tmp0
	  lw $t0, -12($fp)	# fill _tmp0 to $t0 from $fp-12
	  lw $t2, -52($fp)	# fill _tmp10 to $t2 from $fp-52
	  sw $t0, 0($t2) 	# store with offset
	# c = _tmp10
	  lw $t2, -52($fp)	# fill _tmp10 to $t2 from $fp-52
	  sw $t2, -8($fp)	# spill c from $t2 to $fp-8
	# _tmp11 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -60($fp)	# spill _tmp11 from $t2 to $fp-60
	# i = _tmp11
	  lw $t2, -60($fp)	# fill _tmp11 to $t2 from $fp-60
	  sw $t2, -56($fp)	# spill i from $t2 to $fp-56
  _L1:
	# _tmp12 = 10
	  li $t2, 10		# load constant value 10 into $t2
	  sw $t2, -64($fp)	# spill _tmp12 from $t2 to $fp-64
	# _tmp13 = i < _tmp12
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t1, -64($fp)	# fill _tmp12 to $t1 from $fp-64
	  slt $t2, $t0, $t1	
	  sw $t2, -68($fp)	# spill _tmp13 from $t2 to $fp-68
	# IfZ _tmp13 Goto _L2
	  lw $t0, -68($fp)	# fill _tmp13 to $t0 from $fp-68
	  beqz $t0, _L2	# branch if _tmp13 is zero 
	# _tmp14 = *(c)
	  lw $t0, -8($fp)	# fill c to $t0 from $fp-8
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -72($fp)	# spill _tmp14 from $t2 to $fp-72
	# _tmp15 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -76($fp)	# spill _tmp15 from $t2 to $fp-76
	# _tmp16 = i < _tmp15
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t1, -76($fp)	# fill _tmp15 to $t1 from $fp-76
	  slt $t2, $t0, $t1	
	  sw $t2, -80($fp)	# spill _tmp16 from $t2 to $fp-80
	# _tmp17 = _tmp14 < i
	  lw $t0, -72($fp)	# fill _tmp14 to $t0 from $fp-72
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  slt $t2, $t0, $t1	
	  sw $t2, -84($fp)	# spill _tmp17 from $t2 to $fp-84
	# _tmp18 = _tmp14 == i
	  lw $t0, -72($fp)	# fill _tmp14 to $t0 from $fp-72
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  seq $t2, $t0, $t1	
	  sw $t2, -88($fp)	# spill _tmp18 from $t2 to $fp-88
	# _tmp19 = _tmp18 || _tmp16
	  lw $t0, -88($fp)	# fill _tmp18 to $t0 from $fp-88
	  lw $t1, -80($fp)	# fill _tmp16 to $t1 from $fp-80
	  or $t2, $t0, $t1	
	  sw $t2, -92($fp)	# spill _tmp19 from $t2 to $fp-92
	# IfZ _tmp19 Goto _L3
	  lw $t0, -92($fp)	# fill _tmp19 to $t0 from $fp-92
	  beqz $t0, _L3	# branch if _tmp19 is zero 
	# _tmp20 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string2: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string2	# load label
	  sw $t2, -96($fp)	# spill _tmp20 from $t2 to $fp-96
	# PushParam _tmp20
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -96($fp)	# fill _tmp20 to $t0 from $fp-96
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L3:
	# _tmp21 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -100($fp)	# spill _tmp21 from $t2 to $fp-100
	# _tmp22 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -104($fp)	# spill _tmp22 from $t2 to $fp-104
	# _tmp23 = _tmp21 + i
	  lw $t0, -100($fp)	# fill _tmp21 to $t0 from $fp-100
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  add $t2, $t0, $t1	
	  sw $t2, -108($fp)	# spill _tmp23 from $t2 to $fp-108
	# _tmp24 = _tmp23 * _tmp22
	  lw $t0, -108($fp)	# fill _tmp23 to $t0 from $fp-108
	  lw $t1, -104($fp)	# fill _tmp22 to $t1 from $fp-104
	  mul $t2, $t0, $t1	
	  sw $t2, -112($fp)	# spill _tmp24 from $t2 to $fp-112
	# _tmp25 = _tmp24 + c
	  lw $t0, -112($fp)	# fill _tmp24 to $t0 from $fp-112
	  lw $t1, -8($fp)	# fill c to $t1 from $fp-8
	  add $t2, $t0, $t1	
	  sw $t2, -116($fp)	# spill _tmp25 from $t2 to $fp-116
	# *(_tmp25) = i
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t2, -116($fp)	# fill _tmp25 to $t2 from $fp-116
	  sw $t0, 0($t2) 	# store with offset
	# _tmp26 = *(c)
	  lw $t0, -8($fp)	# fill c to $t0 from $fp-8
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -124($fp)	# spill _tmp26 from $t2 to $fp-124
	# _tmp27 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -128($fp)	# spill _tmp27 from $t2 to $fp-128
	# _tmp28 = i < _tmp27
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t1, -128($fp)	# fill _tmp27 to $t1 from $fp-128
	  slt $t2, $t0, $t1	
	  sw $t2, -132($fp)	# spill _tmp28 from $t2 to $fp-132
	# _tmp29 = _tmp26 < i
	  lw $t0, -124($fp)	# fill _tmp26 to $t0 from $fp-124
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  slt $t2, $t0, $t1	
	  sw $t2, -136($fp)	# spill _tmp29 from $t2 to $fp-136
	# _tmp30 = _tmp26 == i
	  lw $t0, -124($fp)	# fill _tmp26 to $t0 from $fp-124
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  seq $t2, $t0, $t1	
	  sw $t2, -140($fp)	# spill _tmp30 from $t2 to $fp-140
	# _tmp31 = _tmp30 || _tmp28
	  lw $t0, -140($fp)	# fill _tmp30 to $t0 from $fp-140
	  lw $t1, -132($fp)	# fill _tmp28 to $t1 from $fp-132
	  or $t2, $t0, $t1	
	  sw $t2, -144($fp)	# spill _tmp31 from $t2 to $fp-144
	# IfZ _tmp31 Goto _L4
	  lw $t0, -144($fp)	# fill _tmp31 to $t0 from $fp-144
	  beqz $t0, _L4	# branch if _tmp31 is zero 
	# _tmp32 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string3: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string3	# load label
	  sw $t2, -148($fp)	# spill _tmp32 from $t2 to $fp-148
	# PushParam _tmp32
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -148($fp)	# fill _tmp32 to $t0 from $fp-148
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L4:
	# _tmp33 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -152($fp)	# spill _tmp33 from $t2 to $fp-152
	# _tmp34 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -156($fp)	# spill _tmp34 from $t2 to $fp-156
	# _tmp35 = _tmp33 + i
	  lw $t0, -152($fp)	# fill _tmp33 to $t0 from $fp-152
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  add $t2, $t0, $t1	
	  sw $t2, -160($fp)	# spill _tmp35 from $t2 to $fp-160
	# _tmp36 = _tmp35 * _tmp34
	  lw $t0, -160($fp)	# fill _tmp35 to $t0 from $fp-160
	  lw $t1, -156($fp)	# fill _tmp34 to $t1 from $fp-156
	  mul $t2, $t0, $t1	
	  sw $t2, -164($fp)	# spill _tmp36 from $t2 to $fp-164
	# _tmp37 = _tmp36 + c
	  lw $t0, -164($fp)	# fill _tmp36 to $t0 from $fp-164
	  lw $t1, -8($fp)	# fill c to $t1 from $fp-8
	  add $t2, $t0, $t1	
	  sw $t2, -168($fp)	# spill _tmp37 from $t2 to $fp-168
	# _tmp38 = *(_tmp37)
	  lw $t0, -168($fp)	# fill _tmp37 to $t0 from $fp-168
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -172($fp)	# spill _tmp38 from $t2 to $fp-172
	# d = _tmp38
	  lw $t2, -172($fp)	# fill _tmp38 to $t2 from $fp-172
	  sw $t2, -120($fp)	# spill d from $t2 to $fp-120
	# _tmp39 = *(c)
	  lw $t0, -8($fp)	# fill c to $t0 from $fp-8
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -176($fp)	# spill _tmp39 from $t2 to $fp-176
	# _tmp40 = 0
	  li $t2, 0		# load constant value 0 into $t2
	  sw $t2, -180($fp)	# spill _tmp40 from $t2 to $fp-180
	# _tmp41 = i < _tmp40
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t1, -180($fp)	# fill _tmp40 to $t1 from $fp-180
	  slt $t2, $t0, $t1	
	  sw $t2, -184($fp)	# spill _tmp41 from $t2 to $fp-184
	# _tmp42 = _tmp39 < i
	  lw $t0, -176($fp)	# fill _tmp39 to $t0 from $fp-176
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  slt $t2, $t0, $t1	
	  sw $t2, -188($fp)	# spill _tmp42 from $t2 to $fp-188
	# _tmp43 = _tmp39 == i
	  lw $t0, -176($fp)	# fill _tmp39 to $t0 from $fp-176
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  seq $t2, $t0, $t1	
	  sw $t2, -192($fp)	# spill _tmp43 from $t2 to $fp-192
	# _tmp44 = _tmp43 || _tmp41
	  lw $t0, -192($fp)	# fill _tmp43 to $t0 from $fp-192
	  lw $t1, -184($fp)	# fill _tmp41 to $t1 from $fp-184
	  or $t2, $t0, $t1	
	  sw $t2, -196($fp)	# spill _tmp44 from $t2 to $fp-196
	# IfZ _tmp44 Goto _L5
	  lw $t0, -196($fp)	# fill _tmp44 to $t0 from $fp-196
	  beqz $t0, _L5	# branch if _tmp44 is zero 
	# _tmp45 = "Decaf runtime error: Array subscript out of bound..."
	  .data			# create string constant marked with label
	  _string4: .asciiz "Decaf runtime error: Array subscript out of bounds\n"
	  .text
	  la $t2, _string4	# load label
	  sw $t2, -200($fp)	# spill _tmp45 from $t2 to $fp-200
	# PushParam _tmp45
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -200($fp)	# fill _tmp45 to $t0 from $fp-200
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintString
	  jal _PrintString   	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# LCall _Halt
	  jal _Halt          	# jump to function
  _L5:
	# _tmp46 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -204($fp)	# spill _tmp46 from $t2 to $fp-204
	# _tmp47 = 4
	  li $t2, 4		# load constant value 4 into $t2
	  sw $t2, -208($fp)	# spill _tmp47 from $t2 to $fp-208
	# _tmp48 = _tmp46 + i
	  lw $t0, -204($fp)	# fill _tmp46 to $t0 from $fp-204
	  lw $t1, -56($fp)	# fill i to $t1 from $fp-56
	  add $t2, $t0, $t1	
	  sw $t2, -212($fp)	# spill _tmp48 from $t2 to $fp-212
	# _tmp49 = _tmp48 * _tmp47
	  lw $t0, -212($fp)	# fill _tmp48 to $t0 from $fp-212
	  lw $t1, -208($fp)	# fill _tmp47 to $t1 from $fp-208
	  mul $t2, $t0, $t1	
	  sw $t2, -216($fp)	# spill _tmp49 from $t2 to $fp-216
	# _tmp50 = _tmp49 + c
	  lw $t0, -216($fp)	# fill _tmp49 to $t0 from $fp-216
	  lw $t1, -8($fp)	# fill c to $t1 from $fp-8
	  add $t2, $t0, $t1	
	  sw $t2, -220($fp)	# spill _tmp50 from $t2 to $fp-220
	# _tmp51 = *(_tmp50)
	  lw $t0, -220($fp)	# fill _tmp50 to $t0 from $fp-220
	  lw $t2, 0($t0) 	# load with offset
	  sw $t2, -224($fp)	# spill _tmp51 from $t2 to $fp-224
	# PushParam _tmp51
	  subu $sp, $sp, 4	# decrement sp to make space for param
	  lw $t0, -224($fp)	# fill _tmp51 to $t0 from $fp-224
	  sw $t0, 4($sp)	# copy param value to stack
	# LCall _PrintInt
	  jal _PrintInt      	# jump to function
	# PopParams 4
	  add $sp, $sp, 4	# pop params off stack
	# _tmp52 = 1
	  li $t2, 1		# load constant value 1 into $t2
	  sw $t2, -228($fp)	# spill _tmp52 from $t2 to $fp-228
	# _tmp53 = i + _tmp52
	  lw $t0, -56($fp)	# fill i to $t0 from $fp-56
	  lw $t1, -228($fp)	# fill _tmp52 to $t1 from $fp-228
	  add $t2, $t0, $t1	
	  sw $t2, -232($fp)	# spill _tmp53 from $t2 to $fp-232
	# i = _tmp53
	  lw $t2, -232($fp)	# fill _tmp53 to $t2 from $fp-232
	  sw $t2, -56($fp)	# spill i from $t2 to $fp-56
	# Goto _L1
	  b _L1		# unconditional branch
  _L2:
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
