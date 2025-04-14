-- ejemplo 2 fibonaci
--
-- Genera una lista infinita de Fibonacci y toma los primeros 'n' elementos
fibonacci :: Int -> [Integer]
fibonacci n = take n fibList
  where
    fibList = 0 : 1 : zipWith (+) fibList (tail fibList)

main :: IO ()
main = do
    putStrLn "Serie de Fibonacci"
    putStr "¿Cuántos términos quieres? "
    n <- readLn
    print (fibonacci n)

