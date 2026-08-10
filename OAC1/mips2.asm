.text
.globl main
main:
        ld $a1,$idade                # carrega a idade da memoria
        blt $a1,18,menor        # verifica se a idade eh menor que 18
        la $a0,$texto1                # idade maior
        j fim                                # idade menor
menor:
        la $a0,$texto2
fim:
        li $v0,4                        # imprime o texto
        syscall                                # termina
        li $v0,10
        syscall
.data
$idade: .word 10
$texto1: .asciiz "Sim"
$texto2: .asciiz "Nao"