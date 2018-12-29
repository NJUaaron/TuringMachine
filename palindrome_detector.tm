; This program checks if the input satisfy  1^m x 1^n = 1^(m+n)  model.
; eg '111 x 11 = 11111'

; the finite set of states
#Q = {0,1o,1i,2o,2i,3,4,accept,accept2,accept3,accept4,halt_accept,reject,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1,x,=}

; the complete set of tape symbols
#T = {1,x,=,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = 0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept,halt_reject}

; the transition functions

; State 0: read the leftmost symbol
0 1 _ r 1a
0 * * * reject     ; not 1

; State 1: find the rightmost symbol
1a _ _ l 2a
1a * * r 1a

1b _ _ l 2b
1b * * r 1b

; State 2: check if the rightmost symbol is 1
2a 1 _ l 3a
2a * * * reject

2b 1 _ l 3b
2b * * * reject

; State 3: return to left end of remaining input
3a _ _ r 4
3a * * l 3a

3b _ _ r 6
3b * * l 3b

; State 4: check if the leftmost symbol is x
4 x _ r 5
4 1 _ r 1a
4 = = * reject

; State 5: check if the leftmost symbol is 1
5 1 _ r 1b
5 * * * reject

; State 6: check if the leftmost symbol is =
6 = _ * accept
6 1 _ r 1c
6 x x * reject


accept * T r accept2
accept2 * r r accept3
accept3 * u r accept4
accept4 * e * halt_accept

reject * _ l reject
reject _ F r reject2
reject2 _ a r reject3
reject3 _ l r reject4
reject4 _ s r reject5
reject5 * e * halt_reject