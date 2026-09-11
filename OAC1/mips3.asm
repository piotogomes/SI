.text

main:	
	addi $t0, $zero, 20  
	addi $t1, $zero, 13
	addi $t2, $zero, 267
	addi $t3, $zero, 1
	addi $t4, $zero, -250
	addi $t1, $t1, -10
	mulo $t0, $t0, $t1
	mulo $t3, $t3, $t4
	add $t2, $t2, $t3
	div $t0, $t0, $t2
	
	move $a0, $t0
	
	addi $v0, $zero, 1
	syscall    