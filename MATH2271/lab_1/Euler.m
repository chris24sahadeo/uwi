function [x, y] = Euler(a, b, N, y0, f)

h = (b-a)/N;
x = linspace(a, b, N+1);
y = zeros(N+1);
y(1) = y0;

for i = 1:N
    y(i+1) = y(i) + h*feval(f, x(i), y(i));
end

end

