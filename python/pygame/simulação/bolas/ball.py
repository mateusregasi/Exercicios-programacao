from pygame import draw
from circle_physics import CirclePhysics

class Ball:
    radius = 30
    color = (255,0,0)

    def __init__(self, x, y):
        self.circle = CirclePhysics(x, y, self.radius)
    
    def set_pos(self, x, y):
        self.circle.set_pos(x, y)
        self.circle.stop()

    def draw(self, surface):
        draw.circle(
            surface, 
            self.color, 
            (self.circle.x, self.circle.y), 
            self.circle.radius
        )
    
    def collidepoint(self, x, y):
        return self.circle.collidepoint(x, y)
    
    def update(self):
        self.circle.update()