caminho_bp(Origem, Destino, Caminho) :-
    dfs(Origem, Destino, [Origem], Caminho).

dfs(Destino, Destino, Caminho, Caminho).

dfs(Atual, Destino, Visitados, Caminho) :-
    edge(Atual, Proximo, _),         
    \+ member(Proximo, Visitados),       
    dfs(Proximo, Destino, [Proximo|Visitados], Caminho).