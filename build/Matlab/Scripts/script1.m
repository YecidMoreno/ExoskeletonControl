clc

Res = out.simout.Data';

out_e_angle = (Res(3,:) - Res(4,:));

res1 = Res(1,:) - 50*out_e_angle;

res2 = rms(res1)/rms(out_e_angle )

