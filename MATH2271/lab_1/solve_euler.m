x = linspace(0, 0.75, 3+1);
y_exact = 2*exp(x) - x;
[x, y_pred] = Euler(0, 0.75, 3, 2, derivative1);

plot(x, y_exact, 'c')
hold on;
plot(x, y_pred, 'm')
legend

