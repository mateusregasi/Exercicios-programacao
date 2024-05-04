print('=' * 20)
print('10 TERMOS DE UMA PA')
print('=' * 20)

num = int(input('Primeiro termo: '))
razao = int(input('Razão: '))

for c in range(0, 10):
    print(num + razao * c, end=" → ")
print('Acabou.')
