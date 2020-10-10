function [ t ] = F( i,x,Y )
    u=Y(1); v=Y(2); w=Y(3);
    if i==1
        t=v-x;
    elseif i==2
        t=u;
    else
        t=u-v+x;
    end
end