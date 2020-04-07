def fatorial(n, mostrar=False):
    num = 1
    for c in range(0, n):
        if mostrar == True:
            if c == 0:
                print(f' {n} ', end='')
            else:
                print(f'x {n - c} ', end='')
        num *= (n - c)
    if mostrar == True:
        print('= ', end='')
    return num


print(fatorial(5, mostrar=True))