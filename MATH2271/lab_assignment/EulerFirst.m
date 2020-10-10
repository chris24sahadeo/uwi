function [x,y]=EulerFirst(a,l,h,y0,f)
    
%     MATLAB code for using Euler's MEthod to solve the general 1st order IVP
%     dy/dx = f(x, y) on the interval (a, a+l) with y(a) = y0
%     
%     Inputs:     a and l define the interval [a, a+l]
%                 h is the interval step
%                 y0 is the value of y(a)
%                 f is the function f(x,y) which must be defined separately
%     
%     Outputs:    x stores the discretized values of x in the interval [a, a+l]
%                 y stores the corresponding approximate values of the solution

    x=a:h:(a+l);
    N = length(x);
    y=zeros(1,N);
    y(1)=y0;
    for i=1:N-1
        y(i+1)=y(i)+h*feval(f,x(i),y(i));
    end
    
end