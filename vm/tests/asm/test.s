;basic.s

.name		"basic"
.comment	"this is a basic stuff"

loop:
	st r1, 6
	live %7
	ld %255, r2
	st r2, r1
	sti r1, %:loop, %6
