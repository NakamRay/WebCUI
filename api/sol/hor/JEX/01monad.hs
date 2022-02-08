{-# LANGUAGE QuasiQuotes #-}

-- #1 Monad
module Ex where
import TH
import SOL

sigm = [signature|
 return : a -> T(a)
 bind : T(a),(a -> T(b)) -> T(b)
 |]

monad = [rule|
 (unitL)  return(X) >>= y.K[y]      => K[X] 
 (unitR)  N >>= y.return(y)         => N 
 (assoc)  (N >>= x.K[x]) >>= y.L[y] => N >>= x.(K[x] >>= y.L[y])
 |] 
