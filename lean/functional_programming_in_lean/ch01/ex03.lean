-- Define a structure named RectangularPrism that contains the height, width, and depth of a rectangular prism, each as a Float.
structure PrismaRetangular where
  altura : Float
  largura : Float
  profundidade : Float
deriving Repr

-- Define a function named volume : RectangularPrism → Float that computes the volume of a rectangular prism.
def volume (p : PrismaRetangular) : Float := p.altura * p.largura * p.profundidade

-- Which names are introduced by the declaration of RectangularPrism?
-- structure que significa que estamos definindo uma estrutura, e Repr que significa que está sendo criada uma função para conseguir printar a estrutura.

def main : IO Unit :=
  IO.println (volume (PrismaRetangular.mk 1 2 3))
