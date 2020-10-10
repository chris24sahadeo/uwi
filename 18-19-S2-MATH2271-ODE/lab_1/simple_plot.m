x = -3:0.1:3;
y = zeros(length(x));
for i = 1:length(x)
    if x(i) > -1 & x (i) < 1
        y(i) = x(i)^2+1;
    else
        y(i) = 2;
    end
end

plot(x, y, 'm')
