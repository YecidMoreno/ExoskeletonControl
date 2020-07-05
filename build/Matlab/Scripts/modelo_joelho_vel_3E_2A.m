function sys=modelo_joelho_vel_3E_2A(Bh,Bk,Jh,Jr,Kh,Ks,Nr,BR)

%Parâmetros:

parametros;

%
a11 = -(Bh+Bk)/(Jh+Jr);
a12 = -((Kh/(Jh+Jr)) + (Ks/Jr) - (Ks/(Jh+Jr)));
%a13 =  1/Jh;
a31 = -1/Ks;%-1/Ks

b11 = Ks*(((Nr*Cm - Nr^(-1)*Br)/(Jr)) +((Bk+Bh)/((Jr+Jh)*Nr)));
b31 = 1/Nr;%1/Nr






g11 = (Kh*Ks/Jh+Jr);
g21 =(Ks/(Jh+Jr));


A = [a11 a12 0;
       1   0   0;
     a31   0   0];
 
B =  [ b11   0  b31]';

Ga =  [g11   0    0]';

%Gb=[g11  0  0 ]';

Gb=[g21  0  0 ]';


C = eye(3);

% C =  [ 0   1    0;
%        0   0    1];

D = 0;

%D =  [ 0   0];



Aaa=[A zeros(3,1); [0 -1 0 ] 0];
Baa=[B;0];
Gaa=[Ga;0];
Gbb=[Gb;0];
Caa=eye(4);


%--------------------------------------------------------------------------

sys = ss(Aaa,[Baa  [0 0 0  1]' Gaa Gbb],Caa,D);





