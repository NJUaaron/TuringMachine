; This program checks if the input satisfy  {ww|w belongs to {a,b}*}.
; eg 'abbabb'

; the finite set of states
#Q = {q0,fa,fb,left,check,aright,bright,clean,accept,accept1,accept2,accept3,accept4,halt_accept,reject,reject1,reject2,reject3,reject4,reject5,halt_reject}

; the finite set of input symbols
#S = {a,b}

; the complete set of tape symbols
#T = {a,b,p,q,A,B,M,S,T,m,n,P,Q,r,u,e,F,a,l,s}

; the start state
#q0 = q0

; the blank symbol
#B = _

; the set of final states
#F = {halt_accept}

; the transition functions

; State q0: read the leftmost symbol
q0 a S r fa
q0 b T r fb
q0 _ _ * accept

; State fa(fb): find the first a(b)
fa a M * left1
fa _ _ l reject
fa M m r fa
fa * * r fa

fb b M * left1
fb _ _ l reject
fb M n r fb
fb * * r fb

; State left1: return to left of M
left1 M M l left2
left1 * * l left1

; State left2: return to left end of remaining input(except p,q)
left2 S S r check
left2 T T r check
left2 p p r check
left2 q q r check
left2 P P r check
left2 Q Q r check
left2 * * l left2

; State check: check the leftmost(except p,q) symbol
check a q r aright1
check b p r bright1
check m Q r aright1
check n P r bright1
check M M * nright1

; State right1: go to right of M
aright1 M M r aright2
aright1 * * r aright1

bright1 M M r bright2
bright1 * * r bright1

nright1 M M r nright2
nright1 * * r nright1

; State right2: go to right(except p,q) of M
aright2 p p r aright2
aright2 q q r aright2
aright2 a q l left1
aright2 * * * clean

bright2 p p r bright2
bright2 q q r bright2
bright2 b p l left1
bright2 * * * clean

nright2 p p r nright2
nright2 q q r nright2
nright2 _ _ l accept
nright2 * * * clean

; State clean: make q,p back to a,b
clean q a l clean
clean p b l clean
clean q a l clean
clean p b l clean
clean Q m l clean
clean P n l clean
clean S S r fa
clean T T r fb
clean * * l clean


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