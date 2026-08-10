.text
.globl main
main:
        li $v0, 5		# Especifica leitura para syscall
        syscall         # entra valor de a
        move $a0,$v0	# variável "a" guardada em a0
        li $v0, 5		
        syscall		# entra valor de b
        move $a1,$v0	# variável "b" guardada em a1
        li $t0, 1   	# Resto é definido como 1 para primeira execução       
        jal mdc           # pula para mdc e salva endereço de retorno
        bltz $a0, negativo              # Se "a" for menor que zero...
        li $v0,1		# específica impressão para syscall
        syscall
        li $v0,10         # termina o programa
        syscall        
mdc:
        beqz $a1, mdc_fim   # Se "b" == 0, ramifica até etiqueta "zero" 
	bnez $t0, mdc_exec		      # Se "resto" nao for igual a zero...

        j mdc_fim                    # pula para mdc_fim
mdc_exec:
	subu $sp,$sp,12              	# Abre um espaço na pilha para 3 variaveis de 4 bytes cada
	sw $ra,0($sp)                	# Salva o endereço de retorno
       sw $a0,4($sp)               	# Salva endereço do "a"
       sw $a1,8($sp)			# Salva endereço do "b"
       div $a0,$a1			# Divide "a" por "b"
      	mfhi $t0   			# Move resto da operação para t0 ("resto")
       move $a0, $a1			# valor de "b" movido para "a"
       move $a1, $t0               	# valor do resto será armazenado em "a"
       jal mdc				# pula para mdc e guarda endereço atual
       lw $ra,0($sp)                # le endereço de retorno que estava na pilha
       addu $sp,$sp,12              # retira o espaço ocupado na pilha
           
 mdc_fim:
        jr $ra

negativo:
	mul $a0, $a0, -1
	jr $ra