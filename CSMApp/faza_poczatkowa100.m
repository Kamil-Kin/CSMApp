x = 1:1:100;
tab = zeros(100,10);
tab2 = zeros(100,10);
tab3 = zeros(100,10);
tab4 = zeros(100,10);
%%
fileID1 = fopen('opoznienie1.txt');A = fscanf(fileID1,'%f');fclose(fileID1);
%%
fileID2 = fopen('opoznienie2.txt');B = fscanf(fileID2,'%f');fclose(fileID2);
%%
fileID3 = fopen('opoznienie3.txt');C = fscanf(fileID3,'%f');fclose(fileID3);
%%
fileID4 = fopen('opoznienie4.txt');D = fscanf(fileID4,'%f');fclose(fileID4);
%%
fileID5 = fopen('opoznienie5.txt');E = fscanf(fileID5,'%f');fclose(fileID5);
%%
fileID6 = fopen('opoznienie6.txt');F = fscanf(fileID6,'%f');fclose(fileID6);
%%
fileID7 = fopen('opoznienie7.txt');G = fscanf(fileID7,'%f');fclose(fileID7);
%%
fileID8 = fopen('opoznienie8.txt');H = fscanf(fileID3,'%f');fclose(fileID3);
%%
fileID9 = fopen('opoznienie9.txt');I = fscanf(fileID9,'%f');fclose(fileID9);
%%
fileID10 = fopen('opoznienie10.txt');J = fscanf(fileID10,'%f');fclose(fileID3);
%%

for j = 1:1:100
    tab(j,1) = A(j);
    tab(j,2) = B(j);
    tab(j,3) = C(j);       
    tab(j,4) = D(j);
    tab(j,5) = E(j);
    tab(j,6) = F(j);
    tab(j,7) = G(j);
    tab(j,8) = H(j);
    tab(j,9) = I(j);
    tab(j,10) = J(j);
end
S = sum(tab,2);
mean = 10.\S ;

for j = 1:1:100
    tab2(j,1) = A(j+100);
    tab2(j,2) = B(j+100);
    tab2(j,3) = C(j+100);       
    tab2(j,4) = D(j+100);
    tab2(j,5) = E(j+100);
    tab2(j,6) = F(j+100);
    tab2(j,7) = G(j+100);
    tab2(j,8) = H(j+100);
    tab2(j,9) = I(j+100);
    tab2(j,10) = J(j+100);
end
S2 = sum(tab2,2);
mean2 = 10.\S2;

for j = 1:1:100
    tab3(j,1) = A(j+200);
    tab3(j,2) = B(j+200);
    tab3(j,3) = C(j+200);       
    tab3(j,4) = D(j+200);
    tab3(j,5) = E(j+200);
    tab3(j,6) = F(j+200);
    tab3(j,7) = G(j+200);
    tab3(j,8) = H(j+200);
    tab3(j,9) = I(j+200);
    tab3(j,10) = J(j+200);
end
S3 = sum(tab3,2);
mean3 = 10.\S3;

for j = 1:1:100
    tab4(j,1) = A(j+300);
    tab4(j,2) = B(j+300);
    tab4(j,3) = C(j+300);       
    tab4(j,4) = D(j+300);
    tab4(j,5) = E(j+300);
    tab4(j,6) = F(j+300);
    tab4(j,7) = G(j+300);
    tab4(j,8) = H(j+300);
    tab4(j,9) = I(j+300);
    tab4(j,10) = J(j+300);
end
S4 = sum(tab4,2);
mean4 = 10.\S4;

figure(1)
title('Wyznaczenie fazy pocz¹tkowej')
xlabel('numer odebranego pakietu')
ylabel('œrednie opóŸnienie pakietu [ms]')
plot(x,mean,'m','LineWidth',1)
hold on
plot(x,mean2,'c','LineWidth',1)
hold on
plot(x,mean3,'g','LineWidth',1)
hold on
plot(x,mean4,'r','LineWidth',1)
title('Wyznaczenie fazy pocz¹tkowej')
xlabel('numer odebranego pakietu')
ylabel('œrednie opóŸnienie pakietu [ms]')
legend('lambda = 0.003', 'lambda = 0.005', 'lambda = 0.007', 'lambda = 0.009')
grid on

