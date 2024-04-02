'''s1 = float(input('Primeiro segmento: '))
s2 = float(input('Segundo seguimento: '))
s3 = float(input('Terceiro seguimento: '))

if s1 == s2 == s3:
    tipo = 'equilátero'
elif s1 == s2 or s1 == s3 or s2 == s3:
    tipo = 'isósceles'
else:
    tipo = 'escaleno'

if s1 < s2 + s3 and s2 < s1 + s3 and s3 < s2 + s1:
    print('Os seguimentos acima \033[0;36;0mPODEM\033[m formar um triângulo do tipo \033[0;36;0m{}\033[m.'.format(tipo))

else:
    print('Os seguimentos \033[0;31;0mNÃO PODEM\033[m formar um triângulo.')'''

s1 = float(input('Primeiro número: '))
s2 = float(input('Segundo número: '))
s3 = float(input('Terceiro número: '))

if s1 < s2 + s3 and s2 < s1 + s3 and s3 + s2:
    print('Os seguimentos acima \033[0;36;0mPODEM\033[m formar um triângulo.')
    if s1 == s2 == s3:
        print('Esse triângulo seria do tipo \033[0;36;0mEQUILÁTERO\033[m.')
    elif s1 == s2 or s1 == s3 or s3 == s2:
        print('Esse triângulo seria do tipo \033[0;36;0mISÓSCELES\033[m')
    else:
        print('Esse triângulo seria do tipo \033[0;36;0mESCALENO\033[m')
else:
    print('Os seguimentos acima \033[0;31;0mNÃO\033[m podem formar um triângulo.')