.name "lldi"
.comment "I'M ALIIIIVE"

lldis: live %1 
#test dir dir
test2:
	lldi -66666, %178520066, r9
	st r9, 0
	lldi -66666, %43648261, r10
	lldi -66666, r9, r11
	lldi -666666666, r10, r12
	lldi 0, %0, r1
	lldi 2, %0, r2
	lldi 4, %3, r3
	lldi 3, %-4, r4
	lldi -4, %3, r5
	lldi -5, %-5, r6
	lldi 666, %-666, r7
	lldi 66666, %10, r8
	lldi 66666, %666, r9
	lldi 66666, %-10, r10
	lldi 66666, %-666, r11
	lldi 666666666, %10, r12
	lldi 666666666, %666, r13
	lldi 666666666, %-10, r14
	lldi 666666666, %-666, r15
	lldi :lldis, %-666, r1
	lldi :test3, %-666, r2
	lldi 193, %-20, r3
	lldi 193, %-900, r4
	lldi -666, %193, r5
	lldi -666, %-193, r6
	lldi -666, %-666, r7
	lldi -66666, %10, r8
	lldi -66666, %666, r9
	lldi -66666, %-10, r10
	lldi -66666, %-666, r11
	lldi -666666666, %10, r12
#test dir reg
test3:
	lldi 0, r1, r1
	lldi 193, r2, r2
	lldi 193, r3, r3
	lldi 193, r4, r4
	lldi 666, r5, r5
	lldi 666, r6, r6
	lldi 666, r7, r7
	lldi 66666, r8, r8
	lldi 66666, r9, r9
	lldi 66666, r10, r10
	lldi 66666, r11, r11
	lldi 666666666, r12, r12
	lldi 666666666, r13, r13
	lldi 666666666, r14, r14
	lldi 666666666, r15, r15
	lldi :lldis, r2, r1
	lldi :test3, r3, r2
	lldi 193, r1, r3
	lldi 193, r2, r4
	lldi -666, r3, r5
	lldi -666, r4, r6
	lldi -666, r5, r7
	lldi -66666, r6, r8
	lldi -65538, r7, r9
	lldi -66666, r8, r10
	lldi -66666, r9, r11
	lldi -666666666, r10, r12
#test ind dir
#test ind reg
#test reg dir
##test reg reg
