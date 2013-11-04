function [jVal, gradient] = cost_function(theta)
% 单值线性回归
A = load('training_set_one.txt');
B = load('result.txt');
C = [ones(50, 1) A]';
m = size(A, 1);

delta = theta'* C - B';
jVal = sum(delta.^2);

gradient(1) = sum(delta)/m;
gradient(2) = sum(delta * A)/m;

end