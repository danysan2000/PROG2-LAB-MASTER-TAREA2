{-
 (): ArbBin
prof :: Integer integer -> integer
prof 0 = 0
prof izq,root,der  = 1 + max(prof(izq), prof(der))
-}

-- Definición del árbol binario:
data Arbol a = Nulo               -- Árbol vacío ()
             | Nodo a (Arbol a) (Arbol a)  -- Nodo con valor y subárboles izq/der
             deriving Show

-- Función hojas:
hojas :: Arbol a -> [a]
hojas Nulo = []                     -- Caso base: árbol vacío
hojas (Nodo a Nulo Nulo) = [a]      -- Caso hoja: ((), a, ())
hojas (Nodo a izq der) = hojas izq ++ hojas der  -- Caso recursivo


ejemplo :: Arbol Int
ejemplo = Nodo 2 (Nodo 1 Nulo Nulo) (Nodo 3 Nulo Nulo)


-- Para probar en GHCi:
main :: IO ()
main = do
  print (hojas ejemplo)  -- Debe imprimir [1, 3]
