{- https://wiki.haskell.org/GHC/Using_rules -}
module P where

{-# RULES
"project/project" forall x . project (project x) = project x
"project/foo" forall x . project (foo x) = projectFoo x
 #-}

f = project . project . foo

{-# NOINLINE project #-}
project :: Integer -> Integer
project x = x + 1

{-# NOINLINE foo #-}
foo :: Integer -> Integer
foo x = x - 1

{-# NOINLINE projectFoo #-}
projectFoo :: Integer -> Integer
projectFoo = project . foo

main = print "foo.hs"
