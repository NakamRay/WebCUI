{-# LANGUAGE QuasiQuotes #-}

-- #10 A theory of Pi-calculus   Ian Stark, TCS 2008   (11)
module Ex where
import TH
import SOL

pisig = [signature| 
  sum : A,A -> A
  out : N,N,A -> A       
  in  : N,(N -> A) -> A
  nil : A
  tau : A -> A
  new : (N -> A) -> A
 |]

pical = [rule| 
 (sum-uniL)  sum(nil(),X)         => X
 (new-uni)  new(a.X)              => X
 ;
 (new-sum)  new(a.sum(X[a],Y[a])) => sum(new(a.X[a]),new(a.Y[a]))
 (new-out0) new(a.out(a,B[a],X[a]))  => nil()
 (new-out)  new(a.out(B,C,X[a]))  => out(B,C,new(a.X[a])) 
 (new-in)   new(a.in(B,c.X[a,c])) => in(B,c.new(a.X[a,c]))
 (new-tau)  new(a.tau(X[a]))      => tau(new(a.X[a]))
 ;
 (new-in0)  new(a.in(a,b.X[a,b])) => nil()                 
 |]

pieq = [axiom| 
 (sum-idem) sum(X,X)              = X
 (sum-asc)  sum(sum(X,Y),Z)       = sum(X,sum(Y,Z))
 (sum-com)  sum(X,Y)              = sum(Y,X)
 (new-com)  new(a.new(b.X[a,b]))  = new(b.new(a.X[a,b])) 
 |]
