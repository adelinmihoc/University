procedure sum(a,b) v=a+b;print(v)


procedure product(a,b) v=a*b;print(v)


and the main program is

int v;
int w;
v=2;
w=5;
call sum(v*10,w);
print(v);

fork(
	call product(v,w);
	fork(
		call sum(v,w)
	)
)

The final Out should be {25,2,10,7}