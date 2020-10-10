function [x,u,v] = Euler2(a,b,h,u0,v0,f,g)
    x=a:h:b;
    N=length(x);
    u=zeros(1,N);
    v=zeros(1,N);
    u(1)=u0; v(1)=v0;
for i=1:N-1
    u(i+1)=u(i)+h*feval(f,x(i),u(i),v(i));
    v(i+1)=v(i)+h*feval(g,x(i),u(i),v(i));
end
    plot(x,u,x,v)
end
