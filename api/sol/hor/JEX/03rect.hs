{-# LANGUAGE QuasiQuotes #-}

-- #3 Rectanglar band, Sam Staton, LICS'13  (5)
module Ex where
import TH
import Com
import SOL

sigrect = [signature| 
 qu : a,a -> a 
 |]

rect = [rule|
 (idem-Q) X ? X => X 
 (dup-Q)  (U ? V) ? (X ? Y) => U ? Y 
 (ex1)    V ? (X ? Y) => V ? Y  
 (ex2)    (U ? V) ? Y => U ? Y  
 |]
