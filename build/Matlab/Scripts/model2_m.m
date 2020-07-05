LoadDatas;

Exo2d = ss(F(1:2,1:2),[G2(1:2,:) B(1:2,:)],eye(2),0,Ts);
Exo2 = d2c(Exo2d,'tustin');

We1 = tf([0.03448 20.69], [1 0.72]);
Wcmd = Wcmd*1.7;
Wnoise = Wnoise;

nameModel = 'model2';
load_system('model2')
set_param('model2/Wcmd','Numerator','[Wcmd.num{:}]');
set_param('model2/Wcmd','Denominator','[Wcmd.den{:}]');
set_param('model2/Wnoise','Numerator','[Wnoise.num{:}]');
set_param('model2/Wnoise','Denominator','[Wnoise.den{:}]');
set_param('model2/We','Numerator','[We1.num{:}]');
set_param('model2/We','Denominator','[We1.den{:}]');
set_param('model2/We2','Numerator','[We1.num{:}]');
set_param('model2/We2','Denominator','[We1.den{:}]');
set_param('model2/Angle/KAngle','Value','AngleW');
disp('Configurado ...')
%%
disp('Calculando Hinf')
ST0 = slTuner('model2',{'C1','C2'});

T0 = getIOTransfer(ST0,{'r','n'},{'y','Z6','Z7'});

opt = hinfstructOptions('RandomStart',5);%'Display','final',
T = hinfstruct(T0,opt);

C1 = getBlockValue(T,'C1');
C2 = getBlockValue(T,'C2');


load_system('model2')
set_param('model2/K/C1','P',num2str(C1.kp));set_param('model2/K/C1','I',num2str(C1.ki));set_param('model2/K/C1','D',num2str(C1.kd));
set_param('model2/K/C2','P',num2str(C2.kp));set_param('model2/K/C2','I',num2str(C2.ki));set_param('model2/K/C2','D',num2str(C2.kd));


K = ss([C1 C2 ]);
save export.mat Ts Exo2d K Ts ExoD Ks
