{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigNeed = [signature| 
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 let : a,(a -> b) -> b                        |]

need = [rule|
 (_G)    let(M, x.N)                => N
 (_I)    lam(x.M[x]) @ N            => let(N,x.M[x])
 (_V-v)  let(V, x.C[x])             => C[V]
 (_C-v)  let(V, x.M[x])@N           => let(V, x.M[x]@N)
 (_A)    let(let(L,x.M[x]), y.N[y]) => let(L,x.let(M[x],y.N[y])) 
 |]
