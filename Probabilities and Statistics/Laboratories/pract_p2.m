%To reach the maximum efficiency in performing an assembling operation in a
%manufacturing plant, new employees are required to take 1-month training
%course. A new method was suggested, and the manager wants to compare the
%new method with the standard one, by looking at the lengths of time
%required for employees to assemble a certain device. They are given below
%(and assumed approximately normally distributed):
%a. At the 5% significance level, do the population variances seem to
%differ?
%b. Find a 95% confidance interval for the difference of the average
%assembling times.
clc

x1 = [46, 37, 39, 48, 47, 44, 35, 31, 44, 37]; %sample test 1
x2 = [35, 33, 31, 35, 34, 30, 27, 32, 31, 31]; %sample test 2


n1 = length(x1);
n2 = length(x2);
v1 = var(x1);
v2 = var(x2);

alpha = input('significance level alpha = ');
fprintf('a.');

%H0: sigma1 = sigma2
%H1: sigma1 != sigma 2 --two tailed test

[H, P, CI, stats] = vartest2(x1, x2, "alpha", alpha);
%quantiles for the two tailed test:
f1 = finv(alpha/2, n1 - 1, n2-1);
f2 = finv(1-alpha/2, n1-1, n2-1); 

if H == 0
   fprintf('H is %d\nSo the null hypothesis is not rejected\nThe variances seem to be equal', H);
   fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
   fprintf('The vale of the test statistic F is %6.4f\n', stats.fstat);
   fprintf('The P-value for the variances test is %6.4f\n', P);
else
   fprintf('H is %d\nSo the null hypothesis is  rejected\nThe variances seem to not be equal', H);
   fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
   fprintf('The vale of the test statistic F is %6.4f\n', stats.fstat);
   fprintf('The P-value for the variances test is %6.4f\n', P);
end

%part b
m1 = mean(x1);
m2 = mean(x2);

c = (v1/n1)/(v1/n1 + v2/n2);
nn = 1/(c^2 /(n1-1) + (1-c)^2/(n2-1));
s = sqrt(v1/n1 + v2/n2);
qq = tinv(1-alpha, nn);
mdiff =m1-m2;
mm1 = mdiff - qq * s;
mm2 = mdiff + qq * s;
fprintf('b. Confidence interval for diff. of means, variances not equal (mm1, mm2) = (%6.4f, %6.4f)\n', mm1, mm2);




