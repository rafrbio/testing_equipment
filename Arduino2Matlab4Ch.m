clear all
close all
clc

delete(instrfindall);
arduino=serial('COM3','BaudRate',9600);
 
fopen(arduino);
 
x=linspace(1,100,100);
   
for i=1:length(x)
	y1(i)=fscanf(arduino,'%f');
    y2(i)=fscanf(arduino,'%f');
    y3(i)=fscanf(arduino,'%f');
    y4(i)=fscanf(arduino,'%f');
end
	
fclose(arduino);
disp('making plot..')
plot(x,y1,x,y2,x,y3,x,y4),legend('data_1','mov-avg_1','data_2','mov-avg_2','Location','best');