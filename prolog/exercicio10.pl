% Ursula é bonita. 
% Norberto é rico e bonito. 
% Berta é rica e forte. 
% Pierre é forte e bonito. 
% Bruno é amável e forte. 
% Todos os homens gostam de mulheres bonitas. 
% Todos os homens ricos são felizes. 
% Qualquer homem que gosta de uma mulher que gosta dele é feliz. 
% Qualquer mulher que gosta de um homem que gosta dela é feliz. 
% Berta gostar de qualquer homem que gosta dela.
% Ursula gosta de qualquer homem que gosta dela, contanto que ele seja rico e amável ou bonito e forte.

% (a) Use Prolog para saber quem é feliz.
% (b) Para este problema especifico, pense uma regra razoável, 
% para adicionar à Base de Conhecimento, tal que todos são felizes.

bonito(ursula).
bonito(noberto).
bonito(pierre).

rico(noberto).
rico(berta).

forte(berta).
forte(pierre).

amavel(bruno).

homem(noberto).
homem(pierre).
homem(bruno).
mulher(ursula).
mulher(berta).

gostar(X,Y) :-
    homem(X),
    mulher(Y),
    bonito(Y).
gostar(berta,Y) :- 
    homem(Y),
    gostar(Y, berta).
gostar(ursula,Y) :-
    homem(Y),
    gostar(Y, ursula),
    ((rico(Y),amavel(Y));
    (bonito(Y),forte(Y))).
gostar(bruno, Y) :- % Regra adicionada
    mulher(Y),
	rico(Y).    

feliz(X) :- %
    homem(X),
    rico(X).
feliz(X) :- 
    homem(X),
    gostar(X,Y),
    mulher(Y),
    gostar(Y,X).
feliz(X) :-
    mulher(X),
    gostar(X,Y),
    homem(Y),
    gostar(Y,X).
