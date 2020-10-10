function [ t ] = F( i,x,Y )
% MATLAB code for the vector function defining the LHS of the system
%   dY/dX=F(x,Y)

% Inputs:   i defines the row number
%           x is an x value
%           Y is a column vector of values of the dependent variables


u=Y(1); v=Y(2); w=Y(3);
if i==1
    t=v-x;
elseif i==2
    t=u;
else
    t=u-v+x;
end
end
