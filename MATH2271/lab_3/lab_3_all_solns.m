%% 1.1.2 Solving a general system of coupled 1st order ODEs using Euler Method

clear; clc;

[x,Y] = Eulersys(0, 2, 0.001, [2;1;1], 'F');
xlabel('x')
legend('u', 'v', 'w')


%% 2  Solving 1st order ODEs using MATLABS built-in solvers

clear; clc;

[x1,y1]=ode23('f_1',[0 2],1);
[x2,y2]=ode45('f_1',[0 2],1);
plot(x1,y1,x2,y2)
legend('ode23 solution', 'ode45 solution')


%% 3 PPLANE and DFIELD

% just type >>pplane8 and >>dfield9 into the command window
