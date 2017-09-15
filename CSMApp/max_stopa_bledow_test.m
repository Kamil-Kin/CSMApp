format long;
lambda = [0.0025 0.0027 0.0028 0.003 0.0031 0.0032 0.0034 0.0037];
fileID = fopen('max_stopa_bledow_test.txt');
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
figure(1)
plot(lambda,srednia,'b-*')
grid on
axis([0.0024 0.0038 0.09 0.15])
title('Wykres maksymalnej stopy b³êdów w zale¿noœci od lambda')
xlabel('lambda')
ylabel('Maksymalna pakietowa stopa b³êdów')
legend('Maksymalna pakietowa stopa b³êdów')
