import pygame
from pygame.locals import *

from conf import WINDOW_SIZE, WIDTH, HEIGHT
from ball import Ball
from mouse import Mouse
from rectangle import Rectangle

class Game:

    def __init__(self):
        pygame.init()
        self._init_window()
        self.ball = Ball(WIDTH/2, HEIGHT/2)
        self.mouse = Mouse()

        rectangle_sizeX = 300
        rectangle_sizeY = 30
        self.floor = Rectangle(
            WIDTH/2 - rectangle_sizeX/2,
            HEIGHT - rectangle_sizeY - 10,
            rectangle_sizeX,
            rectangle_sizeY
        )

    def _init_window(self):
        self.window = pygame.display.set_mode(WINDOW_SIZE)
        pygame.display.set_caption("Bolinha")

    def loop(self):
        self.update()
        self.events()      
        self.draw()

    def events(self):
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                exit
            elif event.type == MOUSEBUTTONDOWN:
                self.mouse.set_holded(True)

            elif event.type == MOUSEBUTTONUP:
                self.mouse.set_holded(False)
            
            elif event.type == MOUSEMOTION:
                if self.mouse.holded:
                    mx = self.mouse.x
                    my = self.mouse.y
                    self.ball.set_pos(mx, my)  
                

    def update(self):
        self.mouse.update()
        self.ball.update()
        self.floor.update()

    def draw(self):
        self.window.fill((0,0,0))
        self.ball.draw(self.window)
        self.floor.draw(self.window)
        pygame.display.update()