-- Define a function volume with type Nat → Nat → Nat → Nat that computes the volume of a rectangular prism with the given height, width, and depth.
def vol (altura : Nat) (largura : Nat) (profundidade : Nat) :=
  altura * largura * profundidade

def main : IO Unit := IO.println (vol 1 2 3)
