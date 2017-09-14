format long;
lambda = [0.0025 0.0027 0.0028 0.003 0.0031 0.0032 0.0034 0.0037];
x = [0.0024 0.0038];
wart_szukana = [0.1 0.1];
fileID = fopen('sr_stopy_bledow_test.txt');
A = fscanf(fileID,'%f');
fclose(fileID);
tab = zeros(8,10);
for i = 1:8
    for j = 1:10
        tab(i,j) = A(j+10*(i-1));
    end
end
suma = sum(tab,2);
srednia = 10.\suma;
odchyl_stand = std(tab,0,2);
t = 2.2622; M = 10;
granica = t*(odchyl_stand/sqrt(M-1));
lewa_granica = srednia - granica;
prawa_granica = srednia + granica;
przedzial = [lewa_granica prawa_granica];
% disp(odchyl_stand);
% disp(granica);
figure(1)
plot(lambda,srednia,'b-*')
grid on
hold on
plot(x,wart_szukana,'r')
hold on 
plot(lambda,przedzial,'k+')
axis([0.0024 0.0038 0.07 0.13]);
title('Wyznaczenie parametru lambda')
xlabel('Intensywnoœæ zg³oszeñ - wartoœci lambda')
ylabel('Œrednia pakietowa stopa b³êdów')
legend('œrednia stopa b³êdów','wartoœæ szukana','przedzia³ ufnoœci','Location','NorthWest')
