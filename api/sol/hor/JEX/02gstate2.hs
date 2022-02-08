{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigstL = [signature| 
  lk-n : (Val -> E) -> E 
  lk-n+1 : (Val -> E) -> E 
  ud-n : Val,E -> E 
  ud-n+1 : Val,E -> E       |]

gstateL = [rule| 
 (lu-n)   lk-n(v.ud-n(v,X))        => X
 (ll-n)   lk-n+1(w.lk-n(v.X[v,w])) => lk-n(v.X[v,v])
 (uu-n)   ud-n(V,ud-n(W,X))        => ud-n(W,X)
 (uu-n)   ud-n+1(V,lk-n(w.X[w]))   => ud-n(V,X[V]) |]
