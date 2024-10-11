clc;
clear all;
close all;

% Mono
% L=B^(gamma)
% B=L^(1/gamma)

% Color
% L=Red^gamma+Green^gamma+Blue^gamma
% B=(Red^gamma+Green^gamma+Blue^gamma)^(1/gamma)

%% Plot Perceived Brightness and Hue
% of Red-Yellow-Green LED Fade
% with gamma correction on each R,G,B channel
% Gamma correction can be made also as RGB LUT instead of individual
% channel

L = 0:1:100;
L_inv = 100-(0:1:100);
Gamma = 2.2;

Red = L_inv.^(1./Gamma);
Green = L.^(1./Gamma);
Blue = zeros(1,101);

RGB_L = (Red.^Gamma)+(Green.^Gamma)+(Blue.^Gamma);
B = RGB_L.^(1./Gamma);
hue = atand((sqrt(3).*(Green-Blue))./(2.*Red-Green-Blue));
hue = mod(hue,180);

Bmax = max(B);
B = B.*(100./Bmax);

figure % new figure
[hAx,hLine1,hLine2] = plotyy(L,B,L,hue);
ylim([0 200]);

ylabel(hAx(1),'Perceived Brightness [%]');
ylabel(hAx(2),'Hue [°]');
xlabel({'Light Intensity [%]'});
title({'Perceived Brightness vs Light Intensity'});