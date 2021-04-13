% A. Correlation and Regression
% X,Y - two characteristics
% Find means, variances, covariance, correlation coefficient

clc

x = [20 * ones(1, 2), 21, 22 * ones(1, 3), 23 * ones(1, 6),...
    24 * ones(1, 5), 25 * ones(1, 9), 26 * ones(1, 2),...
    27 * ones(1, 2)];
% fprintf('%d ', x);

y = [75 * ones(1, 3), 76 * ones(1, 2), 77 * ones(1, 2), 78 * ones(1, 5)...
    79 * ones(1, 8), 80 * ones(1, 8), 81, 82];
%fprintf('%d ', y);

%a)
mx = mean(x);
my = mean(y);
fprintf('a) the means are: mx = %6.3f, my = %6.3f\n', mx,my);

%b)
vx = var(x, 1); % these are populations, not samples, hence, we use var(x,1)
vy = var(y, 1);
fprintf('b) the variances are: vx = %6.3f, vy = %6.3f\n', vx, vy);

%c), d)
c = cov(x, y, 1); % the covariance matrix
co = c(1, 2); % entry on position (1, 2) of the matrix
rr = corrcoef(x, y); % the correlatian coefficients matrix
ro = rr(1, 2); % entry on position (1, 2) of the matrix
fprintf('c) the covariance is: cov(x, y) = %6.3f\n', co);
fprintf('d) the corr. coeff. is: ro(x,y) = %6.3f\n', ro);






