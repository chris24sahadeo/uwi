function [x,y]=Euler(a,b,N,y0,f)
        h=(b-a)/(N-1);
        x=linspace(a,b,N);
        y=zeros(1,N);
        y(1)=y0;
        for i=1:N-1
            y(i+1)=y(i)+h*feval(f,x(i),y(i));
        end
        plot(x,y)
end