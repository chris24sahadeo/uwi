[x,y]=Euler(0, 0.75, 4, 2, 'f');
figure(2)
plot(x,y,'gx-')
hold on
[x,y]=Euler(0, 0.75, 501, 2, 'f');
plot(x,y,'r-.')
hold on
plot(x,2*exp(x)-x,'b-')
xlabel('x')
ylabel('y')
title('Plot to show the Underestimation')
legend('4 points','401 points','exact')