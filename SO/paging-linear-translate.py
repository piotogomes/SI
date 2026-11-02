#! /usr/bin/env python

import sys
from optparse import OptionParser
import random
import math

def mustbepowerof2(bits, size, msg):
    if math.pow(2,bits) != size:
        print('Error in argument: %s' % msg)
        sys.exit(1)

def mustbemultipleof(bignum, num, msg):
    if (int(float(bignum)/float(num)) != (int(bignum) / int(num))):
        print('Error in argument: %s' % msg)
        sys.exit(1)

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
parser.add_option('-A', '--addresses', default='-1',
                  help='a set of comma-separated pages to access; -1 means randomly generate', 
                  action='store', type='string', dest='addresses')
parser.add_option('-s', '--seed',    default=0,     help='semente',                               action='store', type='int', dest='seed')
parser.add_option('-a', '--asize',   default='16k', help='tamanho do espaco de enderecamento (e.g., 16, 64k, 32m, 1g)',   action='store', type='string', dest='asize')
parser.add_option('-p', '--physmem', default='64k', help='tamanho da memoria fisica (e.g., 16, 64k, 32m, 1g)', action='store', type='string', dest='psize')
parser.add_option('-P', '--pagesize', default='4k', help='tamanho da pagina (e.g., 4k, 8k, whatever)',            action='store', type='string', dest='pagesize')
parser.add_option('-n', '--numaddrs',  default=5,   help='numero de enderecos virtuais para gerar',       action='store', type='int', dest='num')
parser.add_option('-u', '--used',       default=50, help='porcentagem de paginas usadas', action='store', type='int', dest='used')
parser.add_option('-v',                             help='verbose mode',                                  action='store_true', default=False, dest='verbose')
parser.add_option('-c',                             help='computar traducao de enderecos',                        action='store_true', default=False, dest='solve')


(options, args) = parser.parse_args()

print('ARG semente',                            options.seed)
print('ARG tamanho do espaco de enderecamento', options.asize)
print('ARG tamanho da memoria fisica',          options.psize)
print('ARG tamanho da pagina',                  options.pagesize)
print('ARG verbose',                            options.verbose)
print('ARG enderecos',                          options.addresses)
print('')

random.seed(options.seed)

asize    = convert(options.asize)
psize    = convert(options.psize)
pagesize = convert(options.pagesize)
addresses = str(options.addresses)

if psize <= 1:
    print('Erro: tamanho de memoria fisica invalido.')
    exit(1)

if asize < 1:
    print('Erro: tamanho de espaco de enderecamento invalido.')
    exit(1)

if psize <= asize:
    print('Erro: memoria fisica precisa ser MAIOR que o espaco de enderecamento (para este simulador especificamente)')
    exit(1)

if psize >= convert('1g') or asize >= convert('1g'):
    print('Erro: tamanhos devem ser menor que 1GB para este simulador.')
    exit(1)

mustbemultipleof(asize, pagesize, 'tamanho espaco de enderecamento deve ser multiplo do tamanho de pagina')
mustbemultipleof(psize, pagesize, 'tamanho da memoria fisica deve ser multiplo do tamanho de pagina')

# print(some useful info, like the darn page table )
pages = psize // pagesize;
import array
used = array.array('i')
pt   = array.array('i')
for i in range(0,pages):
    used.insert(i,0)
vpages = asize // pagesize

# now, assign some pages of the VA
vabits   = int(math.log(float(asize))/math.log(2.0))
mustbepowerof2(vabits, asize, 'tamanho do espaco de enderecamento deve ser uma potencia de 2')
pagebits = int(math.log(float(pagesize))/math.log(2.0))
mustbepowerof2(pagebits, pagesize, 'tamanho de pagina deve ser uma potencia de 2')
vpnbits  = vabits - pagebits
pagemask = (1 << pagebits) - 1

# import ctypes
# vpnmask  = ctypes.c_uint32(~pagemask).value
vpnmask = 0xFFFFFFFF & ~pagemask
#if vpnmask2 != vpnmask:
#    print('ERROR')
#    exit(1)
# print('va:%d page:%d vpn:%d -- %08x %08x' % (vabits, pagebits, vpnbits, vpnmask, pagemask))

print('')
print('The format of the page table is simple:')
print('The high-order (left-most) bit is the VALID bit.')
print('  If the bit is 1, the rest of the entry is the PFN.')
print('  If the bit is 0, the page is not valid.')
print('Use verbose mode (-v) if you want to print the VPN # by')
print('each entry of the page table.')
print('')

print('')
print('O formato da tabela de paginacao eh simples:')
print('O bit mais significativo (mais a esquerda) eh o bit VALIDO.')
print('  Se este bit for 1, o resto da entrada da tabela representa o PFN (numero do page frame).')
print('  Se este bit for 0, a pagina nao eh valida.')
print('Use o modo verboso (-v) para mostar o indice da tabela (equivalente ao numero da pagina virtual - VPN)')
print('')

print('Tabela de paginacao (inciando do indice 0 ate o indice maximo)')
for v in range(0,vpages):
    done = 0
    while done == 0:
        if ((random.random() * 100.0) > (100.0 - float(options.used))):
            u = int(pages * random.random())
            if used[u] == 0:
                used[u] = 1
                done = 1
                # print('%8d - %d' % (v, u))
                if options.verbose == True:
                    print('  [%8d]  ' % v, end="")
                else:
                    print('  ', end="")
                print('0x%08x' % (0x80000000 | u))
                pt.insert(v,u)
        else:
            # print('%8d - not valid' % v)
            if options.verbose == True:
                print('  [%8d]  ' % v, end="")
            else:
                print('  ', end="")
            print('0x%08x' % 0)
            pt.insert(v,-1)
            done = 1
print(''            )


#
# now, need to generate virtual address trace
#

addrList = []
if addresses == '-1':
    # need to generate addresses
    for i in range(0, options.num):
        n = int(asize * random.random())
        addrList.append(n)
else:
    addrList = addresses.split(',')


print('Enderecos virtuais (VA - virtual address)')
for vStr in addrList:
    # vaddr = int(asize * random.random())
    vaddr = int(vStr)
    if options.solve == False:
        print('  VA 0x%08x (decimal: %8d) --> Calcule o endereco fisico ou indique se o acesso eh invalido' % (vaddr, vaddr))
    else:
        paddr = 0
        # split vaddr into VPN | offset
        vpn = (vaddr & vpnmask) >> pagebits
        if pt[vpn] < 0:
            print('  VA 0x%08x (decimal: %8d) -->  Invalido (VPN %d invalida)' % (vaddr, vaddr, vpn))
        else:
            pfn    = pt[vpn]
            offset = vaddr & pagemask
            paddr  = (pfn << pagebits) | offset
            print('  VA 0x%08x (decimal: %8d) --> %08x (decimal %8d) [VPN %d]' % (vaddr, vaddr, paddr, paddr, vpn))
print('')








