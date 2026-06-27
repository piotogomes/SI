.text
.globl main
main:
        li $v0, 5
        syscall
        move $a0,$v0
        li $v0, 5
        syscall
        move $a1,$v0
        li $t0, 1               
        jal mdc              
        li $v0,1                         # imprime o resultado
        syscall
        li $v0,10                        # termina
        syscall        
mdc:
	bnez $t0, mdc_exec
	move $a1, $v0 
        j mdc_fim                        # vai para o final
mdc_exec:
	subu $sp,$sp,12              # Abre um espaco na pilha
	sw $ra,0($sp)                # Salva o endereco de retorno
        sw $a0,4($sp)               	
        sw $a1,8($sp)
        div $a0,$a1
       	mfhi $t0   
        move $a0, $a1
        move $a1, $t0                
        jal mdc                	
        lw $ra,0($sp)                
        addu $sp,$sp,12               # retira o espaco ocupado na pilha
           
mdc_fim:
        jr $ra                                # retorna
