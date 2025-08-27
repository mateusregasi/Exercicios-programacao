
data Talvez tipo = Talvez tipo | Nada deriving (Show)
data Arv tipo = Arv (Talvez tipo) (Talvez (Arv tipo)) (Talvez (Arv tipo)) deriving (Show)
a :: Arv Int
a = Arv (Talvez 1) Nada Nada

main :: IO ()
main = do
    print (a)