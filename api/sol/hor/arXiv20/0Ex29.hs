sigrec = [signature|
  zero : Nat ; succ : Nat -> Nat ; rec : Nat,a,(Nat,a -> a) -> a  
 |]

recursor = [rule|
 (recZ) rec(zero, U,x.y.V[x,y])   => U
 (recS) rec(succ(X),U,x.y.V[x,y]) => V[X,rec(X,U,x.y.V[x,y])] 
 |]
