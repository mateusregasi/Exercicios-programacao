import pygame
from pygame.locals import *
from classes import *

class Game:

    def __init__(self, args):

        # Iniciando os objetos
        self.bolinha = Bolinha(args)
        self.jogador1 = Jogador(args, 0, 'player', {1:K_w, 0:K_s})
        self.jogador2 = Jogador(args, 1, 'ia', {1:K_UP, 0:K_DOWN})

        # Colocando os objetos no args
        args['jogador1'] = self.jogador1
        args['jogador2'] = self.jogador2
        
        # Define o fundo
        self.fundo = pygame.image.load('campo.png').convert()
        self.fundo = pygame.transform.scale(self.fundo, (args['width'], args['height']))

    def loop(self, args):

        # Desenha o fundo
        args['janela'].blit(self.fundo, (0,0))
        
        # Aciona o loop da bolinha e dos jogadores
        self.bolinha.loop(args)
        self.jogador1.loop(args)
        self.jogador2.loop(args)

        # Condição de saída do jogo
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                exit()

class Menu:

    def __init__(self, args):

        # Background do Menu
        self.background_color = args['cores']['white']

        #   Textos do menu
        # Título
        self.titulo = {}
        self.titulo['fonte'] = pygame.font.SysFont('roboto', 150, True)
        self.titulo['formatada'] = self.titulo['fonte'].render('Pong', args['cores']['white'], True)
        self.titulo['tamanho'] = self.titulo['fonte'].size('Pong')
        self.titulo['posx'] = args['width'] // 2 - self.titulo['tamanho'][0] // 2
        self.titulo['posy'] = args['height'] // 2 - self.titulo['tamanho'][1] // 2 - args['height'] // 10

        # Sub-título
        self.subtitulo = {}
        self.subtitulo['fonte'] = pygame.font.SysFont('roboto', 20, True)
        self.subtitulo['formatada'] = self.subtitulo['fonte'].render('Aperte espaço para continuar', args['cores']['red'], False)
        self.subtitulo['tamanho'] = self.subtitulo['fonte'].size('Aperte espaço para continuar')
        self.subtitulo['posx'] = args['width'] // 2 - self.subtitulo['tamanho'][0] // 2
        self.subtitulo['posy'] = args['height'] // 2 - self.subtitulo['tamanho'][1] // 2 + args['height'] // 12

    def loop(self, args):

        # Background
        args['janela'].fill(self.background_color)

        # Titulo
        args['janela'].blit(self.titulo['formatada'], (self.titulo['posx'],self.titulo['posy']))
        args['janela'].blit(self.subtitulo['formatada'], (self.subtitulo['posx'],self.subtitulo['posy']))

        for event in pygame.event.get():
            if event.type == KEYDOWN:

                # Entra no jogo (Space)
                if event.key == K_SPACE:
                    args['next_scene'] = 'game'

                # Sai do jogo (X | Esc)
                if event.key == K_ESCAPE:
                    pygame.quit()
                    exit()
            if event.type == QUIT:
                pygame.quit()
                exit()