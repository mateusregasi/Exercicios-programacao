% Função de avaliação heurística que consiste na distância entre dois nós
avaliacao(Origem, Dest, Resultado) :-
    node(Origem, Xo, Yo),
    node(Dest, Xd, Yd),
    Resultado is ceil(abs((Xd - Xo) ** 2 + (Yd - Yo) ** 2) ** 0.5).

% Insere nó ordenado em uma fila de prioridades
insNoOrd([noFila([A|CaudaA],CA)|B], noFila([H|CaudaH],CH), Res, Dest) :- 
    avaliacao(A,Dest,AA),
    avaliacao(H,Dest,AH),
    TA is AA + CA,
    TH is AH + CH,
    (TH =< TA ->
		Res = [noFila([H|CaudaH],CH)|[noFila([A|CaudaA],CA)|B]]
    ;
		(B = [] ->
			Res = [noFila([A|CaudaA],CA)|noFila([H|CaudaH],CH)]
        ;   
			insNoOrd(B,noFila(H,CH),L,Dest),
			Res = [noFila([A|CaudaA],CA)|L]
        )

    )
    , !.

% Verifica se determinado elemento está em uma lista
naLista(Elemento, [Elemento|_]) :- !.
naLista(Elemento, [_|B]) :- naLista(Elemento, B).

% Verifica se determinado elemento está na fila de prioridade com nós nesse formato: noFila(ListaDeCaminho, CustoDoCaminho)
naFila(Elemento, noFila([Elemento|_], _)) :- !.
naFila(Elemento, [noFila([Elemento|_], _)|_]) :- !.
naFila(Elemento, [noFila([_|_], _)|Proximo]) :-
    naFila(Elemento, Proximo).

% À partir de um nó, pega os filhos e ordena os caminhos do menos custoso para o mais custoso 
ordenaFilhos(Dest,noFila([Origem|CaminhoAnterior],Custo),[],FilaFinal) :-
	edge(Origem,Filho,CustoFilho),
    \+ naLista(Filho,CaminhoAnterior),
	CustoTotal is Custo + CustoFilho,
    ordenaFilhos(Dest,noFila([Origem|CaminhoAnterior],Custo),[noFila([Filho|[Origem|CaminhoAnterior]], CustoTotal)],FilaFinal),!.
ordenaFilhos(Dest,noFila([Origem|CaminhoAnterior],Custo),FilaAnterior,FilaFinal) :-
	edge(Origem,Filho,CustoFilho),
    \+ naFila(Filho,FilaAnterior),
    \+ naLista(Filho,CaminhoAnterior),
	CustoTotal is Custo + CustoFilho,
    insNoOrd(FilaAnterior,noFila([Filho|[Origem|CaminhoAnterior]],CustoTotal),ProxFila, Dest),
    ordenaFilhos(Dest,noFila([Origem|CaminhoAnterior],Custo),ProxFila,FilaFinal),!.
ordenaFilhos(_,_,FilaAnterior,FilaFinal) :-
    FilaFinal = FilaAnterior.

% Concatena a fila de prioridade dos filhos achados pelo ordenaFilhos() com a fila de prioridades acumulada na função de busca
insFilaPrioridades(A, [], A, _) :-!.
insFilaPrioridades([], B, B, _) :-!.
insFilaPrioridades([noFila([A|CaudaA],CA)|FilaA], [noFila([B|CaudaB],CB)|FilaB], [Res|ProxFila], Dest) :-
    avaliacao(A,Dest,AA),
    avaliacao(B,Dest,AB),
    TA is CA + AA,
    TB is CA + AB,
    (TA =< TB -> 
    		insFilaPrioridades(FilaA, [noFila([B|CaudaB], CB)|FilaB], ProxFila, Dest),
        	Res = noFila([A|CaudaA],CA)
    	; 
    		insFilaPrioridades([noFila([A|CaudaA], CA)|FilaA], FilaB, ProxFila, Dest),
    		Res = noFila([B|CaudaB],CB)
    ),!.
insFilaPrioridades(noFila([A|CaudaA],CA), [noFila([B|CaudaB],CB)|FilaB], [Res|ProxFila], Dest) :-
	avaliacao(A,Dest,AA),
    avaliacao(B,Dest,AB),
    TA is CA + AA,
    TB is CA + AB,
    (TA =< TB -> 
    		insFilaPrioridades([], [noFila([B|CaudaB], CB)|FilaB], ProxFila, Dest),
        	Res = noFila([A|CaudaA],CA)
    	; 
    		insFilaPrioridades(noFila([A|CaudaA], CA), FilaB, ProxFila, Dest),
    		Res = noFila([B|CaudaB],CB)
    ),!.
insFilaPrioridades([noFila([A|CaudaA],CA)|FilaA], noFila([B|CaudaB],CB), [Res|ProxFila], Dest) :-
    avaliacao(A,Dest,AA),
    avaliacao(B,Dest,AB),
    TA is CA + AA,
    TB is CA + AB,
    (TA =< TB -> 
    		insFilaPrioridades(FilaA, noFila([B|CaudaB], CB), ProxFila, Dest),
        	Res = noFila([A|CaudaA],CA)
    	; 
    		insFilaPrioridades([noFila([A|CaudaA], CA)|FilaA], [], ProxFila, Dest),
    		Res = noFila([B|CaudaB],CB)
    ),!.
insFilaPrioridades(noFila([A|CaudaA],CA), noFila([B|CaudaB],CB), [Res|ProxFila], Dest) :-
    avaliacao(A,Dest,AA),
    avaliacao(B,Dest,AB),
    TA is CA + AA,
    TB is CA + AB,
    (TA =< TB -> 
        	Res = noFila([A|CaudaA],CA),
    		ProxFila = noFila([B|CaudaB],CB)
    	; 
    		Res = noFila([B|CaudaB],CB),
    		ProxFila = noFila([A|CaudaA],CA)
    ),!.

% Função de busca principal do programa. Consiste em pegar o caminho atual, verificar os filhos do último nó, ordenar os caminhos na fila de prioridade pelo menos custoso, e partir pro primeiro elemento da fila de prioridades. Quando acha o destino, para o algoritmo. Se não achar nada retorna uma fila nula.
busca(noFila([Dest|Caminho], _),Dest,CaminhoFinal) :-
    CaminhoFinal = [Dest|Caminho], !.
busca([noFila(A,_)|B],Dest,A) :-
    naFila(Dest,[noFila(A,_)|B]), !.
busca([],_,[]).

busca([NoAtual|RestoFila], Dest, Caminho) :- 
    ordenaFilhos(Dest,NoAtual,[],Filhos),
    insFilaPrioridades(Filhos,RestoFila,NovaFila,Dest),
    busca(NovaFila,Dest,Caminho),!.
busca([_|RestoFila], Dest, Caminho) :- 
    busca(RestoFila,Dest,Caminho),!.

busca(NoAtual, Dest, Caminho) :- 
    ordenaFilhos(Dest,NoAtual,[],Filhos),
    insFilaPrioridades(Filhos,[],NovaFila,Dest),
    busca(NovaFila,Dest,Caminho),!.
busca(_, Dest, Caminho) :- 
    busca([],Dest,Caminho).

% Função que chama a função de busca
caminho(Origem, Dest, Lista) :-
    avaliacao(Origem,Dest,CustoInicial),
    busca([noFila([Origem], CustoInicial)], Dest, Lista).