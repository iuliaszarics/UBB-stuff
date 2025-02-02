%a. Define a predicate to remove from a list all repetitive elements
%b. Remove all occurences of a maximum value from a list of integer numbers

% removeRepetitive(List, Result)
removeRepetitive([], []).  %daca lista e empty, rezultatul e tot empty list
removeRepetitive([H|T], R) :-   %nu punem H in resultat ca nu e bun ca apare de mai multe ori
    countOcc(H, T, Count),  %numaram de cate ori apare H in T folosind Count
    Count > 0,  %daca count e mai mare decat 0 inseamna ca i repetitiv si l scoatem
    removeAll(H, T, Rez),  %removeAll sa le scoatem pe toate si rezultatul e Rez
    removeRepetitive(Rez, R). %trecem mai departe la Rez care e lista fara elementu scos
removeRepetitive([H|T],[H|R]):-  %punem H in rezultat ca e bun ca apare numai o data
    countOcc(H,T,Count),     %numaram de cate ori apare H in T
    Count=:=0,               %daca apare doar o data
    removeRepetitive(T,R).   %trecem mai departe la tot tailu

% countOcc(Elem, List, Count)
countOcc(_, [], 0).        %daca avem lista gaoal Count e 0
countOcc(E, [H|T], Count) :-
    H =:= E,               % daca headu e egal cu elementu pe care vrem sa l numaram
    countOcc(E, T, Count1), %trecem mai departe
    Count is Count1 + 1.    %si crestem Count cu 1
countOcc(E, [H|T], Count) :-
    H \= E,                 %daca headu nu e egal cu elementu
    countOcc(E, T, Count).  %trecem mai departe

% removeAll(Elem, List, Result)
removeAll(_, [], []).        %daca avem lista goala, rezultatu e lista goala
removeAll(E, [H|T], R) :-    %cand nu pastram headu in rezultat:
    H=:=E,                   %cand headu e egal cu elementu
    removeAll(E, T, R).      %remove la element din restu listei
removeAll(E, [H|T], [H|R]) :-    %cand pastram headu in rezultat
    H \= E,                      %cand headu nu i egal cu elementu
    removeAll(E, T, R).          %trecem mai departe

% maxInList(List, Max)
maxInList([H|T], Max) :-
    maxInListAcc(T, H, Max).           %facem cu accumulator

% maxInListAcc(List, CurrentMax, Max)
maxInListAcc([], Max, Max).               %daca ajungem la empty list maximul ramane maximul curent
maxInListAcc([H|T], CurrentMax, Max) :-
    H > CurrentMax,                        %daca headu e mai mare decat maximul current
    maxInListAcc(T, H, Max).               %trecem mai departe in tail cu headu ca currentMax
maxInListAcc([H|T], CurrentMax, Max) :-
    H =< CurrentMax,                       %daca headu nu e mai mare decat maximul curent
    maxInListAcc(T, CurrentMax, Max).      %trecem mai departe in tail cu curentMax precedent

% removeAllMax(List, Result)
removeAllMax(List, Result) :-
    maxInList(List, Max),                  %cautam maximu
    removeAll(Max, List, Result).          %ii scoatem toate aparentele








