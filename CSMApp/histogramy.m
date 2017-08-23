fileIDr = fopen('hist_rownomierny.txt','r');
[R,size] = fscanf(fileIDr,'%f');
nbins = 100;
figure(1)
title('Histogram rozk�adu r�wnomiernego');
xlabel('Losowane liczby');
ylabel('Ilo�� wylosowanych liczb');
hist(R,nbins);
fclose(fileIDr);

fileIDw = fopen('hist_wykladniczy.txt','r');
[W,size] = fscanf(fileIDw,'%f');
nbins = 100;
figure(2)
title('Histogram rozk�adu wyk�adniczego');
xlabel('Losowane liczby');
ylabel('Ilo�� wylosowanych liczb');
hist(W,nbins);
fclose(fileIDw);


