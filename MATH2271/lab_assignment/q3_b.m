syms x(t) y(t) z(t)
A = [1 0 0; 2 1 -2; 3 2 1];
B = [0;0;0];
Y = [x;y;z];
odes = diff(Y) == A*Y + B;

C = Y(0) == [1;1;2];
[xSol(t), ySol(t), zSol(t)] = dsolve(odes, C)

clf
fplot(ySol)
hold on
fplot(xSol)
hold on
fplot(zSol)
grid on
legend('ySol','xSol','zSol','Location','best')
axis([0 2 -25 10]);
hold off