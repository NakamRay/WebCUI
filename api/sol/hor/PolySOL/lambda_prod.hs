{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL


siglamprod = [signature| 
 app : (Arr(a,b),a) -> b
 lam : (a -> b) -> Arr(a,b)
 pia : Prod(a,b) -> a
 pib : Prod(a,b) -> b
 pair : (a,b) -> Prod(a,b)
 |]
lamprod = [rule| 
 (1)  lam(x.M[x])@N => M[N]
 (2)  lam(x.(L@x)) => L
 (3)  pia(pair(M1,N1)) => M1
 (4)  pib(pair(M1,N1)) => N1
 (5)  pair(pia(M2),pib(M2)) => M2
 |]