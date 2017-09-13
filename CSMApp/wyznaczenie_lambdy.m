format long;
lambda = [0.0055 0.006 0.0061 0.0062 0.0065 0.007 0.0075 0.008];
x = [0.00525 0.00825]
wart_szukana = [0.1 0.1];
fileID = fopen('sr_stopy_bledow.txt');
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
odchyl_stand = std(tab,1,2);
t = 2.2622; M = 10;
granica = t*(odchyl_stand/sqrt(M-1));
lewa_granica = srednia - granica;
prawa_granica = srednia + granica;
przedzial = [lewa_granica prawa_granica];
disp(odchyl_stand);
disp(granica);
figure(1)
plot(lambda,srednia,'b-*')
grid on
hold on
plot(x,wart_szukana,'r')
hold on 
plot(lambda,przedzial,'k+')
axis([0.00525 0.00825 0.085 0.115]);
title('Wyznaczenie parametru lambda')
xlabel('Intensywnoœæ zg³oszeñ - wartoœci lambda')
ylabel('Œrednia pakietowa stopa b³êdów')
legend('œrednia stopa b³êdów','wartoœæ szukana','przedzia³ ufnoœci','Location','NorthWest')
