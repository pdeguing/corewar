.name "zorkb"
.comment "I'M ALIIIIVE"

hello:		sti r1, %5, %9
		and r1, %0, r1
		live %9
		aff r3
		ld %8, r4
