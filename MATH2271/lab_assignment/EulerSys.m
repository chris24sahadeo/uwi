function [x,Y] = EulerSys(a, b, h, Y0, F)
    
%     Using Euler's Method to solve a general system of 1st order ODEs
%     dY/dx = F(x,Y) on the interval (a,b)
%     
%     Inputs:     a and b define the interval(a,b)
%                 h is the step size
%                 Y0 is a column vector that defines the initial conditions
%                 F is a function that doves the LHS of the system dY/dx = F(x,Y)
%                
%     Outputs:    x stores the discretised values of x in the interval (a,b)
%                 Y is a vector that stores the corresponding approximate values 

    x=a:h:b;
    N=length(x);
    M=length(Y0);
    Y=zeros(M,N);
    Y(:,1)=Y0;
    for j=1:N-1
        for i=1:M
            Y(i,j+1)=Y(i,j)+h*feval(F,i,x(j),Y(:,j));
        end
    end
    
%     plotting
    clf;
    for i=1:M
        plot(x,Y(i,:))
        hold on
    end
    title('A plot of the numerical solution of u, v and w vs x');
    xlabel('x');
    ylabel('y');
    legend('u','v','w');
    hold off
end