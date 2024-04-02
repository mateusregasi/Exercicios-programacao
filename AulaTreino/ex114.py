from urllib import request


try:
    pudim = request.urlopen('http://www.pudim.com.br')
except:
    print('O site Pudim não está acessível.')
else:
    print('O site Pudim está acessível.')
