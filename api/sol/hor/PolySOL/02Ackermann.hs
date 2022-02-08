{-# OPTIONS_GHC -fno-warn-overlapping-patterns -fno-warn-missing-methods #-}
{-# LANGUAGE TemplateHaskell, QuasiQuotes, FlexibleInstances, BangPatterns, MultiParamTypeClasses #-}

module Ex where
import TH
import SOL

sigack = [signature| 
  z : N
  s : N -> N
  ack : N,N -> N
  |]

ack = [rule| 
  ack(z(), N) => s(N)
  ack(s(M), z()) => ack(M, s(z()))
  ack(s(M), s(N)) => ack(M, (ack(s(M), N)))
  |]
