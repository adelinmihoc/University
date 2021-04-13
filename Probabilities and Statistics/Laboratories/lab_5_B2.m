% 5.B.2. It is thought that the gas mileage obtained by a particular model
% of automobile will be heigher if unleaded premium gasoline is used in the
% vehicle rather than regulare unleaded gasoline. To ghater evidence in
% this matter, 10 cars are randomly selected from the assembly line and
% tested using specified breand premium gasoline; 10 other are randmoly
% selected and tested using the brand's regular gasoline. Tests are
% conducted under identical controlld conditions and gas mileages for both
% types of gas are assumed independent and (appromiately) normally
% distributed. Theses data results: *some data*
% a) Assuming sigma1 = sigma2, find a 100(1 - alpha)% confidence interval
% for the difference of the true means.
% b) Assuming sigma1 != sigma 2, find a 100(1 - aplha)% confidence interval
% for the differences of the tru means.
% c) Find a 100(1 - alpha)% confiedence interval for the ration of the
% variances.

x1 = [20, 21.6 * ones(1, 2), 21.7, 22.4 * ones(1,2), 23.3,...
      23.4, 24.5, 24.8];
x2 = [12.1, 12.2, 12.6, 14, 14.8 * ones(1, 2), 15.4, 17.7,...
      19.6 * ones(1, 2)];
  
n1 = length(x1);
n2 = length(x2);
oneminusalpha = input('conf. level = ');
alpha = 1 - oneminusalpha;

xm1 = mean(x1);
xm2 = mean(x2);
mdiff = xm1 - xm2;
v1 = var(x1);
v2 = var(x2);
vratio = v1/v2;

%part a
sp = sqrt( ( (n1-1)*v1+(n2-1)*v2 ) / (n1+n2-2) );
n = n1 + n2 - 2;
q = tinv(1 - alpha/2, n);
m1 = mdiff - q * sp * sqrt(1/n1 + 1/n2);
m2 = mdiff + q * sp * sqrt(1/n1 + 1/n2);
fprintf('a) conf. int. for diff. of means = (m1, m2) = (%4.3f, %4.3f)\n', m1, m2);


%part b
c = (v1 / n1)/(v1 / n1 + v2/n2);
nn = 1/(c^2/(n1 - 1) + (1 - c)^2/(n2-1));
s = sqrt(v1/n1 + v2/n2);
qq = tinv(1 - alpha/2, nn);
mm1 = mdiff - qq * s;
mm2 = mdiff + qq * s;
fprintf('b) conf. int. for diff. of means, variances not equal, (mm1, mm2) = (%4.3f, %4.3f)\n', mm1, mm2);


%part c

f1 = finv(1- alpha/2, n1 - 1, n2 - 1);
f2 = finv(alpha/2, n1 - 1, n2 - 1);
vv1 = vratio/f1;
vv2 = vratio/f2;
s1 = sqrt(vv1);
s2 = sqrt(vv2);

fprintf('c) conf. int. for ratio of variances (vv1, vv2) = (%4.3f, %4.3f)\n', vv1, vv2);
fprintf('c) conf. int. for ratio of std. dev (s1, s2) = (%4.3f, %4.3f)\n',s1, s2);














