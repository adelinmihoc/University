clc

%1=========================================================================
x = [7,7,4,5,9,9,4,12,8,1,8,7,3,13,2,1,17,7,12,5,6,2,1,13,14,10,2,4,9,11,3,5,12,6,10,7];
n = length(x);
%part a.-------------------------------------------------------------------
% sigma known = 5, 5% significance level

sigma = 5;
alpha = 0.05;

% the null hypothesis H0: mu = 9
% the alt. hypothesis H1: mu < 9. This is a left-tailed test
% sigma known 

[H, P, CI, stats] = ztest(x, 9, sigma, "alpha", alpha, "tail", "left");

z1 = norminv(alpha);
RR = [-inf, z1];

fprintf('Part a.\n');

if H == 1
   fprintf('H is %d\nSo the null hypothesis is rejected\n the data suggests that the standard is not met.\n', H);
else
   fprintf('H is %d\nSo the null hypothesis is not rejected\n the data suggests that the standard is met.\n', H);
end

fprintf('The conf. int. for mu is (%6.4f, %6.4f)\n', CI);
fprintf('The rejection region is (%6.4f, %6.4f)\n', RR);
fprintf('The value of the test statistic z is %6.4f\n', stats);
fprintf('The P-value of the test is %6.4f\n\n', P);


%part b.-------------------------------------------------------------------
%sigma unknown

% the null hypothesis H0: mu = 5.5
% the alt. hypothesis H1: mu > 5.5. This is a right-tailed test

t1 = tinv(1-alpha, n-1);

[H, P, CI, stats] = ttest(x, 5.5, "alpha", alpha, "tail", "right");
RR = [t1, inf];

fprintf('\nPart b.\n');

if H == 1
   fprintf('H is 1 so the null hypothesis is rejected\n the data suggest that the average exceeds 5.5\n');
else
   fprintf('H is 0 so the null hypothesis is not rejected\n the data suggest that the average does not exceed 5.5\n');
end

fprintf('The conf. int. for mu is (%6.4f, %6.4f)\n', CI);
fprintf('The rejection region is (%6.4f, %6.4f)\n', RR);
fprintf('The value of the test statistic z is %6.4f\n', stats.tstat);
fprintf('The P-value of the test is %6.4f\n\n', P);


clc

%2.========================================================================
x1 = [20, 21.6 * ones(1, 2), 21.7, 22.4 * ones(1, 2), 23.3,...
      23.4, 24.5, 24.8];
x2 = [12.1, 12.2, 12.6, 14, 14.8 * ones(1, 2), 15.4, 17.7,...
      19.6 * ones(1, 2)];

n1 = length(x1); n2 = length(x2);
alpha = 0.05;
m1 = mean(x1); m2 = mean(x2);
v1 = var(x1); v2 = var(x2); 


f1 = finv(alpha/2, n1-1, n2-1);
f2 = finv(1-alpha/2, n1-1, n2-1);

%part a
% the null hypothesis H0: sigma1^2 = sigma2^2
% the alt. hypothesis H1: sigma1^2 != sigma2^2
%two tailes test for comparing the variances

[H, P, CI, stats] = vartest2(x1, x2, "alpha", alpha);

fprintf('\n part a. Comparing variances');
fprintf('Two tailed test for comparing variances\n');

if H == 0
    fprintf('H is 0 so the null hypothesis is not reected\n the variances seem to be equal\n');
    fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
    fprintf('The value of the test statistic F is %6.4f\n', stats.fstat);
    fprintf('The P-value for the variances test is %6.4f\n', P);
    
    %part b
    %the null hypothesis H0: mu1 = mu2
    %the alt. hypothesis H1: mu1 > mu2
    %Right tailed test for the difference of the means
    
    n = n1 + n2 - 2;
    
    t2 = tinv(1 - alpha, n);
    [hh, pp1, ci2, stats] = ttest2(x1, x2, "alpha", alpha, "tail", "right");
    fprintf('\n Part b. Comparing means when variances are equal\n');
    fprintf('Right tailed test for the difference of the means\n');
    fprintf('hh is %d', hh);
    if hh == 1
        fprintf('So the null hypothesis is rejected\n gas mileage is higher with premium gasoline\n');
    else
        fprintf('So the null hypothesis is not rejected\n gas mileage is not higher with premium gasoline\n');
    end
    
    fprintf('The rejection region for T is (%6.4f, %6.4f)\n', t2, inf);
    fprintf('The value of the test statistic T is %6.4f\n', stats.tstat);
    fprintf('The P-value of the test for diff. of means is %4\n', pp1);
    
else
    fprintf('h is %d\n', h);
    fprintf('So the null hypothesis is rejected\n the variances seem to be different\n');
    fprintf('The rejection region for F is (%6.4f, %6.4f) U (%6.4f, %6.4f)\n', -inf, f1, f2, inf);
    fprintf('The value of the test statistic F is %6.4f\n', stats.fstat);
    fprintf('The P-value for the variances test is %6.4f\n', p);
    
    %part b
    %the null hypothesis H0: mu1 = mu2
    %the alt. hypothesis H1: mu > mu2
    %right tailed test for the difference of the means
    c = (v1/n1)/(v1/n1 + v2/n2);
    n = (c^2)/(n1-1) + (1-c)^2/(n2-1);
    n = 1/n;
    t2 = tinv(1-alpha, n); %quantile for right tailed test for rejection region
    [hh, pp2, ci2, stats]= ttest2(x1, x2, alpha, 1, 'unequal');
    fprintf('\nPart b. Comparing means when variances are not eula\n');
    fprintf('Right tailed test for the difference of means\n');
    fprintf('hh is %d\n', hh);
    if hh == 1
       fprintf('So the null hypothesis is rejected,\n gas mileage is higher with premium gasolin\n');
    else
        fprintf('So the null hypothesis is not rejected\n has mileage is not higher with premium gasline\n');
    end
    
    fprintf('The rejection region for T is (%6.4f, %6.4f)\n', t2, inf);
    fprintf('The value for the test statistic T is %6.4f\n', stats.tstat);
    fprintf('The P-value of the test for diff of means is %e\n', pp2); 
end









