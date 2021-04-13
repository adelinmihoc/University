% B.1. In a study of the size of various computer systems, the random
% variable X, the number of files stored (in hundreds of thousands), is
% considered. These data are obtained: *some data*
% a) Assuming that past experience indicates that sigma=5, find a
%   100(1-alpha)% confidance interval for the average number of files
%   strored.
% b) Assuming nothing is known about sigma, find a 100(1 - aplha)% 
%    confidance interval for the average number of files stored.
% c) Assuming the number of files stored are approximately normally
% distributed, find 100(1 - aplha)% confidance interval for the variance 
% and for the standard diviation.

clc

x = [7, 7, 4, 5, 9, 9, 4, 12, 8, 1, 8, 7, 3, 13, 2, 1, 17, 7,...
   12, 5, 6, 2, 1, 13, 14, 10, 2, 4, 9, 11, 3, 5, 12, 6, 10, 7];


% sample size
n = length(x);
% confidance level
oneminusalpha = input('conf. level = ');
% significance level
alpha = 1 - oneminusalpha;
% population standard deviation
sigma = 5;
% sample mean
samp_m = mean(x);
fprintf('\nProblema 1.\n');

%a) Sigma known
m1 = mean(x) + norminv(alpha/2) * sigma/sqrt(n); 
m2 = mean(x) - norminv(alpha/2) * sigma/sqrt(n); 

fprintf('a) the confidence interval for the mean (sigma known) is: (m1, m2) = (%4.3f, %4.3f)\n', m1, m2);


%b) Sigma not known
samp_std = std(x); % we use the sample std.dev.

% limits of the confidence interval
m1b = mean(x) + tinv(alpha/2, n-1) * samp_std/sqrt(n);
m2b = mean(x) - tinv(alpha/2, n-1) * samp_std/sqrt(n);

fprintf('b) the confidence interval for the mean (sigma unkown) is: (m1b, m2b) = (%4.3f, %4.3f)\n', m1b, m2b);

%c) normally distr. Find conf. int. for variance and std. dev.
v = var(x);
q1 = chi2inv(1 - alpha/2, n-1);
q2 = chi2inv(alpha/2, n-1); % here we need both quantiles, there is no more symmetry

v1 = (n-1) * v/q1;
v2 = (n-1) * v/q2;

s1 = sqrt(v1);
s2 = sqrt(v2);

fprintf('c) conf. interval for variance (v1, v2) = (%4.3f, %4.3f)\n', v1, v2);
fprintf('d) conf. interval for std. dev. (s1, s2) = (%4.3f, %3.3f)\n', s1, s2);




