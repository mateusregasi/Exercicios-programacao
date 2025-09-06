-- 7) Define a function that joins a list of lists together using a separator value.
-- intersperse :: a -> [[a]] -> [a]
-- The separator should appear between elements of the list, but should not follow the last element. Your function should behave as follows.
-- ghci> intersperse ',' []
-- ""
-- ghci> intersperse ',' ["foo"]
-- "foo"
-- ghci> intersperse ',' ["foo","bar","baz","quux"]
-- "foo,bar,baz,quux"

intersperse :: a -> [[a]] -> [a]
intersperse sep [h] = h
intersperse sep (h:t) = (h ++ [sep] ++ (intersperse sep t))

main :: IO ()
main = do
    print (intersperse ',' ["foo","bar","baz","quux"])