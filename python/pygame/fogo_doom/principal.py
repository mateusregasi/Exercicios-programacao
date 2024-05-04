from pygame import *
from comandos import *


#Definições da janela
tamanhoJanela = altura, largura = 500, 500
tela = display.set_mode(tamanhoJanela)
init()

#Lista de cores do fogo do Doom
listaCores = [(7, 7, 7), (31, 7, 7), (47, 15, 7), (71, 15, 7), (87, 23, 7), (103, 31, 7), (119, 31, 7), (143, 39, 7), (159, 47, 7), (175, 63, 7), (191, 71, 7), (199, 71, 7), (223, 79, 7), (223, 87, 7), (223, 87, 7), (215, 95, 7), (215, 95, 7), (215, 103, 15), (207, 111, 15), (207, 119, 15), (207, 127, 15), (207, 135, 23), (199, 135, 23), (199, 143, 23),
          (199, 151, 31), (191, 159, 31), (191, 159, 31), (191, 167, 39), (191, 167, 39), (191, 175, 47), (183, 175, 47), (183, 183, 47),
          (183, 183, 55), (207, 207, 111), (223, 223, 159), (239, 239, 199), (255, 255, 255)]

#Define o fps
fps = time.Clock()
#Define o pixel e a área do pixel
pixel = 10
pixelArea = (pixel, pixel)

#Define as posições do fogo
matriz = criarMatriz(50, 50, pixel)
#Coloca um valor de 0 a 36 em cada valor
fogo = criarFogo(matriz)
#Define o tamanho do pixel para cada espaço da matriz.
pxl = Surface(pixelArea)


#Loop
while True:
    #Aplica o fps a 30
    fps.tick(30)
    #Loop de eventos
    for eventos in event.get():
        if eventos.type == QUIT:
            exit()
    #Pinta cada pixel com a determinada cor:    
    for pos, cor in fogo.items():
        tela.blit(pxl, [pos[0], pos[1]])
        pxl.fill(listaCores[cor])
    #Propagação do fogo(atualiza os pixels e os valores)
    fogo = fogoProp(fogo, pixel, 4)
    #Da Update de tela
    display.update()