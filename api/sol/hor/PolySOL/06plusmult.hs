{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


sigplusmult = [signature|
 z : N
 s : N -> N
 plus : (N,N) -> N
 mult : (N,N) -> N
 |]

plusmult = [rule| 
 (1)  z() + Y => Y
 (2)  s(X) + Y => X + s(Y)
 (3)  (X + Y) + Z => X + (Y + Z)
 (4)  mult(z(),Y) => z()
 (5)  mult(s(X),Y) => mult(X,Y) + Y
 (6)  mult(X + Y,Z) => mult(X,Z) + mult(Y,Z)
 |]