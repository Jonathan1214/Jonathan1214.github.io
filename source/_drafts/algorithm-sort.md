---
title: 排序算法
toc: true
categories:
 - 学习
tags:
  - 算法
  - 数据结构
---


1. 哈尔滨的移动用户呼叫北京地区用户，通过随机接入信道（RACH）向基站收发信台（BTS）发送接入请求，请求分配一条独立专用控制信道（SDCCH）。
2.

主呼用户接入过程：哈尔滨的MS向通过RACH向BTS发送接入请求，BTS将接入请求转发给BSC，BSC根据实际情况通知BTS经AGCH向MS发送对接入请求的应答，并分配给MS一个SDCCH。MS接收到分配信息后，通过分配的SDCCH向BTS发送鉴权信息，BTS将鉴权信息经BSC转MSC处的AUC进行鉴权；鉴权通过后，MSC会要求BSC向MS分配TCH，接入过程完成。
路由过程：MSC根据MS发送的MS ISDN可以知道用户不在本服务区，分析出其 HLR 并向它请求 MSRN。HLR根据ISDN信息找到ISDN对应北京的MS所在的VLR2和MSC2，并向MSC2请求MSRNMSC2从MSRN池中选择一个空闲号码回复HLR，HLR转发给请求MSRN的MSC，MSC根据MSRN就可以找到北京的被呼用户所在的MSC2，路由过程结束。
寻呼过程：MSC2根据IMSI从VLR2中查找被呼MS的位置区，即找到被呼MS接入的BSC，并向BSC发起向MS寻呼的请求，BSC通知BTS分配一条PCH，BTS开始寻呼用户，MS应答后，通话建立，被呼MS响铃。