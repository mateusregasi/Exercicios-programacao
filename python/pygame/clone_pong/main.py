# Mateus Regasi Gomes Martins

import pygame
import scenes
from pygame.locals import *


pygame.init()

# CONSTANTES
WIDTH, HEIGHT = 600, 600
CORES = {'black':(46, 40, 42), 'green':(132, 221, 99), 'white':(230, 250, 252), 'red':(239, 45, 86)}
# https://coolors.co/2e282a-ef2d56-84dd63-e6fafc
FPS = 30

# JANELA
janela = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Mateus Regasi Gomes Martins")
relogio = pygame.time.Clock()

# Variáveis iniciais
cenas = {'game':scenes.Game, 'menu':scenes.Menu}
args = {'janela':janela, 'width':WIDTH, 'height':HEIGHT, 'cores':CORES, 'fps':FPS, 'next_scene':None}
args['cena'] = scenes.Menu(args)

# GAMELOOP
tempo_atual = tempo_passado = 0
while True:

    # Define o FPS
    relogio.tick(FPS)
    
    # Calcula o deltaTime
    tempo_passado = tempo_atual
    tempo_atual = pygame.time.get_ticks()
    deltaTime = (tempo_atual - tempo_passado) / 1000
    args['deltaTime'] = deltaTime
    
    # Controla o loop da cena
    args['cena'].loop(args)

    # Troca de cena
    if args['next_scene']:
        del args['cena']
        args['cena'] = cenas[args['next_scene']](args)
        args['next_scene'] = None
        
    # Atualiza a tela
    pygame.display.flip()
