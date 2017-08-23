fileID = fopen('hist_rownomierny.txt','r');
[R,size] = fscanf(fileID,'%f');
nbins = 10;
histogram(R,nbins);