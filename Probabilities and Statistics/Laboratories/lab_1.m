% 1. For the matrices A and B print
% C = A-B, D=A*B, E=[ij], eij = aij*bij
clc
clf

A = [1 0 -2; 2 1 3; 0 1 0];
B = [2 1 1; 1 0 -1; 1 1 0];

C = A - B;
D = A * B; % matrix multiplication
E = A .* B; % dot multiplication

fprintf('C = \n')
fprintf(' %2d %2d %2d\n', C); %print the transpose, matlab goes on columns
fprintf('D = \n');
fprintf(' %2d %2d %2d\n', D);
fprintf('E = \n');
fprintf(' %2d %2d %2d\n', E);


%2. For x in [0,3], graph in the same set of axes the functions x^5/10
% xsinx and cosx, in different colors and linestyles. Display a title and a
% legend on your graph. Then plot them on different pictures, but in the
% same window.

x = 0 : 0.01 : 3; %simulate continuity of the interval
y4 = x .^5 ./10;
ysin = x .*sin(x);
ycos = cos(x);

%plot(x, y4, x, ysin, 'r-.', x, ycos, 'm--');
legend('fifthpower', 'xsin(x)', 'cos(x)')
title('Titlu')
% for subplot
subplot(3,1,1); plot(x, y4); 
subplot(3,1,2); plot(x,ysin);
subplot(3,1,3); plot(x,ycos);





