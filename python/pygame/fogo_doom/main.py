from pygame import *
from random import randint

#Definições da janela
MW, MH = 50, 50
PIXEL = 20
DIM = WIDHT, HEIGHT = MW * PIXEL, MH * PIXEL

screen = display.set_mode(DIM)

#Lista de cores do fogo do Doom
colors = [(7, 7, 7), (31, 7, 7), (47, 15, 7), (71, 15, 7), (87, 23, 7), (103, 31, 7), (119, 31, 7), (143, 39, 7), (159, 47, 7), (175, 63, 7), (191, 71, 7), (199, 71, 7), (223, 79, 7), (223, 87, 7), (223, 87, 7), (215, 95, 7), (215, 95, 7), (215, 103, 15), (207, 111, 15), (207, 119, 15), (207, 127, 15), (207, 135, 23), (199, 135, 23), (199, 143, 23),(199, 151, 31), (191, 159, 31), (191, 159, 31), (191, 167, 39), (191, 167, 39), (191, 175, 47), (183, 175, 47), (183, 183, 47),(183, 183, 55), (207, 207, 111), (223, 223, 159), (239, 239, 199), (255, 255, 255)]

def createFlame(w, h):
    mat = {}
    for i in range(0, h*(w-1)+1):
        mat[i] = 0
    for i in range(h*(w-1), h*w):
        mat[i] = 36
    return mat
def propagateFlame(mat, w, prop=2):
    for pos, color in mat.items():
        if mat[pos] != 36:
            p = randint(1, prop)
            posd = pos+w
            if posd < len(mat) and pos-p > 0:
                mat[pos-p] = mat[posd] - p if mat[posd] - p >= 0 else 0
    return mat

def drawFlame(mat, w, pixel, screen, colors):
    for pos, cor in mat.items():
        x = (pos % w)*pixel
        y = (pos // w)*pixel
        draw.rect(screen, colors[cor], (x, y, x+pixel, y+pixel))

#Define o fps
fps = time.Clock()

#Define as posições do fogo
mat = createFlame(MW, MH)

init()

#Loop
while True:
    fps.tick(30)

    #Loop de eventos
    for eventos in event.get():
        if eventos.type == QUIT:
            exit()

    #Pinta cada pixel com a determinada cor:    
    drawFlame(mat, MW, PIXEL, screen, colors)
    
    #Propagação do fogo (atualiza os pixels e os valores)
    propagateFlame(mat, MW)

    #Da Update de tela
    display.update()