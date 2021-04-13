% Plot the graphs of the pdf and the cdf of a random variable X having a
% binomial distribution of parameters n and p (given by the user)
%clf
%n = input('Nr. of trials n = ');
%p = input('Probability of success p = ');
%x = 0 : n; % nr. of successes, s-values for pdf
%px = binopdf(x,n,p); % the pdf
%plot(x, px, 'r+');
%hold on
%xx = 0 : 0.01 : n; %simulation of continuity, x-values for cdf
%fx = binocdf(xx, n, p); %the cdf
%plot(xx, fx, 'm')
%legend('pdf', 'cdf')


% APPLICATION

% A coin is tossed 3 times. Let X denote the number of heads that appear.

%a) Find the probability distribution function of X. What type of
%distribution X have?
%b Find the cumulative distribution function of X, FX.
%c)Find P(X=0) and P(X != 1)
%d)Find P(X >= 1) and P(X > 1)

%a) Binomial distribution with parameters 3 and 1/2, B(3,0.5). 
%PDF : (0   1   2   3)
%      (1/8 3/8 3/8 1/8)

%fprintf('a) PDF = %d', binopdf(0:3,3,1/2));

%c) P(X = 0) is the value nof the pdf at 0, by definition.
p1 = binopdf(0,3,1/2);
p2 = 1 - binopdf(1,3,1/2); %prob of the complementary event
fprintf('P(X = 0) = %1.6f\n', p1);
fprintf('P(X != 1) = %1.6f\n', p2);

%d)P(X <= 2) is the value of the cdf F(2), by definition
p3 = binocdf(2,3,1/2);
%P(X < 2) = P(X =< 1) or P(X=< 1.5) or any number in the interval [1,2) 
p4 = binocdf(1,3,1/2);
fprintf('P(X <= 2) = %1.6f\n', p3);
fprintf('P(X < 2) = %1.6f\n', p4);

%e) prob of the complementary event d)
p5 = 1-binocdf(0, 3, 1/2);
p6 = 1-binocdf(1,3,1/2);
fprintf('P(X >= 1) = %1.6f\n', p5);
fprintf('P(X > 1) = %1.6f\n', p6);








