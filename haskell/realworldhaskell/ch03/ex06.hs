-- 7) Create a function that sorts a list of lists based on the length of each sublist. (You may want to look at the sortBy function from the Data.List module.) 
size :: [a] -> Int
size [] = 0
size (h:t) = (size t) + 1

cmp :: [a] -> [a] -> Bool
cmp l1 l2 = if (size l1) < (size l2) then True else False

inso :: [a] -> [[a]] -> [[a]]
inso a [] = [a]
inso a (h:t) = if (cmp a h) then (a:h:t) else (h:(inso a t))

ord :: [[a]] -> [[a]]
ord [] = []
ord (h:t) = inso h o
    where o = ord t

main :: IO ()
main = do
    print (ord [[1,2], [1, 2, 3], [1,2,3,4],[1], [1,2,5,6,1]])