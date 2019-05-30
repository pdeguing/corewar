.name "zork"
.comment "I'M ALIIIIVE"

live:
l2:		sti r2, %:live, %1
		and r2, %0, r2

live:	live %1
		zjmp %:live
