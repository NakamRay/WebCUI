{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


siggstate = [signature| 
 lk : (W -> E) -> E
 ud : (W,E) -> E
 |]

gstate = [rule| 
 (1)  lk(v.ud(v,P)) => P
 (2)  ud(V,ud(Q,S)) => ud(Q,S)
 (3)  ud(V,lk(w.Y[w])) => ud(V,Y[V])
 (4)  lk(w.lk(v.X[v,w])) => lk(v.X[v,v])
 |]