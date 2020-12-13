EbN0dB = 0:1:10;
EbN0 = 10.^(EbN0dB/10);
N = 2*10^6;                     % 发送比特数即码元数
Pb = 0.5*erfc(sqrt(EbN0));      % 理论值
ber = zeros(1, length(EbN0dB)); % 仿真误码率 预分配
a = sign(randn(1, N));          % 基带信号
noise = randn(1, N);            % 标准噪声
sigma = sqrt(1./EbN0/2);        % 噪声功率
for n = 1:length(EbN0dB)
    rk = a + sigma(n)*noise;    % 加噪声得到接收信号
    dec_a = sign(rk);           % 判决
    ber(n) = sum(abs(a-dec_a)/2)/length(a);
end

semilogy(EbN0dB, Pb, 'LineWidth', 1);
hold on;
semilogy(EbN0dB, ber, 'rd');
legend('理论结果', '仿真结果')
xlabel('\itE_b/N_0\rm(dB)'); ylabel('Pb');
title('BPSK误码率仿真')
grid on