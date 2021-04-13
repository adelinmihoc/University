%A food store owner receives 1-liter water bottles from two suppliers.
%After some complaints from customers he wants to check the accuracy of the
%weights of 1-liter water bottles. He finds the following weights (the two
%populations are approximately normally distributed):
%a. At the 5% significance level, do the populations variances seem to
%differ?
%b. At the same significance level, on average, does Supplier A seem to be
%more reliable?

clc

%The samples:
x1 = [1021, 980, 1017, 988, 1005, 998, 1014, 985, 995, 995, 1004, 1030, 1015, 995, 1023];
x2 = [1070, 970, 993, 1013, 1006, 1002, 1014, 997, 1002, 1010, 975];

%The lengths of the samples:
n1 = length(x1);
n2 = length(x2);

%The means of the samples:
m1 = mean(x1);
m2 = mean(x2);

%The variances of the samples:
v1 = var(x1);
v2 = var(x2);

%Part a.
fprintf('Part a.\n');

alpha = 0.05; % 5% significance level

%Test
%the null hypothesis H0: sigma1 = sigma2
%the alt. hypothesis H1: sigma1 != sigma2
% This is a two tailed test for the ratio of the variances

%the quantiles for the two tailed test
f1 = finv(alpha/2, n1 - 1, n2 - 1);
f2 = finv(1-alpha/2, n1 - 1, n2 - 1);

[H, P, CI, stats] = vartest2(x1, x2, "alpha", alpha);

fprintf('Comparing variances with a two tailed test:\n');
if H == 0
   fprintf('H is %d\n so the null hypothesis is not rejected\n i.e the variances seem to be equal\n', H);
   fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
   fprintf('The value of the test statistic F is %6.4f\n', stats.fstat);
   fprintf('The P-value for the variances test is %6.4f\n', P);
else
   fprintf('H is %d\n so the null hypothesis is rejected\n i.e the variances seem to not be equal\n', H);
   fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
   fprintf('The value of the test statistic F is %6.4f\n', stats.fstat);
   fprintf('The P-value for the variances test is %6.4f\n', P);
end


fprintf('\nPart b.\n');
% the null hypothesis H0: mu1 = mu2
% the alt. hypothesis H1: mu1 > mu2
%right tailed test fot the difference of means

%in the point a we found that the variances seem to be equal
% so perform a test for the difference of the populations means with sigma1
% = sigma2 unknown

[H1, P1, CI1, stats1] = ttest2(x1, x2, "alpha" , alpha, "tail", "right");
t2 = tinv(1 - alpha, n); %the quantile for right tailed test
n = n1 + n2 - 2;
if H1 == 0
    fprintf('H is 0 so the null hypothesis is rejected\n first supplier does seem more reliable\n');
else
    fprintf('H is 1 so the null hypothesis is not rejected\n first supplier does not seem more reliable\n');
end

fprintf('The rejection region for T is (%6.4f, %6.4f)\n', t2, inf);
fprintf('The value of the test statistic T is %6.4f\n',stats1.tstat);
fprintf('The P-value of the test for diff. of means is %e\n\n\n', P1);

