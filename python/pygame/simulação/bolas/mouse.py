import pygame

class Mouse():

    def __init__(self):
        self.pos = pygame.mouse.get_pos()
        self.x = self.pos[0]
        self.y = self.pos[1]
        self.pressed = pygame.mouse.get_pressed()
        self.holded = False
    
    def set_holded(self, holded):
        self.holded = holded

    def update_pos(self):
        self.pos = pygame.mouse.get_pos()
        self.x = self.pos[0]
        self.y = self.pos[1]

    def update_pressed(self):
        self.pressed = pygame.mouse.get_pressed()
    
    def update(self):
        self.update_pos()
        self.update_pressed()
        
    def get_pressed(self):
        return self.pressed