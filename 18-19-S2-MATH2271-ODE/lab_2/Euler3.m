function [x,y] = Euler3(a, b, h, y0, u0, f)
    % A second order IVP can be solved by first converting it to a system of 2 first order ODEs
    % substitution with u = dy/dx
    
    %f here is a first order ode
    x=a:h:b;
    N=length(x);
    y=zeros(1,N); % y is the solution to the first order ode
    u=zeros(1,N);
    y(1)=y0;
    u(1)=u0; % the initial value of the second order ode f
    
for i=1:N-1
    y(i+1)=y(i)+h*u(i); % finding the solution points of 1st order ode
    u(i+1)=u(i)+h*feval(f,x(i),y(i),u(i)); % f is the function 'h': getting the value of the second order ode by Euler's
end
plot(x,y)