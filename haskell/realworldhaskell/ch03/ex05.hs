-- Write a function that determines whether its input list is a palindrome.
ehPalindromo :: [a] -> [Char]
ehPalindromo l = comparaLista l li
    where li = inverte l

inverte :: [a] -> [a]
inverte [h] = [h]
inverte (h:t) = inverte t ++ [h]

comparaLista :: [a] -> [a] -> Bool 
comparaLista (a:b) (c:d) = if a == c then comparaLista b d else False

main :: IO ()
main = do
    print (ehPalindromo [1, 2, 3])
    print (ehPalindromo [1, 2, 3, 3, 2, 1])