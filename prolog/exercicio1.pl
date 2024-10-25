arco(a,b,3).
arco(a,d,5).
arco(a,c,4).
arco(b,d,2).
arco(c,d,4).
arco(d,e,2).
arco(c,f,5).
arco(e,f,2).

custo(U,V,L) :- 
    arco(U,V,L).
custo(U,V,L) :-
    arco(U,W,L1),
    arco(W,V,L2),
    L is L1 + L2.
