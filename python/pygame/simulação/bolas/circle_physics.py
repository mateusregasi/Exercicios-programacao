from circle import Circle
from physics import Physics

class CirclePhysics(Circle, Physics):

    def __init__(self, x, y, rad):
        Circle.__init__(self, x, y, rad)
        Physics.__init__(self, self)
    