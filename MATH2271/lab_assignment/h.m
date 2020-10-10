function [ x ] = h( t,y,u )
    % t is the vector of second order ode solution points, 
    % u is the first order ode solutions
    x= -4.*y + t.^2 + 3.*exp(t);
end
