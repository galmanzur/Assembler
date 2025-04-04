MAIN: add r3, LIST ic+=2 dc+=2 
LOOP: prn #48 ic+=2 dc+= 2
lea W, r6 IC+=2
inc r6 IC+=1
mov r3, K IC+=2
sub r1, r4 IC+=1
bne END IC+=2
cmp K, #-6 IC+=3
bne &END IC+=2
dec W IC+=2
jmp &LOOP IC+=2
add L3, L3 IC+=2
END: stop IC+=1 dc+=1
STR: .string "abcd" dc+=5
LIST: .data 6, -9 dc+=2
.data -100 dc+=1
K: .data 31 dc+=1
.extern L3

