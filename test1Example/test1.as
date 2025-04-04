; file test1.as

TEST:	    mov    r3, LENGTH
.entry TEST

.extern                      GAL
MAIN:	    mov    r3, LENGTH
LOOP:	    jmp    L1(#-1,r6)
		    mcr m1
			    sub    r1,r4
			    bne    END
		    endmcr m1
      	    	    prn    #-5
		    bne    LOOP(r4,r3)
		    m1
		    mcr m2
			    sub    r1,r4
			    bne    END
		    endmcr
			m2
		    mcr m3
			    sub    r1,r4
			    bne    END
		    endmcr
			m3
			mov r1, r7
L1:         inc    K
            bne    LOOP(K,STR)
END:        stop
STR:        .string "abcdehhhhf"
JJJJJJJJJJJJJJ:    .data +6, +7, +8, -7
K:          .data 22
m1