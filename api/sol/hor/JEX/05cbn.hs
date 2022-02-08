{-# LANGUAGE QuasiQuotes #-}

-- #5 Remark. The untyped lambda calculus
module Ex where
import TH
import SOL

sigcbn = [signature|
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 |]

cbn = [rule| 
 (beta) lam(x.M[x]) @ N  => M[N]
 (eta)  lam(x.M@x)       => M
 |]
