lambda = [];
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
plot(lambda,S)
title('')
xlabel('')
ylabel('')
legend('')
grid on