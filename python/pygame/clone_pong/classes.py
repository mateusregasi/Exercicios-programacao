import pygame
from random import randint

class Bolinha:
    
    def __init__(self, args):
        
        # Posição e tamanho
        self.w = self.h = 50 
        self.setPos(args)
        
        # Sprite
        self.sprite = pygame.image.load("bola.png").convert_alpha()
        self.sprite = pygame.transform.scale(self.sprite, (self.w, self.h))
        self.rect = pygame.Rect(self.x, self.y, self.w, self.h)

    def setPos(self, args):

        # Velocidade da bolinha
        self.velx = self.vely = 300

        # Posição (inicia a bolinha no meio da tela)
        self.x = args['width'] // 2 - self.w // 2
        self.y = args['height'] // 2 - self.w // 2

        # Direção (deixa a direção da bolinha aleatoria)
        self.dirx = randint(0, 1)
        self.diry = randint(0, 1)
        self.velx = self.velx if self.dirx == 1 else -self.velx
        self.vely = self.vely if self.diry == 1 else -self.vely
        
    def loop(self, args):

        # Verifica se a bola vazou da tela
        if ((self.x + self.w) < 0) or (self.x - 2 * self.w) >= args['width']:
            del args['y_bolinha']
            args['next_scene'] = 'menu'
        
        # Verifica se bateu na parede e altera a velocidade
        if (self.y < 0 and self.diry == 0) or (self.y > (args['height'] - self.h) and self.diry == 1):
            self.vely *= -1
            self.diry = 1 if self.diry == 0 else 0

        # Verifica se bateu na parte da frente do personagem e altera a velocidade
        else:
            if(self.rect.colliderect(args['jogador1'].rect_top) and self.diry == 1) or (self.rect.colliderect(args['jogador2'].rect_buttom) and self.diry == 0):
                self.velx = -self.velx
                self.dirx = 0 if self.dirx == 1 else 1
            if(self.rect.colliderect(args['jogador1'].rect_right) and self.dirx == 0) or (self.rect.colliderect(args['jogador2'].rect_left) and self.dirx == 1):
                self.velx *= -1
                self.dirx = 0 if self.dirx == 1 else 1
        
        # Altera a posição
        self.x += int(self.velx * args['deltaTime'])
        self.y += int(self.vely * args['deltaTime'])

        # Desenha o personagem
        args['janela'].blit(self.sprite, (self.x, self.y))
        self.rect = pygame.Rect(self.x, self.y, self.w, self.h)

        # Altera a direção da bolinha
        args['y_bolinha'] = self.y
        self.velx += 1
        self.vely += 1

class Jogador:

    def __init__(self, args, lado, tipo, teclas=''):
        global WIDTH, HEIGHT

        # Tamanho e posição
        self.w = 10
        self.h = 100
        self.x = 5 if lado == 0 else args['width'] - self.w - 5 
        self.y = args['height'] // 2 - self.h // 2
        self.vely = 500

        self._get_rect()

        # Define o tipo de jogador = player ou ia
        self.tipo = tipo

        # Define as teclas
        self.teclas = teclas

        self.incerteza = 0
        self.sense = 1

    # Loop do jogador
    def loop(self, args):
        self.move(args)
        self.draw(args)

    def _get_rect(self):

        self.rect_top = pygame.Rect(self.x, self.y, self.w, 1)
        self.rect_buttom = pygame.Rect(self.x, self.y + self.h, self.w, 1)
        self.rect_right = pygame.Rect(self.x + self.w, self.y, 1, self.h)
        self.rect_left = pygame.Rect(self.x, self.y, 1, self.h)

    # Controla as teclas do jogador e seu resultado
    def control_player(self, args):
        if pygame.key.get_pressed()[self.teclas[1]]:
            self.y -= int(self.vely * args['deltaTime'])
        if pygame.key.get_pressed()[self.teclas[0]]:
            self.y += int(self.vely * args['deltaTime'])

    # Controla a IA do jogo
    def control_ia(self, args):

        # Controla o sentido da IA
        if self.sense == 75:
            self.sense = randint(self.sense * 50, self.sense * 100)
        if self.sense > 75:
            self.sense -= 1
        elif self.sense < 75:
            self.sense += 1

        # Controla a incerteza da IA
        if self.incerteza == 0:
            self.incerteza = randint(-10, 100)
        if self.incerteza >= 0:
            i = 1
        else: 
            i = -1
        self.incerteza += 1 if self.incerteza < 1 else -1

        if args['y_bolinha'] < self.y - self.sense:
            self.y -= i * int(self.vely * args['deltaTime'])
        elif args['y_bolinha'] > (self.y + self.h) + self.sense:
            self.y += i * int(self.vely * args['deltaTime'])

    def move(self, args):

        # Movimentação do personagem
        if(self.tipo == 'player'):
            self.control_player(args)
        elif(self.tipo == 'ia'):
            self.control_ia(args)

        if self.y <= 0:
            self.y = 0
        elif self.y >= (args['height'] - self.h):
            self.y = (args['height'] - self.h)

        self._get_rect()

    def draw(self, args):

        pygame.draw.rect(args['janela'], args['cores']['red'], (self.x, self.y, self.w, self.h))
