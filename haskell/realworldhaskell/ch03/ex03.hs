-- Write a function that computes the mean of a list, i.e. the sum of all elements in the list divided by its length. (You may need to use the fromIntegral function to convert the length of the list from an integer into a floating point number.)
media :: [Int] -> Float
mediaaux :: Int -> Float -> [Int] -> Float

media [] = 0
media (h:t) = mediaaux 1 (fromIntegral h) t

mediaaux n m (h:[]) = ((nc * m + hc) / (nc + 1))
    where nc = (fromIntegral n)
          hc = (fromIntegral h)
mediaaux n m (h:t) = mediaaux (n+1) ((nc * m + hc) / (nc + 1)) t
    where nc = (fromIntegral n)
          hc = (fromIntegral h)

-- Fiz uma média menos eficiente mais para treinar essa recursão maluca usando
-- m = (n1*m1 + n2*m2) / (n1 + n2) onde n2 = 1  => m = (n1*m1 + m2) / (n1 + 1)

main :: IO ()
main = do
    print (media [1,2,3,4,5])