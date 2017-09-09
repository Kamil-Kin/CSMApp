x = 1:1:1000;
tab = zeros(1000,10);
tab2 = zeros(1000,10);
tab3 = zeros(1000,10);
tab4 = zeros(1000,10);
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

for j = 1:1:1000
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

for j = 1:1:1000
    tab2(j,1) = A(j+1000);
    tab2(j,2) = B(j+1000);
    tab2(j,3) = C(j+1000);       
    tab2(j,4) = D(j+1000);
    tab2(j,5) = E(j+1000);
    tab2(j,6) = F(j+1000);
    tab2(j,7) = G(j+1000);
    tab2(j,8) = H(j+1000);
    tab2(j,9) = I(j+1000);
    tab2(j,10) = J(j+1000);
end
S2 = sum(tab2,2);
mean2 = 10.\S2;

for j = 1:1:1000
    tab3(j,1) = A(j+2000);
    tab3(j,2) = B(j+2000);
    tab3(j,3) = C(j+2000);       
    tab3(j,4) = D(j+2000);
    tab3(j,5) = E(j+2000);
    tab3(j,6) = F(j+2000);
    tab3(j,7) = G(j+2000);
    tab3(j,8) = H(j+2000);
    tab3(j,9) = I(j+2000);
    tab3(j,10) = J(j+2000);
end
S3 = sum(tab3,2);
mean3 = 10.\S3;

for j = 1:1:1000
    tab4(j,1) = A(j+3000);
    tab4(j,2) = B(j+3000);
    tab4(j,3) = C(j+3000);       
    tab4(j,4) = D(j+3000);
    tab4(j,5) = E(j+3000);
    tab4(j,6) = F(j+3000);
    tab4(j,7) = G(j+3000);
    tab4(j,8) = H(j+3000);
    tab4(j,9) = I(j+3000);
    tab4(j,10) = J(j+3000);
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
legend('lambda = 0.005', 'lambda = 0.006', 'lambda = 0.007', 'lambda = 0.008')
grid on

