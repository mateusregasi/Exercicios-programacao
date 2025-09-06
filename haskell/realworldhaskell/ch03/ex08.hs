-- Using the binary tree type that we defined earlier in this chapter, write a function that will determine the height of the tree. The height is the largest number of hops from the root to an Empty. For example, the tree Empty has height zero; Node "x" Empty Empty has height one; Node "x" Empty (Node "y" Empty Empty) has height two; and so on.

data Arv = Arv Int Arv Arv
            |    Folha deriving (Show) 

arv = (Arv 1 (Arv 2 (Arv 3 Folha Folha) (Arv 4 Folha Folha)) (Arv 2 Folha Folha))

parv :: Arv -> IO ()
parv (Arv a e d) = putStr (pa (Arv a e d) 0)
    where
        pa Folha i = pfo i
        pa (Arv a e d) i = (pa e (i+1)) ++ (pno a i) ++ (pa d (i+1))
        pno n i = (p i) ++ (show n) ++ "\n"
        pfo i = (p i) ++ "Folha\n"
        p :: Int -> [Char]
        p 0 = "" 
        p i = "    " ++ p (i-1)

peso :: Arv -> Int
peso Folha = 0
peso (Arv _ e d) = max (peso e) (peso d) + 1

main :: IO ()
main = do
    parv arv
    putStrLn ("Peso: " ++ show (peso arv))