class Physics:
    gravity = True
    gravity_force = 1
    m = 1000

    vx = 0
    vy = 0
    ax = 0
    ay = 0

    def __init__(self, shape):
        self.shape = shape
        if(self.gravity): self.ay = self.gravity_force

    def update(self):
        if(self.gravity): self.vy = self.vy + self.gravity_force/self.m
        self._apply_force2shape()
    
    def apply_force(self, fx=0, fy=0):
        self.ax += fx/self.m
        self.ay += fy/self.m
    
    def stop(self):
        self.vx = 0
        self.vy = 0

    def _apply_force2shape(self):
        print(self.shape.x, self.shape.y)
        self.shape.x += self.vx
        self.shape.y += self.vy
        print(self.shape.x, self.shape.y)
        print()
