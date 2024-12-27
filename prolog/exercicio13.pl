% Problema dos jarros:
% Dado jarros de volume R1 e R2, queremos saber qual sequência
% de movimentos (enchar R1, encher R2, jogar de R1 para R2, jogar de R2 para R1)
% serão necessários para deixar o R2 com volume 2

% Capacidade dos jarros
capacidade(r1, 5).
capacidade(r2, 3).

% Algoritmo de busca
buscaR(A) :-
    busca([0], [0], A).

% Verificar loop
verLoop([A|_], [C|_], A, C) :- !.
verLoop([_|B], [_|D], E, F) :- verLoop(B, D, E, F).

% Condição inicial
busca([2|_], _, []) :- !.

% Encher R1 (a)
busca([A|B], [C|D], [a|E]) :-
    capacidade(r1, X),
    A < X,
    \+ verLoop([A|B], [C|D], X, C),
    busca([X|[A|B]], [C|[C|D]], E),!.
  
% Encher R2 (b)
busca([A|B], [C|D], [b|E]) :-
    capacidade(r2, X),
    C < X,
    \+ verLoop([A|B], [C|D], A, X),
    busca([A|[A|B]], [X|[C|D]], E),!.

% Jogar R1 em R2
busca([A|B], [C|D], [c|E]) :-
    capacidade(r2, X),
 	C < X,
	R is A + C,
    ((   
    	R > X, 
    	I is R - X, 
    	J = X
    );(   
    	I = 0, 
    	J = R
    )),
    \+ verLoop([A|B], [C|D], I, J),
    busca([I|[A|B]], [J|[C|D]], E),!.

% Jogar R2 em R1
busca([A|B], [C|D], [d|E]) :-
    capacidade(r1, X),
 	A < X,
	R is A + C,
    ((   
    	R > X, 
    	I = X, 
    	J is R - X
    );(   
    	I = R, 
    	J = 0
    )),
    \+ verLoop([A|B], [C|D], I, J),
    busca([I|[A|B]], [J|[C|D]], E), !.