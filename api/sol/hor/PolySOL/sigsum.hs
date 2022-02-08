{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

-- Computation rules for sum with eta
-- van de Pol, PhD thesis 1996

module Ex where
import TH
import SOL

sigsum = [signature| 
  case : Sum(a,b),(a -> c),(b -> c) -> c
  inl : a -> Sum(a,b)
  inr : b -> Sum(a,b)
 |]

sumtype = [rule| 
 (rho1)   case(inl(X),x.F[x],y.G[y]) => F[X]
 (rho2)   case(inr(Y),x.F[x],y.G[y]) => G[Y]
 (sumEta) case(Z,x.H[inl(x)],y.H[inr(y)]) => H[Z]
 |]