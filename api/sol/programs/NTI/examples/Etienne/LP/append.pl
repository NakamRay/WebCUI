% The modes append(i,o,o) and append(o,o,i) terminate,
% hence every less general mode also terminates.
% The following mode does not terminate.
%query: append(o,i,o).
% Hence every more general mode also does not terminate.
append([],Ys,Ys).
append([X|Xs],Ys,[X|Zs]) :- append(Xs,Ys,Zs).
