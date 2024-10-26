comprimento(X,L) :-
    L = [],
    X = 0.
comprimento(X,[_|B]) :-
    comprimento(R,B),
    X is 1 + R.

% comprimento(X,[a,b,c,d])
