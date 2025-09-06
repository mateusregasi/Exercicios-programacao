-- Write a function that computes the number of elements in a list. To test it, ensure that it gives the same answers as the standard length function.
lengthl :: [a] -> Int
lengthl [_] = 1
lengthl (h:t) = 1 + lengthl(t)

main :: IO ()
main = do
    print (lengthl [1,2,3,4])