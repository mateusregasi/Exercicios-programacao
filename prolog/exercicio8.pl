maximo(X,[A|B]) :-
    B = [],
	X = A, !.
maximo(X, [A|B]) :-
    maximo(R,B),
    ((A >= R,M = A);
    (R > A,M = R)),
    X = M.

% maximo(X,[3,2,1,7,4]).
