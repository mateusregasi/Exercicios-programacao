class Circle:

    def __init__(self, x, y, rad):
        self.x = x
        self.y = y
        self.radius = rad
    
    def collidepoint(self, x, y):
        return True if ((x-self.x) ** 2 + (y-self.y) ** 2) ** 0.5 <= self.radius else False

    def set_pos(self, x, y):
        self.x = x
        self.y = y