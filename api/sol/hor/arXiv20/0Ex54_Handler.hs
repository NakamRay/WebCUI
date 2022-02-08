sig_Handle = [signature|
  unit : Unit
  pair : a1,a2 -> Pair(a1,a2)
  inj1  : a1 -> Sum(a1,a2)    
  inj2  : a2 -> Sum(a1,a2)    
  thunk : c -> U(c)
  return : a -> Arr(a,a)
  lam : (a -> c) -> Arr(a,b)
  caseP : Pair(a1,a2),(a1,a2 -> c) -> c
  case  : Sum(a1,a2),(a1 -> c),(a2 -> c) -> c
  bang  : U(c) -> c
  let : Arr(a,a),(a -> c) -> c
  app : Arr(a,c),a -> c
  prj1 : CPair(c1,c2) -> c1
  prj2 : CPair(c1,c2) -> c2
  handler : (a -> Arr(a,a)),(Arr(a,Arr(a,a)) -> Arr(a,a)),(a,Arr(a,a) -> Arr(a,a)), Arr(a,a) -> Arr(a,a)
  tm : Arr(a,a)
  runState : Arr(a,a) -> Arr(a,a)
  get : (Nat -> Arr(Nat,Nat)) -> Arr(Nat,Nat)
  put : Nat,Arr(Nat,Nat) -> Arr(Nat,Nat)
  sub : (Nat -> a), Nat -> a
 |]

hand = [rule| 
 (h_r) handler(y.RET[y], k.GET[k], p.k.PUT[p,k], return(X))     => RET[X]
 (h_g) handler(y.RET[y], k.GET[k], p.k.PUT[p,k], get(x.M[x]))   => GET[  lam(x.handler(y.RET[y],k.GET[k],p.k.PUT[p,k],M[x]))]
 (h_p) handler(y.RET[y], k.GET[k], p.k.PUT[p,k], put(P,M)) => PUT[P,handler(y.RET[y],k.GET[k],p.k.PUT[p,k],M)]
 (run) runState(T) => handler(y.lam(z.y), k.lam(n.(k@n)@n), p.k.lam(n.k@p), T)
 |]
