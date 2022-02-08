sig_MAM = [signature|
  unit : Unit
  pair : a1,a2 -> Pair(a1,a2)
  inj1  : a1 -> Sum(a1,a2)    
  inj2  : a2 -> Sum(a1,a2)    
  thunk : c -> U(c)
  return : a -> Arr(a,a)
  lam : (a -> c) -> Arr(a,b)
  cpair : c1,c2 -> CPair(c1,c2)
  caseP : Pair(a1,a2),(a1,a2 -> c) -> c
  case  : Sum(a1,a2),(a1 -> c),(a2 -> c) -> c
  bang  : U(c) -> c
  let : Arr(a,a),(a -> c) -> c
  app : Arr(a,c),a -> c
  prj1 : CPair(c1,c2) -> c1
  prj2 : CPair(c1,c2) -> c2
 |]


mam = [rule| 
  (beta) lam(x.M[x])@V => M[V]
  (u)    bang(thunk(M)) => M
  (and)  prj1(cpair(M1,M2)) => M1
  (prod) prj2(cpair(M1,M2)) => M2
  (sum1) case(inj1(V),x.F[x],y.G[y]) => F[V]
  (sum2) case(inj2(V),x.F[x],y.G[y]) => G[V] 
  (f)    let(return(V),x.M[x]) => M[V]
|]
