{-# LANGUAGE QuasiQuotes #-}

-- #4 Writing a bit, Sam Staton, LICS'13
module Ex where
import TH
import SOL

sigw = [signature|
 w0 : a -> a
 w1 : a -> a
 qu  : a,a -> a
 |]

wbit = [axiom|
 (w0w0)  w0(w0(X)) = w0(X)  ;  (w1w0)  w1(w0(X)) = w0(X)
 (w0w1)  w0(w1(X)) = w1(X)  ;  (w1w1)  w1(w1(X)) = w1(X)
 (w0Q)   w0(X ? Y) = w0(X)  ;  (w1Q)   w1(X ? Y) = w1(Y) 
 (_Qw)   w0(Z) ? w1(Z) = Z                              
 ;
 (idem-Q) X ? X       => X 
 (ex1)    V ? (X ? Y) => V ? Y  
 (ex2)    (U ? V) ? Y => U ? Y  
 (e0)     w0(Z) ? Y   => Z ? Y 
 (e1)     w1(Z) ? Z   => w1(Z)  
 (e2)     Z ? w0(Z)   => w0(Z)  
 (e3)     Y ? w1(Z)   => Y ? Z                            |]
