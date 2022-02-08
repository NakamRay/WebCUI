{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


sigkripke = [signature| 
 app : (Arr(a,b),a) -> b
 abs : (a -> b) -> Arr(a,b)
 box : a -> Box(a)
 unbox : Box(a) -> a
 |]
kripke = [rule| 
 (1)  abs(x.M[x])@N => M[N]
 (2)  abs(x.(P@x)) => P
 (3)  unbox(box(K)) => K
 (4)  box(unbox(L)) => L
 |]
