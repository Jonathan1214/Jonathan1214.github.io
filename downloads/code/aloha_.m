clear all;clc;
% ALOHA 仿真
% 网络负载G
% 成功发送条件，请求为0
T = 100000;   % 仿真时间 1000个帧长
load_scale = 0.1;
G = 0:load_scale:5; % 网络负载
requests = zeros(T+1, size(G,2)); % 请求次数
pure_ALOHA_sucess = zeros(1,size(G,2)); % pure ALOHA成功次数
slotted_ALOHA_sucess = zeros(1,size(G,2)); % slotted ALOHA
% 产生请求
for g = 1:size(G,2)
    requests(:,g) = random('Poisson',G(g),T+1,1);
end
% pure ALOHA
for g = 1:size(G,2)
    for index = 1:T
       if requests(index,g) + requests(index+1,g) == 0
           pure_ALOHA_sucess(g) = pure_ALOHA_sucess(g) + 1;
       end
       if requests(index,g) == 0
           slotted_ALOHA_sucess(g) = slotted_ALOHA_sucess(g) + 1;
       end
    end
end
%% calculate
% pure ALOHA
probl_pure_ALOHA = pure_ALOHA_sucess / T; % 成功概率
S_pure_ALOHA = G.*probl_pure_ALOHA;       % 吞吐率
% slotted ALOHA
probl_slotted_ALOHA = slotted_ALOHA_sucess / T;
S_slotted_ALOHA = G.*probl_slotted_ALOHA;
%% plot
% pure
figure(1)
yyaxis left
plot(G,probl_pure_ALOHA)
ylabel('Probablity of Sucess')
yyaxis right
plot(G,S_pure_ALOHA)
title('Average Throughput of Pure ALOHA')
xlabel('G')
ylabel('Average Throughput')
grid on
% slotted
figure(2)
yyaxis left
plot(G,probl_slotted_ALOHA)
ylabel('Probablity of Sucess')
yyaxis right
plot(G,S_slotted_ALOHA)
title('Average Throughput of Slotted ALOHA')
xlabel('G')
ylabel('Average Throughput')
grid on