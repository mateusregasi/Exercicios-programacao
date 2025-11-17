import numpy as np
import pygame
from pygame.locals import *
from time import sleep

colors = [(7, 7, 7), (31, 7, 7), (47, 15, 7), (71, 15, 7), (87, 23, 7), (103, 31, 7), (119, 31, 7), (143, 39, 7), (159, 47, 7), (175, 63, 7), (191, 71, 7), (199, 71, 7), (223, 79, 7), (223, 87, 7), (223, 87, 7), (215, 95, 7), (215, 95, 7), (215, 103, 15), (207, 111, 15), (207, 119, 15), (207, 127, 15), (207, 135, 23), (199, 135, 23), (199, 143, 23),(199, 151, 31), (191, 159, 31), (191, 159, 31), (191, 167, 39), (191, 167, 39), (191, 175, 47), (183, 175, 47), (183, 183, 47),(183, 183, 55), (207, 207, 111), (223, 223, 159), (239, 239, 199), (255, 255, 255)]
n_colors = len(colors)

# Variáveis
k = 100
Tt0 = 0
Tx0 = 100
Ty0 = 100
TLx = 100
TLy = 100
Lx = Ly = 100
dx = dy = 1
nx = ny = int(Lx / dx)
dt_max = dx**2 / (4.0 * k)
dt = min(0.1, dt_max)
max_temp = max(Tt0, Tx0, Ty0, TLx, TLy)
min_temp = min(Tt0, Tx0, Ty0, TLx, TLy)

# Monta a matriz inicial
T = np.zeros(dtype=np.double, shape=(nx, ny))
for i in range(1, nx-1):
    T[i][0] = Tx0
    T[0][i] = Ty0
    T[nx-1][i] = TLx
    T[i][ny-1] = TLy
I = np.fromfunction(lambda y, x: x, (nx, ny), dtype=np.int32)[1:nx-1, 1:ny-1]
J = np.fromfunction(lambda y, x: y, (nx, ny), dtype=np.int32)[1:nx-1, 1:ny-1]


PIXEL_SIZE = 8
HEIGHT = WIDTH = nx * PIXEL_SIZE

pygame.init()
window = pygame.display.set_mode((WIDTH, HEIGHT))

def foward():
    global T, dt, k
    T_next = T.copy()
    T_next[1:-1, 1:-1] = (T[1:-1, 1:-1] +
                          (dt * k) / (dx ** 2) *
                          (T[2:, 1:-1] + T[:-2, 1:-1] + T[1:-1, 2:] + T[1:-1, :-2] - 4 * T[1:-1, 1:-1]))
    T = T_next

def color(temp):
    global max_temp, min_temp
    c = min(int(round((temp - min_temp) / (max_temp-min_temp) * n_colors)), n_colors-1)
    return colors[c]

while True:
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            exit

    window.fill(color=(0,0,0))
    for i in range(nx):
        for j in range(ny):
            rect = (i*PIXEL_SIZE, j*PIXEL_SIZE, PIXEL_SIZE, PIXEL_SIZE)
            pygame.draw.rect(window, color(T[i, j]), rect=rect)

    pygame.display.update()
    foward()