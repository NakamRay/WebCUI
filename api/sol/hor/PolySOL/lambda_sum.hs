{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


sigsum = [signature|
 app : (Arr(a,b),a) -> b
 lam : (a -> b) -> Arr(a,b)
 case : (S(a,b),(a -> c),(b -> c)) -> c
 inl : a -> S(a,b)
 inr : b -> S(a,b)
 |]

lmdsum = [rule| 
 (1)  lam(x.M[x])@N => M[N]
 (2)  lam(x.(L@x)) => L
 (3)  case(inl(X),x.F[x],y.G[y]) => F[X]
 (4)  case(inr(Y),x.F[x],y.G[y]) => G[Y]
 |]
