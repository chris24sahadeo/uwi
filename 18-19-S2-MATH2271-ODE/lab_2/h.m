function [ t ] = h( x,y,u )
    % t is the vector of second order ode solution points, 
    % u is the first order ode solutions
    t=u-y+x.^3;
end
