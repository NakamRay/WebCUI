{-# LANGUAGE QuasiQuotes #-}

-- Moggi's computational lambda calculus
module Ex where
import TH
import Com
import SOL

siglamC = [signature| 
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 let : a,(a -> b) -> b                        |]

lamC = [rule|
 (beta-v)    lam(x.M[x]) @ V  => M[V] 
 (eta-v)     lam(x.V @ x)     => V    
 (beta-let-v) let(V, x.M[x])  => M[V] 
 (eta-let)   let(M, x.x)      => M    
 (assoc)     let(let(L,x.M[x]), y.N[y]) =>let(L,x.let(M[x],y.N[y])) 
 (let1-p)    P @ M            => let(P,x.x@M)
 (let2-v)    V @ P            => let(P,y.V@y) |]
