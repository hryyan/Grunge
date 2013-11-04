function [optTheta, functionVal, exitFlag] = linearRegression_fminunc()
% 使用内置的fminunc
options = optimset('GradObj', 'on', 'MaxIter', 100);
initialTheta = zeros(2, 1)
[optTheta, functionVal, exitFlag] = fminunc(@cost_function, initialTheta, options);
end