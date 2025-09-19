-- Define the function joinStringsWith with type String → String → String → String that creates a new string by placing its first argument between its second and third arguments. joinStringsWith ", " "one" "and another" should evaluate to "one, and another".
def juntarStringsCom (sep : String) (s1 : String) (s2 : String) :=
  String.append (String.append s1 sep) s2

def main : IO Unit :=
  IO.println (juntarStringsCom ", " "um" "e outro")

-- What is the type of joinStringsWith ": "? Check your answer with Lean.
#check (juntarStringsCom ": ")
