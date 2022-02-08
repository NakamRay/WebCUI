{-# LANGUAGE QuasiQuotes #-}

module Ex where
import TH
import SOL

sigML = [signature| 
 app : Arr(a,b),a -> b      ;   let    : T(a),(a -> T(b)) -> T(b)
 lam : (a -> b) -> Arr(a,b) ;   return : a -> T(a)                |]

lamML = [rule| 
 (beta) lam(x.M[x]) @ N  => M[N]
 (eta)  lam(x.M@x)       => M
 (beta-let) let(return(M),x.N[x]) => N[M]
 (eta-let)  let(M,x.return(x)) => M
 (assoc)    let(let(L,x.M[x]),y.N[y]) => let(L,x.let(M[x],y.N[y]))
 |]
