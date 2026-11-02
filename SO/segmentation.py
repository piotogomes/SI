#! /usr/bin/env python

import sys
from optparse import OptionParser
import random
import math

def convert(size):
    length = len(size)
    lastchar = size[length-1]
    if (lastchar == 'k') or (lastchar == 'K'):
        m = 1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'm') or (lastchar == 'M'):
        m = 1024*1024
        nsize = int(size[0:length-1]) * m
    elif (lastchar == 'g') or (lastchar == 'G'):
        m = 1024*1024*1024
        nsize = int(size[0:length-1]) * m
    else:
        nsize = int(size)
    return nsize


#
# main program
#
parser = OptionParser()
parser.add_option("-s", "--seed", default=0, help="a semente aleatoria", 
                  action="store", type="int", dest="seed")
parser.add_option("-A", "--addresses", default="-1",
                  help="uma lista de enderecos separados por virgula para serem acessadod; -1 para gerar aleatoriamente", 
                  action="store", type="string", dest="addresses")
parser.add_option("-a", "--asize", default="1k",
                  help="tamanho do espaco de enderecamento (e.g., 16, 64k, 32m, 1g)", 
                  action="store", type="string", dest="asize")
parser.add_option("-p", "--physmem", default="16k",
                  help="tamanho da memoria fisica (e.g., 16, 64k, 32m, 1g)", 
                  action="store", type="string", dest="psize")
parser.add_option("-n", "--numaddrs", default=5,
                  help="numero de enderecos virtuais a serem gerados",
                  action="store", type="int", dest="num")
parser.add_option("-b", "--b0", default="-1",
                  help="valor do registrador de base do segmento 0",
                  action="store", type="string", dest="base0")
parser.add_option("-l", "--l0", default="-1",
                  help="valor do registrador de limite do segmento 0",
                  action="store", type="string", dest="len0")
parser.add_option("-B", "--b1", default="-1",
                  help="valor do registrador de base do segmento 1",
                  action="store", type="string", dest="base1")
parser.add_option("-L", "--l1", default="-1",
                  help="valor do registrador de limite do segmento 1",
                  action="store", type="string", dest="len1")
parser.add_option("-c", help="calcular respostas",
                  action="store_true", default=False, dest="solve")


(options, args) = parser.parse_args()

print("ARG semente", options.seed)
print("ARG tamanho do espaco de enderecamento:", options.asize, "bytes")
print("ARG tamanho da memoria fisica:", options.psize, "bytes")
print("")

random.seed(options.seed)
asize = convert(options.asize)
psize = convert(options.psize)
addresses = str(options.addresses)

if psize <= 1:
    print('Erro: especifique um tamanho de memeoria fisica maior que zero.')
    exit(1)

if asize == 0:
    print('Erro: especifique um tamanho de espaco de enderecamento maior que zero.')
    exit(1)

if psize <= asize:
    print('Erro: a memoria fisica precisa ser maior que o espaco de enderecamento (neste simulador).')
    exit(1)

#
# need to generate base, bounds for segment registers
#
len0 = convert(options.len0)
len1 = convert(options.len1)
base0 = convert(options.base0)
base1 = convert(options.base1)

if len0 == -1:
    len0 = int(asize/4.0 + (asize/4.0 * random.random()))

if len1 == -1:
    len1 = int(asize/4.0 + (asize/4.0 * random.random()))

# now have to find room for them
if base0 == -1:
    done = 0
    while done == 0:
        base0 = int(psize * random.random())
        if (base0 + len0) < psize:
            done = 1

# internally, base1 points to the lower address, and base1+len1 the higher address
# (this differs from what the user would pass in, for example)
if base1 == -1:
    done = 0
    while done == 0:
        base1 = int(psize * random.random())
        if (base1 + len1) < psize:
            if (base1 > (base0 + len0)) or ((base1 + len1) < base0):
                done = 1
else:
    base1 = base1 - len1


if len0 > asize/2.0 or len1 > asize/2.0:
    print('Error: length register is too large for this address space')
    exit(1)


