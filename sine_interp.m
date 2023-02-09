rng default

t_end = 0.2;
% original signal 

orig_freq = 20;
orig_fs = 100000;
dt_orig = 1/orig_fs; 
t_sig = 0:dt_orig:t_end;

wav = sin(t_sig * 2 * pi * orig_freq);

% sampled signal
fs = 50;
dt = 1/fs;
t = 0:dt:t_end;
sampled = sin(t * 2 * pi * orig_freq);
disp(t)
% tx = 1:1:length(t)
% t = t*50;
up_fs = 1000;
up_dt = 1/up_fs;
up_ts = 0:up_dt:t_end;

spline_y = interp1(t, sampled, up_ts, "spline");
breaks = 0:0.01:t_end;

plot(t, sampled, "b+", up_ts, spline_y);
xlabel Time, ylabel Signal
% legend('Sampled','Interpolated','Location','SouthWest')
% legend boxoff