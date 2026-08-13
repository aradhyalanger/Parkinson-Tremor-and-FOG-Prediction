clc;
clear;
close all;

%% Load CSV data
data = readtable('../Data/sample_tremor_data.csv');

t  = data.time;
gx = data.gyro_x;

%% Sampling frequency
fs = 100;   % 100 Hz

%% Remove DC offset
gx = gx - mean(gx);

%% Band-pass filter (3-8 Hz)
[b,a] = butter(4,[3 8]/(fs/2),'bandpass');
gx_filt = filtfilt(b,a,gx);

%% RMS calculation
rms_val = rms(gx_filt);

fprintf('RMS = %.3f deg/s\n', rms_val);

%% FFT analysis
N = length(gx_filt);
f = (0:N-1)*(fs/N);
Y = abs(fft(gx_filt));

[~,idx] = max(Y(1:floor(N/2)));
peakFreq = f(idx);

fprintf('Peak Tremor Frequency = %.2f Hz\n', peakFreq);

%% Time-domain plot
figure;
plot(t,gx_filt,'LineWidth',1.5);
xlabel('Time (s)');
ylabel('Gyro X (deg/s)');
title('Filtered Tremor Signal');
grid on;

%% Frequency-domain plot
figure;
plot(f(1:floor(N/2)),Y(1:floor(N/2)),'LineWidth',1.5);
xlabel('Frequency (Hz)');
ylabel('Magnitude');
title('FFT Spectrum');
grid on;

%% Save processed signal
output = table(t,gx_filt,'VariableNames',{'time','gyro_x_filtered'});
writetable(output,'processed_tremor_signal.csv');

disp('Processed file saved: processed_tremor_signal.csv');