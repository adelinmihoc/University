clc

%part a
fprintf('Part a.\n');

x = [20 * ones(1, 2), 21 * ones(1, 1), 22* ones(1, 3), 23* ones(1, 6), 24* ones(1, 5), ...
    25* ones(1, 9), 26* ones(1, 2), 27* ones(1, 2)];
y = [75* ones(1, 3), 76* ones(1, 2), 77* ones(1, 2), 78* ones(1, 5), 79* ones(1, 8), 80* ones(1, 8), 81, 82];

%means 
m1 = mean(x);
m2 = mean(y);
fprintf('The means are %6.4f and %6.4f\n', m1, m2);

%variances
v1 = var(x, 1); % 1 because they are populations not samples
v2 = var(y, 1);
fprintf('The variances are %6.4f and %6.4f\n', v1, v2);

%covariances
c = cov(x, y, 1); %result is a matrix
co = c(1,2);
fprintf('The covariance is %6.4f\n', co);

%the correlation coefficient
cc = corrcoef(x, y); %result is a matrix
cco = cc(1,2);
fprintf('The corelation coefficient is %6.4f\n\n', cco);

clc

%part B Confidence Intervals

%1.=======================================================================================
x = [7 7 4 5 9 9 4 12 8 1 8 7 3 13 2 1 17 7 12 5 6 2 1 13 14 10 2 4 9 11 3 5 12 6 10 7];
n = length(x);
m = mean(x);
%a.------------------------------------------------------------------------
sigma = 5;
alpha = input('significance level alpha = ');

% for a population mean sigma known

%quantiles
q1 = norminv(1-alpha/2);
q2 = norminv(alpha/2);

%limits of the confidence interval
l1 = m - sigma/sqrt(n)*q1;
l2 = m - sigma/sqrt(n)*q2;

fprintf('a) The confidence interval for the mean (sigma known) is (l1, l2)=  (%6.4f, %6.4f)\n', l1, l2);


%b-------------------------------------------------------------------------
samp_std = std(x); % the standard deviation of the sample

%the quantiles 
t1 = tinv(1-alpha/2, n - 1);
t2 = tinv(alpha/2, n - 1);

%the limits of the confidence interval
l12 = m - samp_std/sqrt(n) * t1;
l22 = m - samp_std/sqrt(n) * t2;

fprintf('b) The confidence interval for the mean (sigma unknown) is (l1, l2)=  (%6.4f, %6.4f)\n', l12, l22);

%c)------------------------------------------------------------------------
v = var(x);
q12 = chi2inv(1-alpha/2, n-1);
q22 = chi2inv(alpha/2, n-1);

%the limits of the confidence interval for the variance
v1 = ((n-1)*v)/q12;
v2 = ((n-1)*v)/q22;

fprintf('c) The confidence interval for the variance is (l1, l2)=  (%6.4f, %6.4f)\n', v1, v2);

%the limits of the confidence interval for the standard deviation
s1 = sqrt(v1);
s2 = sqrt(v2);

fprintf('c) The confidence interval for stadard deviation is (l1, l2)=  (%6.4f, %6.4f)\n', s1, s2);

clc

%=========================================================================================================

%2.=======================================================================================================

x = [22.4, 21.7, 24.5, 23.4, 21.6, 23.3, 22.4, 21.6, 24.8, 20.0];
y = [17.7, 14.8, 19.6, 19.6, 12.1, 14.8, 15.4, 12.6, 14.0, 12.2];

n1 = length(x);
n2 = length(y);

m1 = mean(x);
m2 = mean(y);

v1 = var(x);
v2 = var(y);

%a.------------------------------------------------------------------------

%case sigma1 = sigma2
q13 = tinv(1- alpha/2, n1 + n2 -2);

sp = sqrt(((n1 - 1)*v1 + (n2 - 1)*v2)/n1 + n2 -2);

%limits of the confidence interval
l10 = m1 -m2 - q13 * sp * sqrt(1/n1 + 1/n2);
l11 = m1 -m2 + q13 * sp * sqrt(1/n1 + 1/n2);

fprintf('a) The confidence interval for the diff. of means (sigma1 = sigma2)  is (l1, l2)=  (%6.4f, %6.4f)\n', l10, l11);


%b-------------------------------------------------------------------------
% case sigma1 != sigma2
c = (v1/n1)/(v1/n1 + v2/n2);
n = 1/(c ^ 2/(n1 - 1) + (1-c)^2/(n2 - 1));
q14 = tinv(1-alpha/2, n);

%the limits of the confidence interval
l13 = m1-m2-q14*sqrt(v1/n1 + v2/n2);
l14 = m1-m2+q14*sqrt(v1/n1 + v2/n2);
fprintf('b) The confidence interval for the diff. of means (siqma1 != sigma2) is (l1, l2)=  (%6.4f, %6.4f)\n', l13, l14);

%c.------------------------------------------------------------------------
% CI for the ratio of variances
q15 = finv(1-alpha/2, n1 - 1, n2 - 1);
q16 = finv(alpha/2, n1 - 1, n2 - 1);

l15 = v1/ (q15 * v2);
l16 = v1/ (q16 * v2);

fprintf('a) The confidence interval for the ratio of variances is (l1, l2)=  (%6.4f, %6.4f)\n', l15, l16);


