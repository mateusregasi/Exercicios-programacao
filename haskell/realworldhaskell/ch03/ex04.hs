-- Turn a list into a palindrome, i.e. it should read the same both backwards and forwards. For example, given the list [1,2,3], your function should return [1,2,3,3,2,1]
palindromo :: [Int] -> [Int]
palindromo l = l ++ reverso l

reverso :: [a] -> [a]
reverso [h] = [h]
reverso (h:t) = reverso (t) ++ [h]

main :: IO ()
main = do
    print (palindromo [1, 2, 3]) 