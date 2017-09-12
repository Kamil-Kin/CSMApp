format long;
lambda = [0.0055 0.006 0.0065 0.007 0.0075];
wart_szukana = [0.1 0.1 0.1 0.1 0.1];
fileID = fopen('sr_stopy_bledow.txt');
A = fscanf(fileID,'%f');
fclose(fileID);
tab = zeros(5,10);
for i = 1:5
    for j = 1:10
        tab(i,j) = A(j+10*(i-1));
    end
end
S = sum(tab,2);
mean = 10.\S;
figure(1)
plot(lambda,mean,'b-*')
grid on
hold on
plot(lambda,wart_szukana,'r')
title('Wyznaczenie parametru lambda')
xlabel('Intensywno�� zg�osze� - warto�ci lambda')
ylabel('�rednia pakietowa stopa b��d�w')
legend('�rednia stopa b��d�w','warto�� szukana')
