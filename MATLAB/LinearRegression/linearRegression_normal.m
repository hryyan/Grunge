function [theta] = linearRegression_normal()
% normal������Ч�ʷǳ���
A=load('training_set_one.txt');
B=load('result.txt');
C=[ones(50, 1) A];

theta=pinv(C'*C)*C'*B;
end