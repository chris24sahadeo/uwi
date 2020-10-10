[x1,y1]=ode23('f',[0 0.75],2);
[x2,y2]=ode45('f',[0 0.75],2);
plot(x1,y1,x2,y2)
legend('ode23 solution', 'ode45 solution')