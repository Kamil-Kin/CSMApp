lambda = [];
wart_szukana = 0.1;
fileID = fopen('sr_stopy_bledow.txt');
A = fscanf(fileID,'%f');
fclose(fileID);
tab = zeros(10,10);
for i = 1:10
    for j = 1:10
        tab(i,j) = A(j+10*(i-1));
    end
end
S = sum(tab);

figure(1)
plot(lambda,S,'b')
hold on
plot(lambda,war_szukana,'r')
title('Wyznaczenie parametru lambda')
xlabel('Intensywnoœæ zg³oszeñ - wartoœci lambda')
ylabel('Œrednia pakietowa stopa b³êdów')
legend('œrednia stopa b³êdów','wartoœæ szukana')
grid on