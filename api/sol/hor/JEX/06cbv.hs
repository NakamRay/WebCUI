{-# LANGUAGE QuasiQuotes #-}

-- #6 The call-by-value lambda calculus
module Ex where
import TH
import SOL

siglam = [signature|
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 y : a
 |]

cbv = [rule| 
(beta-v_v)   lam(x.M[x])@y           => M[y]
(beta-v_b)   lam(x.M[x])@lam(w.K[w]) => M[lam(w.K[w])]
(eta-v_v)    lam(x.y@x)              => y
(eta-v_b)    lam(x.lam(w.K[w])@x)    => lam(w.K[w])
 |]
