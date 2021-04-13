%6.1. In a study of the size of various computer systems, the random
%variable X, the number of files stored, is cosidered. If a cimputer system
%cannot store at least 9, in average, it does not meet the efficiency
%standard and has to be replaced. *some data obtained*
%a.Assuming that past experience indicates that sigma = 5, at the 5%
%significance level, does the data suggest that the standard is met?
%b.Without the assumption on sigma, does the data suggest that, on average,
%the number of files stored exceeds 5.5? (same significance level).


clc

alpha = input('Significance level alpha = ');

x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7,...
   12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];
n = length(x);

%a) the null hypothesis H0: mu = 9
% the alt. hypothesis H1: mu < 9. This is a left-tailed test for mu

fprintf('Part a: ');
fprintf('\nLeft-tailed test for the mean (sigma known)\n');
sigma = 5;

m0 = input('Test value m0 = '); %m0 = teta0
%m0 is in this case 9.

[H, P, CI, zstat] = ztest(x, m0, sigma, "alpha", alpha, "tail", "left");
%z1 = norminv(1-alpha); for the right-tailed test
z2 = norminv(alpha);
RR = [-inf, z2]; % rejection region for left-tailed test
fprintf('\nH is %d', H);
if H == 1 %result of the test , h = 0, if H0 is not rejected, h = 1, if Ho is rejected
    fprintf('\nSo the null hypothesis is rejected,\n');
    fprintf('i.e. the data suggests that the standard is not met.\n');
else
    fprintf('\nSo the null hypothesis is not rejected.\n');
    fprintf('i.e. the data suggests that the standard is met.\n');
end

fprintf('The confidence interval for mu is (%4.4f, %4.4f)\n', CI);
fprintf('The rejection region is (%4.4f, %4.4f)', RR);
fprintf('The value of the test statistic z is %4.4f\n', zstat);
fprintf('The P-value of the test is %4.4f\n', P);

 
%b)
%the null hypothesis H0 = mu = 5.5
%the alternative hypothesis H1: mu > 5.5. This is a right-tailed test for
%mu

fprintf('\nPart b:');
fprintf('\nRight-tailed test for the mean (sigma unknown)\n');

m0b = input('test value m0 = ');
%m0 in this case is 5.5
[H, P, CI, stats] = ttest(x, m0b, "alpha", alpha, "tail", "right"); % 1, for right-tailed
t1 = tinv(1 - alpha, n-1); %quantile for right-tailed test
RR = [t1, Inf]; %rejection region for the right-tailed test
fprintf('\nH is %d', H);
if H == 1
    fprintf('\n So the null hypothesis is rejected,\n') 
    fprintf('i.e. the data suggests that the average exceeds 5.5.\n')
else
    fprintf('\n So the null hypothesis is not rejected,\n')
    fprintf('i.e. the data suggests that the average DOES NOT exceed 5.5.\n')
end
fprintf(' the confidence interval for mu is (%4.4f,%4.4f)\n', CI)
fprintf('the rejection region is (%4.4f,%4.4f)\n', RR)
fprintf('the value of the test statistic t is %4.4f\n', stats.tstat)
fprintf('the P-value of the test is %4.4f\n\n', P)










