%3. Write a predicate to determine all decomposition of n (n given,
% positive) as sum of consecutive natural numbers

%luam toate numerele dintre 2 numere
% between(Start:integer ,End:integer, Nr:integer)
inBetween(Start, End, Nr) :-
    Start =< End,     %daca start<=end
    Nr = Start.        %nr o sa fie Start
inBetween(Start, End,Nr) :-
    Start < End,      %daca start<end
    Start1 is Start + 1,       %incrementam start cu 1
    inBetween(Start1, End, Nr).       %trecem mai departe



%generam perechile de nr astfel incat suma lor e N
% generatePair(N - number we want to get, X - first of the pair, Y -
% second)
%generatePair(i,o,o)
generatePair(N, X, Y) :-
    inBetween(1, N, X), %luam un X din intervalu [1,N]
    inBetween(1, N, Y), %luam un Y din intervalu [1,N]
    X < Y,              %X trebe sa fie mai mic decat Y ca sa nu se repete perechile
    N =:= X + Y.        %suma lor sa fie N

%descompunem N intr o lista de int astfel inczt suma lor sa fie N
% decomposeNumber(N - number we want to get, L - list of all possible
% pairs)
%decomposeNumber(i,o)
decomposeNumber(N, [X|L]) :- %punem X in rezultat
    generatePair(N, X, Y),   %daca X are o pereche Y cu care sa fie suma N
    decomposeNumber(Y, L).   %trecem mai departe cu Y pt ca N-X=Y
decomposeNumber(N, [N]).   %daca nu gasim nr care sa inseplineasca conditiile, rezultatu e lista doar cu numaru

%verficam nr din lista sa fie consecutive
isConsecutive([X,Y]):-
    X+1=:=Y.
isConsecutive([H1,H2|T]):-
    H2=:=H1+1,
    isConsecutive([H2|T]).


%amu luam numa listele cu nr consecutive
nAsSumOfConsecutives(N,L):-
    decomposeNumber(N,List),  %descompunem N intr-o lista
    isConsecutive(List),      %daca nr din lista is consecutive
    L=List.                   %rezultatu primeste acea lista

%main: findall listsof consecutive numbers whose sum  adds up to n
main(N,L):-
    findall(R,nAsSumOfConsecutives(N,R),L).
% gasim toate listele care reprezinta decompozitia lui N ca suma de nr
% consecutiv







