{- https://wiki.haskell.org/GHC/Using_rules -}
module P where

{-# RULES
"project/project" forall x . project (project x) = project x
"project/foo" forall x . project (foo x) = projectFoo x
"project/projectFoo" forall x . project (projectFoo x) =
                     projectFoo x
 #-}

f = project . project . foo

project :: Integer -> Integer
project = id

foo :: a -> a
foo = id

projectFoo :: Integer -> Integer
projectFoo = project . foo

main = print "foo.hs"
