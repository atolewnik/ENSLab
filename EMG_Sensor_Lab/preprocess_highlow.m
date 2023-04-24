function y = preprocess(x)
%  Preprocess input x
%    This function expects an input vector x.

% Generated by MATLAB(R) 9.12 and Signal Processing Toolbox 9.0.
% Generated on: 23-Oct-2022 23:54:49

% Data -> High Pass -> Low Pass

y = highpass(x,0.5,'Steepness',0.85,'StopbandAttenuation',60);

y = lowpass(y,0.5,'Steepness',0.85,'StopbandAttenuation',60);