{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

-- #1 Monad
module Ex where
import Types
import TH
import Com
import SOL

sigGl = [signature|
  unit : Unit
  pair : a1,a2 -> Pair(a1,a2)
  inj1  : a1 -> Sum(a1,a2)    
  inj2  : a2 -> Sum(a1,a2)    
  thunk : c -> U(c)
  return : a -> Arr(a,a)
  lam : (a -> c) -> Arr(a,b)
  cpair : c1,c2 -> CPair(c1,c2)
  get : (Nat -> Arr(Nat,Nat)) -> Arr(Nat,Nat)
  put : Nat,Arr(Nat,Nat) -> Arr(Nat,Nat)
  sub : (Nat -> a), Nat -> a
 |]

gstate = [rule| 
 (lu)   get(v.put(v,X))      => X
 (ll)   get(w.get(v.X[v,w])) => get(v.X[v,v])
 (uu)   put(V,put(W,X))      => put(W,X)
 (ul)   put(V,get(w.X[w]))   => put(V,sub(w.X[w],V))
 (sub1) sub(x.return(x),K)   => return(K)
 (sub2) sub(x.M,K)           => M  
 (sub3) sub(x.get(v.M[v,x]),K) => get(v.sub(x.M[v,x],K))
 (sub4) sub(x.put(V,M[x]),K)   => put(V,sub(x.M[x],K))
 |]
