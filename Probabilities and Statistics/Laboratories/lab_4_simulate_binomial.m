% Simulate Binomial distr. Bino(n, p) variables
n = input('n (in N) = ');
p = input('p (in (0,1)) = ');

U = rand(n, 1);
X = sum(U < p);

% Generate a sample of such variables

N = input('nr. of simulations = ');

U = rand(1, N);
X = sum(U < p);

%Compare it to Bino(n, p) distribution, graphically

k = 0 : n; % all the values of a binomial distr.

p_k = binopdf(k, n, p); % the probabilities of a binomial distr.
U_X = unique(X); % the values of X listed only once, no repetitions
n_X = hist(X, length(U_X)); % the frequency of each value in U_X 
%(how many times each occurs)
rel_freq = n_X/N;
clf
plot(U_X, n_X/N, '*', k, p_k, 'ro', 'Markersize', 10, 'LineWidth', 2)
legend('simulation', 'Binomial distr')








