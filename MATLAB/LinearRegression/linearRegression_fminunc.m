function [optTheta, functionVal, exitFlag] = linearRegression_fminunc()
% ʹ�����õ�fminunc
options = optimset('GradObj', 'on', 'MaxIter', 100);
initialTheta = zeros(2, 1)
[optTheta, functionVal, exitFlag] = fminunc(@cost_function, initialTheta, options);
end