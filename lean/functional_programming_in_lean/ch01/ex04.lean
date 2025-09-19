-- Define a structure named Segment that represents a line segment by its endpoints, and define a function length : Segment → Float that computes the length of a line segment. Segment should have at most two fields.
structure Ponto where
  x : Float
  y : Float
deriving Repr

structure Segmento where
  p1 : Ponto
  p2 : Ponto
deriving Repr

def distancia (s : Segmento) : Float :=
  Float.sqrt (((s.p2.x - s.p1.x) ^ 2) + ((s.p2.y - s.p1.y) ^ 2))

def main : IO Unit :=
  IO.println (distancia (Segmento.mk (Ponto.mk 1 1) (Ponto.mk 2 2)))

-- Which names are introduced by the following declarations of Hamster and Book? What are their types?

-- structure Hamster where
--   name : String
--   fluffy : Bool
-- structure Book where
--   makeBook ::
--   title : String
--   author : String
--   price : Float

-- nome :: representa o construtor da classe, seus tipos são, para Hamster tem nome com String, fluffy como booleano, já o Book tem como título e autor String e preço um float
