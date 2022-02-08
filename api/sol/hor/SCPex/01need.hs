{-# LANGUAGE QuasiQuotes #-}

-- #1 Call-by-need lambda caluclus
module Ex where
import TH
import SOL

sigNeed = [signature| 
 app : Arr(a,b),a -> b
 lam : (a -> b) -> Arr(a,b)
 let : a,(a -> b) -> b                        |]

need = [rule|
 (rG)    let(M, x.N)                => N
 (rI)    lam(x.M[x]) @ N            => let(N,x.M[x])
 (rV-v)  let(V, x.C[x])             => C[V]
 (rC-v)  let(V, x.M[x])@N           => let(V, x.M[x]@N)
 (rA)    let(let(L,x.M[x]), y.N[y]) => let(L,x.let(M[x],y.N[y])) 
 |]
