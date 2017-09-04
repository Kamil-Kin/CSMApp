fileIDr = fopen('hist_rownomierny.txt','r');
R = fscanf(fileIDr,'%f');
nbins = 100;

figure(1)
hist(R,nbins);
grid on;
title('Histogram rozk�adu r�wnomiernego');
xlabel('Losowane liczby');
ylabel('Ilo�� wylosowanych liczb');

fclose(fileIDr);

fileIDw = fopen('hist_wykladniczy.txt','r');
W = fscanf(fileIDw,'%f');
nbins = 100;

figure(2)
hist(W,nbins);
grid on;
title('Histogram rozk�adu wyk�adniczego');
xlabel('Losowane liczby');
ylabel('Ilo�� wylosowanych liczb');
fclose(fileIDw);


