{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigtylmd = [signature|
 app : (Arr(a,b),a) -> b
 lam : (a -> b) -> Arr(a,b)
 |]

tylmd = [rule| 
 (1)  lam(x.M[x])@N => M[N]
 (2)  lam(x.(L@x)) => L
 |]
