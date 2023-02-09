original_fs = 44100 * 10;
sampled_fs = 44100;
intvl = 1/original_fs; 
samlv = 1/sampled_fs; 
freq = 19000;
secs = 0.0009;
tim = intvl:intvl:secs;
tim2 = samlv:samlv:secs;

upscaled_fs = 44100 * 8;
intup = 1/upscaled_fs;
time_up = intup:intup:secs;


wav = 127 * sin(tim * 2 * pi * freq) + 128;
wav2 = 127 * sin(tim2 * 2 * pi * freq) + 128;

data = wav2';
ts = time_up;
[Ts, T] = ndgrid(ts, tim2);
disp(Ts - T);
y = sinc(Ts - T) * data;

# yspline = interp1(tim2, wav2, time_up, "spline");
# yspline = interp1(tim2, wav2);

figure(1);
plot(tim, wav, "b-", tim2, wav2, "r+", ts, y, 'g-'); 
#, time_up, yspline, "g-")