# print 'Segment register information:'
# print ''
# print '  Segment 0 base  (grows positive) : 0x%08x (decimal %d)' % (base0, base0)
# print '  Segment 0 limit                  : %d' % (len0)
# print ''
# print '  Segment 1 base  (grows negative) : 0x%08x (decimal %d)' % (base1+len1, base1+len1)
# print '  Segment 1 limit                  : %d' % (len1)
# print ''
print('Informacoes dos registradores dos segmentos:')
print('')
print('  Segmento 0 base  (cresce para frente) : 0x%08x (decimal %d)' % (base0, base0))
print('  Segmento 0 limite                     : %d' % (len0))
print('')
print('  Segmento 1 base  (cresce para trás) : 0x%08x (decimal %d)' % (base1+len1, base1+len1))
print('  Segmento 1 limite                   : %d' % (len1))
print('')
nbase1  = base1 + len1

if (len0 + base0) > (base1) and (base1 > base0):
    print('Erro: segmentos se sobrepoe na memoria fisica')
    exit(1)


addrList = []
if addresses == '-1':
    # need to generate addresses
    for i in range(0, options.num):
        n = int(asize * random.random())
        addrList.append(n)
else:
    addrList = addresses.split(',')

#
# now, need to generate virtual address trace
#
print('Virtual Address (VA) Trace')
i = 0
for vStr in addrList:
    # vaddr = int(asize * random.random())
    vaddr = int(vStr)
    if vaddr < 0 or vaddr >= asize:
        print('Erro: virtual address %d nao pode ser gerado em um espaco de enderecamento de tamanho %d' % (vaddr, asize))
        exit(1)
    if options.solve == False:
        print('  VA %2d: 0x%08x (decimal: %4d) --> Gera um endereco fisico (qual?) or uma violacao de segmentacao?' % (i, vaddr, vaddr))
    else:
        paddr = 0
        if (vaddr >= (asize / 2)):
            # seg 1
            paddr = nbase1 + (vaddr - asize)
            if paddr < base1:
                print('  VA %2d: 0x%08x (decimal: %4d) --> VIOLACAO DE SEGMENTACAO (SEG1)' % (i, vaddr, vaddr))
            else:
                print('  VA %2d: 0x%08x (decimal: %4d) --> VALIDO no SEG1: 0x%08x (decimal: %4d)' % (i, vaddr, vaddr, paddr, paddr))
        else:
            # seg 0
            if (vaddr >= len0):
                print('  VA %2d: 0x%08x (decimal: %4d) --> VIOLACAO DE SEGMENTACAO (SEG0)' % (i, vaddr, vaddr))
            else:
                paddr = vaddr + base0
                print('  VA %2d: 0x%08x (decimal: %4d) --> VALIDO no SEG0: 0x%08x (decimal: %4d)' % (i, vaddr, vaddr, paddr, paddr))
    i += 1

print('')

if options.solve == False:
#    print 'For each virtual address, either write down the physical address it translates to'
#    print 'OR write down that it is an out-of-bounds address (a segmentation violation). For'
#    print 'this problem, you should assume a simple address space with two segments: the top'
#    print 'bit of the virtual address can thus be used to check whether the virtual address'
#    print 'is in segment 0 (topbit=0) or segment 1 (topbit=1). Note that the base/limit pairs'
#    print 'given to you grow in different directions, depending on the segment, i.e., segment 0'
#    print 'grows in the positive direction, whereas segment 1 in the negative. '
#    print ''

    print("Para cada endereco virtual, anote o endereco fisico resultante OU anote que e\' um endereco fora dos limites (uma violacao de segmentacao).")
    print("Para este problema, voce deve assumir um espaco de enderecamento simples com dois segmentos.")
    print("Portanto, o bit mais significativo do endereco virtual pode ser usado para verificar se o endereco virtual")
    print("esta\' no segmento 0 (bit mais significativo==0) ou no segmento 1 (bit mais significativo==1).")
    print("Observe que o segmento 0 cresce na direcao positiva, enquanto o segmento 1 na negativa.")
    print()

