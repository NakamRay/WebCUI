{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigord = [signature| 
 plus : (O,O) -> O
 lim : (N -> O) -> O
 z : O
 s : O -> O
 |]

ord = [rule| 
 (1)  z + Y => Y
 (2)  s(X) + Y => s(X + Y)
 (3)  lim(x.Z[x]) + Y => lim(m.(Z[m] + Y))
 |]