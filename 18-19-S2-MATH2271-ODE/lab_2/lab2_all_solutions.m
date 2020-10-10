%% lab 2 solutions 

clear; clc;

%% 1.1.2: single first order ODEs, underestimate

a = 0;
b = 0.75;
N = 501;
y0 = 2;
h = 0.1

[x,y]=EulerFirst(a,b,h,y0,'f'); % 4 points is an underestimate: concave up imples underestimate
xlabel('x')
ylabel('y')
title('A plot of the numerical solution of y versus x')
hold on;

[x,y]=EulerFirst(a,b,h,y0,'f'); % more points = actual
legend('underestimate', 'actual')

%% 1.1.3: single first order ODEs, overestimate

clear; clc;

[x,y]=Euler(0, 2, 4, 1,'g'); % accurate % over estimating (concave down) with 4 points
xlabel('x')
ylabel('y')
title('A plot of the numerical solution of y versus x')
hold on;

[x,y]=Euler(0, 2, 1001, 1,'g'); % accurate

%% 2.1.2: a system of two coupled 1st order ODEs

clear; clc;

a = 1;
b = 5;
h = 0.001;
u0 = 2;
v0 = 2;
[x,u,v] = Euler2(a,b,h,u0,v0,'f1','g1');
xlabel('x')
legend('u', 'v')
title('A plot of the numerical solutions of u and v versus x')


%% 3.1.2: 2nd order ODEs

clear; clc;

[x,y] = Euler3(0, 2*pi, 0.001, -6, 0, 'h');
xlabel('x')
ylabel('y')
title('A plot of the numerical solution of y versus x')

%% built in ode solvers: https://blogs.mathworks.com/cleve/2014/05/26/ordinary-differential-equation-solvers-ode23-and-ode45/#bb31cd19-1926-421d-9888-4ff43f510746

% redoing solution to 1.1.2

clear; clc;

[x1,y1]=ode23('f',[0 0.75],2); % faster, less accurate
[x2,y2]=ode45('f',[0 0.75],2); % slower, more accurate
plot(x1,y1,x2,y2)
legend('ode23 solution', 'ode45 solution')

