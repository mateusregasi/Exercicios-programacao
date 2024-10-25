membro(X, [A|B]) :-
    X = A.
membro(X, [_|B]) :-
    membro(X, B).


% membro(b,[a,b,c])
% membro(X,[a,b,c])
% findall(X, membro(X,[a,b,c]),L)
