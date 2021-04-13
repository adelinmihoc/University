%f) Simulating 3 coin tosses.

N = input('Number of simulations: ');

%Try different number simulations, 10, 50, 100, 1e4, 1e5, 1e6, you will
%notice that the larger the N is, the more shape will resemble the
%binomial(3, 1/2) distribution

U = rand(3, N); % a 3 x N matrix of random numbers form [0, 1], simulating
% the 3 coin tosses

Y = (U < 1/2); % Y = 1(heads) if U < 1/2, otherwise Y = 0(tails)

X = sum(Y); % sum across columns of Y, i.e. X = number of heads in 3 tosses

clf
histogram(X);
