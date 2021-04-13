%1. Let X have one of the following distributions: X in normal,
% X in student, X in fischer
%a) P(X <= 0) and P(X >= 0)
%b) P(-1 <= X <= 1) and P(X <= -1 or X >= 1)
%c) the value xalpha s.t. P(X < xaplha) = alpha for alpha in (0,1)
% xalpha = the quantile of order alpha
%d) the balue xbeta s.t. P(X > xbeta) = beta for beta in (0,1)
% xbeta = the quantil of order 1 - beta

alpha = input('alpha = ');
beta = input('beta = ');

option = input('Choose option: normal, Student, chi^2, Fischer: \n', 's');
switch option
    case 'normal'
        fprintf('Normal Distribution\n')
        %distribution parameters
        mu = input('mu = ');
        sigma = input('sigma = ');
        
        %a)
        Pa1 = normcdf(0, mu, sigma); %the cdf of F(0)
        Pa2 = 1 - Pa1; %compl. event
        
        %b)
        Pb1 = normcdf(1, mu, sigma) - normcdf(-1, mu, sigma); % F(1) - F(-1)
        Pb2 = 1 - Pb1; %compl. event
        
        %c)
        x_alpha = norminv(alpha, mu, sigma); % quantile of order apha, inverse cdf
        
        %d)
        x_beta = norminv(1 - beta, mu, sigma); %quantile of order 1 - beta
        
    case 'Student'
        fprintf('Student (T) Distribution\n')
        %distribution parameters
        n = input('n = ');
        Pa1 = tcdf(0, n); %the cdf of F(0)
        Pa2 = 1 - Pa1;
        
        Pb1 = tcdf(1, n) - tcdf(-1,n);
        Pb2 = 1 - Pb1;
        
        x_alpha = tinv(alpha, n);
        x_beta = tinv(1 - beta, n);
    case 'chi^2'
        fprintf('Chi squared Distribution')
        
        n = input('n = ');
        
        Pa1 = chi2cdf(0, n);
        Pa2 = 1 - Pa1;
        
        Pb1 = chi2cdf(1, n);
        Pb2 = 1 - Pb1;
        
        x_apha = chi2inv(alpha, n);
        x_beta = chi2inv(1 - beta, n);
        
        
    case 'Fischer'
        fprintf('Fischer Distribution')
        
        m = input('m = ');
        n = input('n = ');
        
        Pa1 = fcdf(0, m, n);
        Pa2 = 1 - Pa1;
        
        Pb1 = fcdf(1, m, n) - fcdf(-1, m, n);
        Pb2 = 1 - Pb1;
        
        x_alpha = finv(alpha, m, n);
        x_beta = finv(1 - beta, m, n);
        
    otherwise 
        fprintf('Wrong option!')
end

fprintf('First probability in part a) is: %1.5f \n', Pa1)
fprintf('Second probability in part a) is: %1.5f \n', Pa2)
fprintf('First probability in part b) is: %1.5f \n', Pb1)
fprintf('Second probability in part b) is: %1.5f \n', Pb2)
fprintf('Answer in part c) x_alpha is: %1.5f \n', x_alpha)
fprintf('Answer in part d) x_beta is: %1.5f \n', x_beta)