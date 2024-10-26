% Traduza as seguintes sentenças para Prolog:
% Tweety é um pássaro. Goldie é um peixe. Squiggly é uma minhoca. Pássaros gostam de minhoca.
% Gatos gostam de peixe. Gatos gostam de pássaros. Amigos se gostam. Meu gato é meu amigo.
% Meu gato come tudo o que ele gosta.

passaro(tweety).
peixe(goldie).
minhoca(squiggly).
gato(meu_gato).

amigo(meu_gato, eu).

gostar(X,Y) :-
    passaro(X),
    minhoca(Y).
gostar(X,Y) :-
    gato(X),
    (peixe(Y);passaro(Y)).
% gostar(X,Y) :- amigo(X,Y).

come(meu_gato,Y) :- gostar(meu_gato, Y).

% (a) Use Prolog para determinar o que come meu gato.

% (b) A resposta é razoável? Se não for, verifique se o problema está na especificação original ou na sua
% tradução para Prolog, corrija e execute novamente.
% R: tá na especificação
