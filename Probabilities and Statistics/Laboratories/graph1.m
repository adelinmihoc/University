x = 0:0.01:3;
f1 = @(x) x.^5./10;
f2 = @(x) x.*sin(x)
f3 = @(X) cos(x)

%plot(x,f1(x),'r--',x,f2(x),'m+',x,f3(x),'g-.');
title("Graph1");
%legend("data1","data2","data3");
subplot(3,1,1): plot(x,f1(x));
subplot(3,1,2): plot(x,f2(x));
subplot(3,1,3): plot(x,f3(x));