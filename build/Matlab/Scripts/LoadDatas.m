clc, clear all, close all

parametros;

%    Heel-Strike(1)   Midstance(2)     Toe-Off(3)     I-Swing(4)   F-Swing(5)                
Jh =[   0.001              0.001          0.01          0.15           0.001];
Bh =[    2.0                1.2           1.2             4            1.5  ];
Kh =[    175                200           130            400           145  ];

Ts=0.002;

in=4;
for in = 4
    
    
    %disp(in)
    sys=modelo_joelho_vel_3E_2A(Bh(in),Jh(in),Kh(in),Bk,Jr,Ks,Nr,Br);
    sysd=c2d(sys, Ts);
    
    %MATRICES FROM NOMINAL MODELS
    F(:,:,in)=sysd.a;
    B(:,:,in)=sysd.b(:,1);  
    B2(:,:,in)=sysd.b(:,2);  
    G(:,:,in)=sysd.b(:,3);
    G2(:,:,in)=sysd.b(:,4);
    
eig(sys);
% disp('controlabilidade do sistema discreto com integrador');
[Abar,Bbar,Cbar,T,kk] =ctrbf(F(:,:,in),[B(:,:,in) B2(:,:,in)] , eye(4));
% obsv
posto_4estados(:,in) = sum(kk);
% 
% disp('controlabilidade do sistema sem integrador');
 posto_3estados(:,in)=rank(ctrb(F(1:3,1:3,in),B(1:3,:,in)));
      
end
 
% B Control
% B2 referencia
% G disturbio


F = F(:,:,in);
B = B(:,:,in);
B2 = B2(:,:,in);
G = G(:,:,in);
G2 = G2(:,:,in);

%Sistema em tempo discreto:
sysd_r=ss(F,[G B],eye(4),0,Ts);
F = sysd_r.a;
G = sysd_r.b;
eig(sysd_r); 
sysc_b = d2c(sysd_r,'tustin');
ExoD = sysd_r;

Exo2 = ss(F(1:2,1:2),[G2(1:2,:) B(1:2,:)],eye(2),0,Ts);
Exo2 = d2c(Exo2,'tustin');

Wmodel = 10*tf(Ks^2,[1 1*Cm Ks^2]);

Wu1 = tf([0.02273 13.64],[1 60000]);
We1 = tf([0.03448 20.69], [1 0.72]);
We2 = tf([0.03448 20.69], [1 0.72]);

Ws1 = tf([0.03448 20.69], [1 0.72]);
Ws2 = tf([0.03448 20.69], [1 0.72]);
Ws3 = tf([0.03448 20.69], [1 0.72]);
Ws4 = tf([0.03448 20.69], [1 0.72]);

Wcmd = tf([1],[.01 000.1 1]);
Wnoise = tf([1],[0.0001 000.1 100]);
Wdist = tf(0.007);

Exo = sysc_b;

AngleW = ExoD.A(3,1:3)/Ks;



















return
clc, clear all, close all
% warning('off','all')
% warning



% cores_graficos;
parametros;

%    Heel-Strike(1)   Midstance(2)     Toe-Off(3)     I-Swing(4)   F-Swing(5)                
Jh =[   0.001              0.001          0.01          0.15           0.001];
Bh =[    2.0                1.2           1.2             4            1.5  ];
Kh =[    175                200           130            400           145  ];


% Jh = Jh+100
Ts=0.002;

% dt T
% T
% Phi K
% Int Error T

in=1;
for in=4:1:4
    
    
    %disp(in)
    sys=modelo_joelho_vel_3E_2A(Bh(in),Jh(in),Kh(in),Bk,Jr,Ks,Nr,Br);
    sysd=c2d(sys, Ts);
    
    %MATRICES FROM NOMINAL MODELS
    F(:,:,in)=sysd.a;
    B(:,:,in)=sysd.b(:,1);  
    B2(:,:,in)=sysd.b(:,2);  
    G(:,:,in)=sysd.b(:,3);
    G2(:,:,in)=sysd.b(:,4);
    
eig(sys);
% disp('controlabilidade do sistema discreto com integrador');
[Abar,Bbar,Cbar,T,kk] =ctrbf(F(:,:,in),[B(:,:,in) B2(:,:,in)] , eye(4));
% obsv
posto_4estados(:,in) = sum(kk);
% 
% disp('controlabilidade do sistema sem integrador');
 posto_3estados(:,in)=rank(ctrb(F(1:3,1:3,in),B(1:3,:,in)));
      
end
 
% B Control
% B2 referencia
% G disturbio


F = F(:,:,4);
B = B(:,:,4);
B2 = B2(:,:,4);
G = G(:,:,4);
G2 = G2(:,:,4);

%Sistema em tempo discreto:
sysd_r=ss(F,[G B],eye(4),0,Ts);

F = sysd_r.a;
G = sysd_r.b;
eig(sysd_r); 
sysc_b = d2c(sysd_r,'tustin');
ExoD = sysd_r;


Wmodel = 10*tf(Ks^2,[1 1*Cm Ks^2]);

Wu1 = tf([0.02273 13.64],[1 60000]);
We1 = tf([0.03448 20.69], [1 0.72]);
We2 = tf([0.03448 20.69], [1 0.72]);

Ws1 = 1*tf([0.03448 20.69], [1 0.72]);
Ws2 = 1*tf([0.03448 20.69], [1 0.72]);
Ws3 = 1*tf([0.03448 20.69], [1 0.72]);
Ws4 = 1*tf([0.03448 20.69], [1 0.72]);

Wcmd = tf(1);
Wnoise = tf(1);
Wdist = tf(0.007);

Exo = sysc_b;



