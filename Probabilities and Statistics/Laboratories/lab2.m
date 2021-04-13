n = input('nr of trials n=');
p = input('probability of success p=');
x=0:n;
px=binopdf(x,n,p);
plot(x,px,'r+');
hold on
xx=0:0.01:n;
pxx=binocdf(xx,n,p);
plot(xx,pxx,'m');
legend('pdf','cdf');