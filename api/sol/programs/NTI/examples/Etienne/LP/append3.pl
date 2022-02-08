append([],Ys,Ys).
append([X|Xs],Ys,[X|Zs]) :- append(Xs,Ys,Zs).

% The modes append3(i,i,o,o) and append3(i,o,o,i) terminate,
% hence every less general mode also terminates.
% The following mode does not terminate.
%query: append3(i,o,i,o).
% Hence every more general mode also does not terminate.
append3(Xs,Ys,Zs,Ts) :- append(Xs,Ys,Us), append(Us,Zs,Ts).
