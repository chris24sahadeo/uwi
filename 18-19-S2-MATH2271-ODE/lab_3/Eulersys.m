function [x,Y] = EulerSys(a, b, h, Y0, F)
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
    for i=1:M
        plot(x,Y(i,:))
        hold on
    end
    legend('u','v','w')
    hold off
end