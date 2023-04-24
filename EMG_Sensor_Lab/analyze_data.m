clc
clear
close all

emg = readtable("DataRecording2-2022-10-23.csv");
emg = table2array(emg);
emg = transpose(emg);
t = 1:1:length(emg);

subplot(2,1,1);
plot(t, emg);

emg_fft = fft(emg);
subplot(2,1,2);
plot(t, abs(emg_fft));

% [p_time, f_time] = pspectrum(emg);
% [p_freq, f_freq] = pspectrum(emg_fft);
% subplot(2,1,1);
% plot(p_time);
% subplot(2,1,2);
% plot(abs(p_freq));

% figure;
% plot(f_time/pi,abs(p_time));
% 
% figure;
% plot(f_freq/pi,abs(p_freq));