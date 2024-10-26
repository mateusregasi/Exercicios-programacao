soma(X, [A|B]) :-
    B = [],
    X = A, !.
soma(X, [A|B]) :-
    soma(R, B),
    X is R + A.
conta(X, [_|B]) :-
    B = [],
    X = 1, !.
conta(X,[_|B]) :-
    conta(R,B),
    X is R+1.
media(X,L) :-
    soma(R1, L),
    conta(R2,L),
    X is R1 / R2.


% media(X,[1,2,3,4,5]).
