h = [0.1 0.01 0.001];
figure;
title('A plot of the numerical solution of y versus x');
xlabel('x');
ylabel('y');
hold on;

for i = 1:length(h)
    [x, y] = EulerFirst(0, 0.5, h(i), 1, 'f');
    plot(x, y)
    legendInfo{i} = ['h = ', num2str(h(i))];
end
legend(legendInfo)

% legend('h = ')