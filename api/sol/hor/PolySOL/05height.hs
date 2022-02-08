{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigheight = [signature| 
 nil : f
 cons : (t,f) -> f
 max : (N,N) -> N
 heightt : t -> N
 heightf : f -> N
 leaf : t
 node : f -> t
 z : N
 s : N -> N
 |]

height = [rule| 
 (1)  heightf(nil) => z
 (2)  heightf(cons(T,F)) => max(heightt(T),heightf(F))
 (3)  heightt(leaf) => z
 (4)  heightt(node(F)) => s(heightf(F))
 |]