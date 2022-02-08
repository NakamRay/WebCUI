{-# LANGUAGE QuasiQuotes #-}

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

lamMLstar = [rule| 
 (beta_v)  lam(x.M[x])@y => M[y]
 (beta_b)  lam(x.M[x])@lam(w.K[w]) => M[lam(w.K[w])]
 (eta_v)  lam(x.(y@x)) => y
 (eta_b)  lam(x.(lam(w.K[w])@x)) => lam(w.K[w])
 (beta-let_v)  let(return(y),x.N[x]) => N[y]
 (beta-let_b)  let(return(lam(w.K[w])),x.N[x]) => N[lam(w.K[w])]
 (eta-let)  let(M,x.return(x)) => M
 (assoc)  let(let(L,x.M[x]),y.N[y]) => let(L,x.let(M[x],y.N[y]))
 |]
