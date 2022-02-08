{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

-- simplified lambda ML*, [Sabry-Wadler Fig.4]

module Ex where
import TH
import SOL


sigMLstar = [signature| 
  app : Arr(a,b),a -> b
  lam : (a -> b) -> Arr(a,b)
  let : T(a),(a -> T(b)) -> T(b)
  return : a -> T(a)
 |]

lamMLstar0 = [rule| 
 (beta-v) lam(x.M[x]) @ V  => M[V]
 (eta-v)  lam(x.V@x)       => V
 (beta-let-v) let(return(V),x.N[x]) => N[V]
 (eta-let)  let(M,x.return(x)) => M
 (assoc)    let(let(L,x.M[x]),y.N[y]) => let(L,x.let(M[x],y.N[y]))
 |]
