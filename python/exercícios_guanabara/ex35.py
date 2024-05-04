print('\033[0;33;0m-=-\033[m'*10)
print('\033[0;33;0m-\033[m'*2,'\033[0;31;0mANALIZADOR DE TRIÂNGULOS\033[m','\033[0;33;0m-\033[m'*2)
print('\033[0;33;0m-=-\033[m'*10)
r1 = float(input('\033[0;34;0mPrimeiro segmento: '))
r2 = float(input('Segundo segmento: '))
r3 = float(input('Terceiro segmento: \033[m'))
if r1 < r2 + r3 and r2 < r1 + r3 and r3 < r1 + r2:
    print('\033[0;32;0mOs segmentos acima podem formar um triângulo!\033[m')
else:
    print('\033[0;31;0mOs segmentos acima não podem formar um triângulo!\033[m')
print('\033[0;33;0m-'*13,'FIM','-'*13,'\033[m')