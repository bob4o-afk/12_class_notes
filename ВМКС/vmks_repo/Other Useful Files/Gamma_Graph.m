clc;
clear all;
close all;

L = 0:1:100;
Gamma = 2.2;
B = L.^(1./Gamma);
Bmax = 100.^(1./Gamma);
B = B.*(100./Bmax);

plot(L,B);
ylabel({'Perceived Brightness [%]'});
xlabel({'Light Intensity [%]'});
title({'Perceived Brightness vs Light Intensity'});