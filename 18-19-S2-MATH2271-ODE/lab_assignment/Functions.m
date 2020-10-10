function [ t ] = Functions( i,x,Y )
    u=Y(1); v=Y(2); w=Y(3);
    if i==1
        t= u;
    elseif i==2
        t= 2.*u + v - 2.*w;
    else
        t= 3.*u + 2.*v + w;
    end
end

