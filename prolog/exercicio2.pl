retangulo(p(X1,Y1), p(X2,Y2)) :- 
    X1 < X2, Y1 < Y2.
quadrado(retangulo(p(X1,Y1), p(X2,Y2))) :-
    X2 - X1 == Y2 - Y1.
