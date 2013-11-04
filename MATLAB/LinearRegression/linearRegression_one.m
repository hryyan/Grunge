function [theta] = linearRegression_one()
% Ó²Ëã
A=load('training_set_one.txt');
B=load('result.txt');
C=[ones(50, 1) A]';

theta=zeros(2, 1);
trainfact=0.00001;
newVal=0;
oldVal=sum(B.^2)/100;

while abs((newVal-oldVal)/oldVal)>0.00001
    oldVal=newVal;
    newVal=0;
    delta=zeros(2, 1);
    for x=1:1:50
        delta=delta+(theta'*C(:,x)-B(x))*C(:,x);
        newVal=newVal+(theta'*C(:,x)-B(x))^2;
    end
    newVal=newVal/100;
    theta=theta-trainfact*delta/50;
end
end