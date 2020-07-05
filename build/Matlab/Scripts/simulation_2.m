clc
clear all

load export.mat



f = 2*pi*.9;

sample = 1:(50/Ts);

ref = 20*sin(f*(sample*Ts));

Xs = [sample*0;sample*0];

Kd = c2d(K,Ts);
Exo2d;
K;

Ea = Exo2d.A;
Eb = Exo2d.B;
Ec = Exo2d.c;
Ed = Exo2d.D;

Ka = Kd.A;
Kb = Kd.B;
Kc = Kd.C;
Kd = Kd.D;

KE = series(Kd,Exo2d(:,1));
fb_KE = feedback(KE,eye(2));

A = fb_KE.A;
B = fb_KE.B;
C = fb_KE.C;
D = fb_KE.D;

AngleW = ExoD.A(3,1:3)/Ks;
Angle = sample*0;

Ref = [ref*0;ref];

save exportCpp.mat Ts A B AngleW Ref

for t = sample
    
   Xs(:,t+1) = A*Xs(:,t) + B*[0 ref(t)]';
   Angle(t+1) = AngleW*[Angle(t) Xs(:,t)']';
   
end

plot(Xs')
hold on
plot(ref)

% varName= {'AngleW' , 'A'  , 'B' , 'Ts'};
% Matlab_2_Cpp;
