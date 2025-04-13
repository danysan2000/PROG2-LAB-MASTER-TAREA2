-- ejemplo factorial por deepseek HASKELL
--
--
--
--
-- Definición de la función factorial
factorial :: Integer -> Integer
factorial 0 = 1  -- Caso base
factorial n = n * factorial (n - 1)  -- Caso recursivo

-- Función principal (para ejecutar)
main :: IO ()
main = do
    putStrLn "¡Calculadora de factorial en Haskell!"
    putStr "Ingresa un número: "
    num <- readLn  -- Lee un número desde la terminal
    putStrLn ("El factorial de " ++ show num ++ " es: " ++ show (factorial num))


