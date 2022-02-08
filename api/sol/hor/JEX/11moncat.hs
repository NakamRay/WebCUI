{-# LANGUAGE QuasiQuotes #-}

-- #11 Coherence of Monoidal Categories
module Ex where
import TH
import SOL

sigmcat = [signature| 
 times : C,C -> C
 i     : C
 |]

mcat = [rule| 
 (rho) A * i() => A
 (lmd) i() * A => A
 (alpha) (A * B) * C => A * (B * C)
 |]
