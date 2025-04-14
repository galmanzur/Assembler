.entry GAL
.extern CHECK
CHECK: mov r1, r2
TEST: inc r5
test: inc r6
GAL: .string "gal"
itswork: dec r5
.entry LIKE
LIKE: cmp r6, r6
;hi
jmp &LIKE
jsr test
red r2
prn r3
rts
stop
dec Count
Count: .data -100
not r5
MaabadaIsFun: .string "yess"
