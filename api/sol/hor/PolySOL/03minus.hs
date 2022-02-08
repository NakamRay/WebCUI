{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


sigminus = [signature|
  z : N
  s : N -> N
  minus : (N,N) -> N |]

rminus = [rule|
 (1)  minus(z(),X) => z()
 (2)  minus(X,z()) => X
 (3)  minus(s(X),s(Y)) => minus(X,Y)
 (4)  minus(X,X) => z()
 |]
