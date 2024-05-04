peso = float(input('Qual é o seu peso? (kg) '))
altura = float(input('Qual é a sua altura? (m) '))
imc = peso / altura ** 2

print('O IMC dessa pessoa é de {:.1f}'.format(imc))

if imc < 18.5:
    print('\033[0;31;0mVocê está abaixo do peso ideal!\033[m')
elif imc > 18.4 and imc < 25:
    print('\033[0;36;0mVocê esta no peso ideal!\033[m')
elif imc > 24.9 and imc < 30:
    print('\033[0;32;0mQue pena... Você está com sobrepeso...\033[m')
elif imc > 29.9 and imc < 40:
    print('\033[0;33;0mSinto muito... Você está obeso(a).\033[m')
elif imc > 39.9:
    print('\033[0;31;0mVocê precisa de um nutricionista. Está com obesidade mórbida\033[m')