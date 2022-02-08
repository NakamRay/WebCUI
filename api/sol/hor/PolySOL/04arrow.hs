{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigarrow = [signature| 
 arrow:(t,t)->t
 lessthan:(t,t)->c
 and:(c,c)->c
 |]

arrow = [rule| 
 (1)  lessthan(arrow(X,Y),arrow(V,W)) => and(lessthan(V,X),lessthan(Y,W))
 |]
