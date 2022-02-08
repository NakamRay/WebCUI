{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns #-}

module Ex where
import Types
import TH
import SOL

sigSysT = [signature| 
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 var : V(a) -> a
 zero : N 
 s : N -> N 
 rec : N, a, (N,a -> a) -> a
 |]

sysT = [rule|
 (beta) lam(x.M[var(x)]) @ N  => M[N]
 (eta)  lam(x.M@var(x))       => M 
 (rec1) rec(zero, S, n.x.T[n,x]) => S
 (rec2) rec(s(X), S, n.x.T[n,x]) => T[X,rec(X,S,n.x.T[n,x])]
 |]
