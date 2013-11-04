function [jVal, gradient] = cost_function_two(theta)
% 双值的线性回归
A = load('training_set.txt');
B = load('result.txt');
C = [ones(50, 1) A]';
m = size(A, 1);

delta = theta'* C - B';
jVal = sum(delta.^2);

gradient(1) = sum(delta)/m;
gradient(2) = sum(delta * C(2,:)')/m;
gradient(3) = sum(delta * C(3,:)')/m;

end