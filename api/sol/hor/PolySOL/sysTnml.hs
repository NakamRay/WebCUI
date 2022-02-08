sigSysT = [signature| 
 app: Arr(a,b),a -> b;  lam: (a -> b) -> Arr(a,b) 
 zero: N;          s  : N -> N;           rec: N, a, (N,a -> a) -> a  |]

sysT = [rule| 
 (beta) lam(x.M[x])@N       => M[N]
 (eta)  lam(x.M @ x)   => M    
 (rec1) rec(zero(), S, n.x.T[n,x]) => S
 (rec2) rec(s(X), S, n.x.T[n,x]) => T[X,rec(X,S,n.x.T[n,x])] |]
