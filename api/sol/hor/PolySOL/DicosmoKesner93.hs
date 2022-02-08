{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


sigdi = [signature| 
 app : (Arr(a,b),a) -> b
 lam : (a -> b) -> Arr(a,b)
 case : (S(a,b),(a -> C),(b -> C)) -> C
 inl : a -> S(a,b)
 inr : b -> S(a,b)
 pia : P(a,b) -> a
 pib : P(a,b) -> b
 pair : (a,b) -> P(a,b)
 |]

di = [rule| 
 (1)  lam(x.M[x])@N => M[N]
 (2)  lam(x.(L@x)) => L
 (3)  pia(pair(M1,N1)) => M1
 (4)  pib(pair(M1,N1)) => N1
 (5)  pair(pia(M2),pib(M2)) => M2
 (6)  case(inl(X),x.F[x],y.G[y]) => F[X]
 (7)  case(inr(Y),x.F[x],y.G[y]) => G[Y]
 |]