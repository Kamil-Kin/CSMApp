format long;
lambda = [0.0025 0.0027 0.0028 0.003 0.0031 0.0032 0.0034 0.0037];
fileID = fopen('przeplywnosc_test.txt');
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
axis([0.0024 0.0038 105 108.5])
title('Wykres przep³ywnoœci w zale¿noœci do lambda')
xlabel('lambda')
ylabel('Przep³ywnoœæ')
legend('przeplywnoœæ')
