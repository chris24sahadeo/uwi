[x,y]=Euler(0, 2, 4, 1, 'g');
figure(3)
plot(x,y,'gx-')
hold on
[x,y]=Euler(0, 2, 1001, 1, 'g');
plot(x,y,'r-.')
xlabel('x')
ylabel('y')
title('Plot to show the Overestimation')
legend('4 points','1001 points')