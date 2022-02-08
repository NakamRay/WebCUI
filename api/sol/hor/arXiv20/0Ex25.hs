siglam = [signature|
  lam : (L(a) -> L(b)) -> L(Arr(a,b))
  app : L(Arr(a,b)),L(a) -> L(b)
 |]

lam = [rule| 
 (beta) lam(x.M[x]) @ N  => M[N]
 |]
