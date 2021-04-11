BEGIN {
	sum = 0
}

{
	p = $3 * $4
	sum = sum + p
}

END {
	print sum
}
