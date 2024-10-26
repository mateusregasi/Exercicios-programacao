% Considerando que os dias formam o universo de discurso, formalize em Lógica de Predicados os enunciados
% a seguir. Após, faça uma tradução de cada sentença para uma cláusula em Prolog, identificando as
% dificuldades declaradas em cada uma delas. Assuma que não há interdependência entre as sentenças.

% (a) Todo dia têm aula de Lógica.
% \forall d \in \{ dias \} p(d) \text{ onde p(x) : no dia x tem aula de lógica}

% dia(d,m,a).
dia_aula_logica(D,M,A) :- dia(D,M,A).
    
% (b) Sempre que tem aula de Lógica tem aula de Matemática.
% p(d) \rightarrow q(d) \text{ onde q(x): no dia x tem aula de matemática}

dia_aula_matematica(D,M,A) :- dia_aula_logica(D,M,A).
 
% (c) Quando tem aula de Programação não tem aula de Lógica.
% r(d) \rightarrow \not p(d) \text{ onde r(x): no dia x tem aula de programação

dia_aula_logica(D,M,A) :- dia_aula_programação(D,M,A).

% (d) Nunca tem aula de Lógica nos domingos.
% d\text{ é no domingo } \rightarrow \not p(d)

% domingo(dia(D,M,A)).
dia_aula_logica(D,M,A) :- \x domingo().

% (e) Um mesmo dia, ou tem aula de Lógica ou de Programação.
dia_aula_logica(D,M,A) :- \x dia_aula_programacao(D,M,A).
dia_aula_programacao(D,M,A) :- \x dia_aula_logica(D,M,A).
    
