{-# LANGUAGE QuasiQuotes #-}

-- Hasegwa's "a yet simpler" linear lambda-calculus
module Ex where
import TH
import SOL

sigLL = [signature| 
  bang : a -> Bang(a)
  app : Arr(a,b),a -> b
  lam : (a -> b) -> Arr(a,b)
  let : Bang(a),(a -> b) -> b
 |]

lamHas = [rule|
 (beta-o) lam(x.M[x])@N       => M[N] 
 (eta-o)  lam(x.M@x)          => M    
 (eta!)   let(M, x.L@bang(x))  => L@M 
 (beta!)  let(bang(M), x.N[x]) => N[M]
 (eta'!)  let(M, x.C[bang(x)])  => C[M]  
 |]
