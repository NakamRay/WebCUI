module F where

{-# RULES
"f/0" forall x. f x = 0
"f/1" forall x. f x = 1
  #-}

e = f 99

{-# NOINLINE f #-}
f :: Integer -> Integer
f x = undefined
