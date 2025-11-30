import pygame
from conf import COLOR_WHITE

class Rectangle:

    def __init__(self, x, y, w, h, color=COLOR_WHITE):
        self.x = x
        self.y = y
        self.w = w
        self.h = h
        self.color = color

    def draw(self, window):
        pygame.draw.rect(
            window, 
            self.color, 
            (
                self.x, 
                self.y, 
                self.w, 
                self.h
            )
        )
    
    def update(self):
        pass