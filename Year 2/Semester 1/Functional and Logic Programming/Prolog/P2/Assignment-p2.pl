%3.a. Merge two sorted lists with removing the double values
%merge(L1:list,L2:list,Res:resulted list)
%merge(i,i,o)

merge([],[],[]).  %daca avem 2 empty lists rezultatu e tot empty list
merge([],L,L).   %daca avem un empty list si o lista, rezultatu e lista cu elem
merge(L,[],L).   %la fel aci
merge([H1|T1],[H2|T2],[H1|Res]):-   %cand punem H1 in lista:
    H1<H2,                          %H1 mai mic ca H2
    merge(T1,[H2|T2],Res).          %trecem mai departe
merge([H1|T1],[H2|T2],[H2|Res]):-  %cand punem H2 2 in lista:
    H1>H2,                         %H2 mai mic ca H1
    merge([H1|T1],T2,Res).         %trecem mai departe
merge([H|T1],[H|T2],[H|Res]):-     %daca is egale numerele, il punem o data in rez
    merge(T1,T2,Res).              %si daca


% b. For a heterogeneous list, formed from integer numbers and list of
% numbers, merge all sublists with removing the double values.

% get_sublists_from_list(L:list, Res:list of all sublists)
% get_sublists_from_list(i,o)

get_sublists_from_list([],[]).         %daca avem empty list, reultatu e empty list
get_sublists_from_list([H|T],[H|R]):-   %cand punem H in rezultat:
    is_list(H),                         %cand H e lista
    get_sublists_from_list(T,R).        %trecem mai departe
get_sublists_from_list([_|T],R):-       %daca nu e lista nu l punem in rezultat
    get_sublists_from_list(T,R).


merge_list_of_sublists([],[]).          %daca avem empty list, rezultatu e empty list
merge_list_of_sublists([L],L).          %daca avem o singura lista, rezultatu e acea lusta
merge_list_of_sublists([H1,H2|T],Result):-      %luam primele doua liste din lista mare
    merge(H1,H2,Res),                          % le dam merge
    merge_list_of_sublists([Res|T],Result).       %dupa rezultatu in punem ca head la lista initiala, si dam merge la lista

merge_sublists(List, Res) :-
    get_sublists_from_list(List, Sublists),      %scoatem sublistele din liste
    merge_list_of_sublists(Sublists, Res).       %le dam merge















