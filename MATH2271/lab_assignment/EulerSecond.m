function [x,y] = EulerSecond(a, l, h, y0, u0, f)
%     A second order IVP can be solved by first converting it to a system of 2 first order ODEs
%     substitution with u = dy/dx
    
%     Inputs:     a and l define the interval [a, a+l]
%                 h is the step size
%                 y0, u0 are the values of y(a) and dy/dx(a)
%                 f is the function f(x,y,dy/dx), defined in another file
%                 
%      Outputs:   x stores the discretized values of x in the interval [a, a+l]
%                 y stores the corresponding approximate values of y
    
    %f here is a first order ode
    x=a:h:(a+l);
    N=length(x);
    y=zeros(1,N); % y is the solution to the first order ode
    u=zeros(1,N);
    y(1)=y0;
    u(1)=u0; % the initial value of the second order ode f
    
    for i=1:N-1
        y(i+1)=y(i)+h*u(i); % finding the solution points of the first ODE 
        u(i+1)=u(i)+h*feval(f,x(i),y(i),u(i)); % f is the function 'h': getting the value of the second ODE by Euler's
    end

    figure;
    hold on;
    title('A plot of the numerical solution of y versus x');
    xlabel('x');
    ylabel('y');
    plot(x,y)

end