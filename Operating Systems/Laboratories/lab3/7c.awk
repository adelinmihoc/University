BEGIN {
	p = 1
}

{
	d = $3 - $4
	if(d != 0) {
		p = p*d
	}
}

END {
	print p
}
