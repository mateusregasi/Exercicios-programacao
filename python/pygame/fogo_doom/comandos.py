from random import randint


def criarMatriz(alt, lar, pxt=1):
    """
    -> Cria uma matriz com as posições, com altura, largura e o tamanho do pixel.
    """
    matriz = []
    for coluna in range(0, alt * pxt, pxt):
        for linha in range(0, lar * pxt, pxt):
            matriz.append((linha, coluna))
    return matriz
def criarFogo(matriz):
    """
    -> Adiciona os valores de cores as posições da matriz.
    """
    fogo = {}
    for pos in matriz:
        if pos[1] == matriz[-1][1]:
            fogo[pos] = 36
        else:
            fogo[pos] = 0
    return fogo
def fogoProp(fogo, pixel=1, prop=10):
    """
    -> Comportamento de propagação do fogo, ou seja como ele se espalha.
    """
    for pos, fi in fogo.items():
        if fogo[pos] != 36:
            fogo[pos] = fogo[pos[0], pos[1] + pixel] - randint(1, prop)
            if fogo[pos] < 0:
                fogo[pos] = 0
    return fogo
