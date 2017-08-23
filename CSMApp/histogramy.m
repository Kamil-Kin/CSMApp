fileIDr = fopen('hist_rownomierny.txt','r');
[R,size] = fscanf(fileIDr,'%f');
nbins = 100;
figure(1)
title('Histogram rozk³adu równomiernego');
xlabel('Losowane liczby');
ylabel('Iloœæ wylosowanych liczb');
hist(R,nbins);
fclose(fileIDr);

fileIDw = fopen('hist_wykladniczy.txt','r');
[W,size] = fscanf(fileIDw,'%f');
nbins = 100;
figure(2)
title('Histogram rozk³adu wyk³adniczego');
xlabel('Losowane liczby');
ylabel('Iloœæ wylosowanych liczb');
hist(W,nbins);
fclose(fileIDw);


