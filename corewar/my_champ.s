.name "minus_42"
.comment "I'M CHEATER"

l2:		fork %:l3
sti r1, %:live, %1
live %1
fork %:l3
live %1
fork %:l3
live %1
fork %:l3
live %1
fork %:l3

l3: sti r1, %:live, %1
ld %0, r2

live:	live %1
		zjmp %:live
