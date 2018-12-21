; This program checks if the input satisfy  1^m x 1^n = 1^(m*n)  model.
; eg '111 x 11 = 111111'

; the finite set of states
#Q = {0_0,0_1,1,2_0,2_1,3,4,5,6,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject1,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {1,x,=}

; the complete set of tape symbols
#T = {1,0,x,=,_,T,r,u,e,F,a,l,s}

; the start state
#q0 = 0_0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the transition functions

; State 0: read the leftmost symbol
0_0 1 _ r 1
0_0 * * * reject     ; not 1

0_1 1 _ r 1
0_1 x _ r accept
0_1 * * * reject

; State 1: find the first '1' after 'x'
1 1 1 r 1
1 x x r 2_0
1 * * * reject

; State 2: turn '1' to '0'
2_0 1 0 r 3
2_0 * * * reject

2_1 1 0 r 3
2_1 = = l 6
2_1 * * * reject

; State 3: find the rightmost '1'
3 _ _ l 4
3 * * r 3

; State 4: delete the rightmost '1'
4 1 _ l 5
4 * * * reject

; State 5: return to the first '1' after 'x'
5 0 0 r 2_1
5 * * l 5 

; State 6: return to the leftmost '1' and turn all the '0' to '1'
6 0 1 l 6
6 _ _ r 0_1
6 * * l 6


accept _ _ l accept1
accept * * r accept
accept1 _ T r accept2
accept1 * _ l accept1
accept2 * r r accept3
accept3 * u r accept4
accept4 * e * halt_accept


reject _ _ l reject1
reject * * r reject
reject1 _ F r reject2
reject1 * _ l reject1
reject2 * a r reject3
reject3 * l r reject4
reject4 * s r reject5
reject5 * e * halt_reject