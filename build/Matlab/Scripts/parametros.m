
Bk = 0.5*1;

%Parâmetros fixos do robô:
Cm = 0.00287; % Nms/rad
Nr  = 150;
Br = 60;      % Nms/rad
Jr = 0.47;    % Kgm2;
Ks = 100;     % Nm/rad

% Controle de Força PID:
Kp = 300;
Ki = 35;
Kd = 3.5;

BR= (Br/Nr) + Nr*Cm;
disp('P')