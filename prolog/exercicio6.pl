concatena(L1,L2,L3) :-
    L1 = [],
    L2 = [],
    L3 = [], !.
concatena(L1, [A|B], L3) :-
    L1 = [],
    concatena(L1,B,R),
    L3 = [A|R].
concatena([A|B],L2,L3) :-
    concatena(B,L2,R),
    L3 = [A|R].
    


% concatena([1,2],[3,4],L).
% concatena([1,2],L,[1,2,3,4]).
% concatena(L,[3,4],[1,2,3,4]).
