%3. Nickel powders are used in coatings used to shield electronic
%equipment. A random sample is selected, and the sizes of nikel particles
%in each coating are recorded (they are assumed to be approximately
%normally distributed):
%a. Find a 95% confidence interval for the average size of nikel particles
%b. At the 1% significance level, on average, do these nickel particles
%seem to be smaller than 3?

clc
x = [3.26, 1.89, 2.42, 2.03, 3.07, 2.95, 1.39, 3.06, 2.46, 3.35, 1.56, 1.79, 1.76, 3.82, 2.42, 2.96];
n = length(x);
m = mean(x);

fprintf('Part a.\n');

alpha = 0.05; %the significance level 1-alpha = 0.95 
%for a population mean m, normal underlying population
q = tinv(1-alpha/2, n - 1);
samp_std = std(x); %standard deviation of the sample
%limits of the confidence interval:
m1 = m - samp_std/sqrt(n)*q;
m2 = m + samp_std/sqrt(n)*q;

fprintf('The confidence interval for the mean (sigma unknown) is (%6.4f, %6.4f)\n', m1, m2);

%part b
fprintf('\n\nPart b.\n');

alpha = 0.01; % 1% significance level

%H0: mu = 3 
%H1: mu < 3 so it is a left tailed test RR = (-inf, ttalpha)
%for a population mean, sigma unknown

[H,P,CI, stats]= ttest(x, 3, "alpha", alpha, "tail", "left");
t1 = tinv(alpha, n - 1); %quantile for left tailed test
RR = [-inf, t1]; %rejection region for left tailed test
if H == 0
   fprintf('H is %d\n', H);
   fprintf('So the null hypothesis is rejected,\nthe data suggests that the average does exceed 3\n');
else
    fprintf('H is %d\n', H);
    fprintf('So the null hypothesis is not rejected,\nthe data suggests that the average does not exceed 3\n');
end

fprintf('The confidence interval for mu is (%6.4f, %6.4f)\n', CI);
fprintf('The rejection region is (%4.4f, %4.4f)\n', RR);
fprintf('The value of the test statistic t is %4.4f\n', stats.tstat);
fprintf('The P-value of the test is %4.4f\n\n', P);



