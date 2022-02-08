{-# LANGUAGE QuasiQuotes #-}

-- Skew monoidal category
module Ex where
import TH
import Com
import SOL

sigskew = [signature| 
 times : Hom(a,c),Hom(b,d) -> Hom(Pr(a,b),Pr(c,d))
 app   : Hom(b,c),Hom(a,b) -> Hom(a,c)
 id    : Hom(a,a)
 lmd   : Hom(Pr(I,a),a)
 rho   : Hom(a,Pr(a,I))
 alpha : Hom(Pr(Pr(a,b),c),Pr(a,Pr(b,c)))
 |]

skew = [rule| 
 (idL)     id() @ F                => F 
 (idR)     F  @ id()               => F
 ;
 (ox-id)   id() * id() => id()
 (ox-comp) (H * K) @ (F * G)       => (H @ F) * (K @ G)
 ;
 (alpha-nat)  alpha() @ ((F * G) * H) => (F * (G * H)) @ alpha()
 (lmd-nat)    lmd() @ (id() * F)      => F @ lmd()
 (rho-nat)    (F * id()) @ rho()      => rho() @ F
 (alpha-nat)  alpha() @ ((F * G) * H) => (F * (G * H)) @ alpha()
 ;
 (a)  lmd() @ rho()    => id()
 (b)   (id() * lmd()) @ (alpha() @ (rho() * id())) => id()
 (b') ((id() * lmd()) @ alpha()) @ (rho() * id())  => id()
 (c)  lmd() @  alpha() => lmd() * id() 
 (d)  alpha() @ rho()  => id() * rho()
 (e)   (id() * alpha()) @ (alpha() @ (alpha() * id())) => alpha() @ alpha()
 (e') ((id() * alpha()) @ alpha()) @ (alpha() * id())  => alpha() @ alpha()
 |]
