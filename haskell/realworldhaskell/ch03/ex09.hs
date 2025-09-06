-- Consider three two-dimensional points a, b, and c. If we look at the angle formed by the line segment from a to b and the line segment from b to c, it either turns left, turns right, or forms a straight line. Define a Direction data type that lets you represent these possibilities.

data Point = Point Int Int deriving (Show)
pa = Point 10 10
pb = Point 6 1
pc = Point 4 9 

direcao :: Point -> Point -> [Char]
direcao (Point x _) (Point y _) | x == y = "straight"
direcao (Point x _) (Point y _) | y-x > 0 = "direita"
direcao (Point x _) (Point y _) | y-x < 0 = "esquerda"

main :: IO ()
main = do
    print (direcao pa pb)
    print (direcao pb pa)
    print (direcao pb pc)
    print (direcao pa pc)
