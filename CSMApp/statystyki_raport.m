format long;
fileID = fopen('statystyki_srednia.txt');
A = fscanf(fileID,'%f');
fclose(fileID);
stat = zeros(10,6);
for i = 1:6
    for j = 1:10
        stat(j,i) = A(j+10*(i-1));
    end
end
% disp(stat);
srednia = mean(stat); %disp(srednia);
odchyl_stand = std(stat,0); %disp(odchyl_stand);
t = 2.2622; M = 10;
granica = t*(odchyl_stand/sqrt(M-1)); %disp(granica);
