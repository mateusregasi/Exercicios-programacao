apaga(X, [A|B],L2) :-
    A \= X,
    B = [],
    L2 = A, !.
apaga(X, [X|B],L2) :-
    B = [], !.
apaga(X,[X|B],L2) :-
    apaga(X,B,R),
    L2 = R.
apaga(X,[A|B],L2) :-
    A \= X,
    apaga(X,B,R),
    L2 = [A|R].

% apaga(a,[a,b,a,c],L).
% apaga(a,L,[b,c]).

% apaga(_,[],[]).
% apaga(X,[X|F1],F2) :- 
%     apaga(X,F1,F2),!.
% apaga(X,[C|F1],[C|F2]) :- 
%     apaga(X,F1,F2).
