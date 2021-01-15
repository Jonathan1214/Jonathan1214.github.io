---
title: 记录高频硬件课程设计
date: 2019-12-29 09:23:10
updated:
categories:
  - 生活
tags:
  - 记录
---
本文绝大部分内容是在19年12月29日写的，我记得很清楚，那天是周日上午，我没有为即将到来的通原考试而复习，而是选择去写点东西记录几天前刚刚结束的高频课设，这是一次很难忘的经历，有痛苦也有快乐，有想过放弃但还是坚持了下来，感谢自己和队友们。现在是2020年3月15日，本该在学校度过周日的我，和所有的大学生一样，因为肺炎疫情只能在家里学习，我没什么学习状态，有些无聊，因此整理博客，把这篇去年的记录整理整理，发到GitHubBlog上，留作纪念，发表日期还是使用去年写这篇文章的日子。
<!-- more -->

## 最终验收

12月24号，高频硬件课设验收，在队友的强烈要求下，我们选择了一个比较宽松的老师给我们验收，因为我们功率达不到，但还想 **『恰完烂分』**，这能对他的保研有所帮助。最后的结果很好，我们拿到了5分（满分5分），**『烂分恰完』**。
<div align="center" class="img">
    <img src="/assets/img/2019/final.jpg" alt="验收" height="400">
    <p align="center" style="color:#999">最终验收时电路连接和波形</p>
</div>

## 开始

12月17号周二下午考完『随机过程』，终于有时间休息了，躺了一个小时，吃个饭，室友已经去搞硬件了，虽然已经是晚上9点多了，但我还想去，带上东西，去李老师办公室焊。折腾了两个小时，焊好了一个西勒振荡器，但没有测试工具，只能第二天测试焊接是否正确，测试工具缺乏和焊接出错这两个问题在整个课设过程中一直困扰着我们。
<div align="center" class="img">
    <img src="/assets/img/2019/siler_oscillator.jpg" alt="西勒振荡器" height="400">
    <p align="center" style="color:#999">第一天晚上焊好的西勒振荡器</p>
</div>

## 一起干

第二天是周三，没有课，我和赵公子决定去实验室接着焊板子，顺便测试下昨晚上焊的振荡器。两个小时后，我们焊好了发射机和接收机的振荡器，经过测试，他的能用，而我的那块振荡器产生了寄生调幅。检查了电路没有任何问题，折腾到下午，最后发现是射极偏置电阻过大导致的，微调射极电阻，即可解决这个问题。

下午和晚上我们都在实验室呆着，一直做到晚上11点。因为我已经很久没焊接东西，有点手生，他更是没啥经验，我们效率比较低，只焊好了一个乘法电路、一个中频放大器和一个包络检波器。后面测试时发现，我焊接的那个乘法电路不能实现信号相乘。那时我还不知道，接下来3天我都会把时间花在乘法电路上，如果早知道调试它会这么折腾，第一天晚上就应该当机立断重新焊一个的。

## 心生退意

接下来的几天我感到痛苦不堪，我焊接乘法电路始终不好使，不知为什么我就是不愿重新焊一块，执着地想把它修好，但这一切都是徒劳的。看着周围的同学一个个都做出来乘法电路了，我开始怀疑自己：如果做不出来是不是证明我不行，我怎么能不行呢？要不放弃吧，这样就不存在证明了，我告诉自己这些bonus对我来说并不那么重要，我保研与否与这课设5分没什么关系。沃老板执着地说焊板子的烟搞得他很难受，实验室里面人太多了，空气太差，乌烟瘴气，他想回寝室做，这样的参与状态让我心有不快，偏偏他才是一定要拿这 5 分保研的人，为什么我要受这些精神折磨，我当时的确不想再做下去了。

周六早上，纠结了许久，我去教化补充了些元器件，决定去实验室再焊一个乘法器，还说服沃老板也焊一个接收机的乘法电路。我不知道是什么力量支撑着我继续做下去，这件事对我来说不是那么必要，最诱人的bonus并不是我一定需要的，如果不做课设，我可以去复习通原，我可以享受轻松的一周。事后我仔细想了想，大概是因为我自己的性格决定的，我不是那种遇到问题就放弃的人，借口谁都有一些，但是作为我，一旦开始做了，就要做到最后，没有中途放弃的，之前的软件仿真就是如此，没有理由硬件不坚持下去，到这个时候，其实做这个课设已经变成了和自己较劲了，我不想就这么输了。

周六下午去做了通信原理实验，晚上终于焊好我的第二块乘法电路，测试再次失败，沃老板也焊好接收机混频电路，经过测试也失败。这时候我心态已经到了最低点了，我真的不想再来了，前面说的那么多不服输如何如何，可是看着别人一个个做好，我的却始终不行，旁边还有人明着嘲讽我，这使我明白『挫败感』是何含义。晚上10点，我和沃老板回寝室了，赵公子在周五下午有事回家了，但他做的已经足够多了。我突然决定不再去了。

## 坚持才是胜利

周日上午我还是去实验室了，我想就是什么都做不出来，也得一直在实验室坐着，我就要和它刚到底。好在一切坚持都没有白费，我的乘法电路测试成功了，事实证明我的电路设计没有问题，焊接的也没有问题，昨晚测试失败只是因为电路连线没有接好，胜利让我欣喜若狂，我真想大声怒吼：我终于完成了。另一边也有好消息传来，沃老板焊的和赵公子焊的乘法电路都是好使的，还有什么比此刻更快乐呢？

<div align="center">
    <img src="/assets/img/2019/amplitude_modulation.jpg" alt="AM调幅" height="400">
    <p align="center" style="color:#999">赵公子的乘法器AM波形</p>
    <img src="/assets/img/2019/mixing.jpg" alt="混频" height="400">
    <p align="center" style="color:#999">沃老板的混频器波形</p>
</div>

周日下午发生了一些不愉快的事情，因为下午找不到他人（其实他在午睡），我对沃老板的不满更加强烈了，而那时我已经十分疲惫，愤怒之下，下午3点左右我直接回寝室，拒绝回他消息，然后睡了一觉。期间他来找我，我『哈哈』糊弄过去，不想再干。6点多起来看一眼手机，想了想，还是再去试试，把级联和功率要求做完吧，都已经到这个份上了，干脆就把它做到完。

## 乘胜追击

我不想就此打住，野心开始膨胀了，**『恰5分』** 是调侃，此时更像是口号。发射机 AM 调制输出接上我焊调试乘法器抽空焊好的小信号放大器，效果非常好！放大了80倍，但我心里清楚，因为没有接负载，最后功率肯定达不到；接收机，混频后中频放大再检波，效果很差，但也算检波出来了，在要求不那么严苛的时候，可以拿到分；发射机接收机级联成功，和仿真保持一致。

如此算来，我们已经可以拿到 4.5 分，但是我们不想收手，我们继续调放大器，要把功率的 5 分也拿到手。很不幸，我们没有成功，三极管射极电阻过小，导致射极电流过大，二极管被烧坏了，放大器也就怀了，这又是我们唯一的放大器，级联也没办法做了，这下只有 4 分了，后悔，懊恼。

第二天周一，已经是12月23号了，我都没想到自己会在这上面花上近一周时间。白天上了一天课，晚上我们接着调试了一下，还是那个问题，AM 波后的小信号放大器不好使，级联就不行，功率也没有。赵公子也回来了，我们让他重新焊了一个，失败了，因为我临时对之前测试成功的电路做了修改，为了减小电流避免三极管烧毁的事再发生，但是我没想到这么一改，电流太小，放大倍数达不到要求，而且我应该自己亲手焊的。可以说今天又是一无所获。但我不会就此打住，我不愿放弃。

周二上午上完微波课，我立马去教化买了元件，再焊一个小信号放大器，再试一次，不到最后，谁也不知道结果，我不想放弃。一番折腾，焊好，测试，成功。

下午验收前一刻，上周三买的陶瓷滤波器终于从深圳邮到了学校，我赶紧去取回来，接到电路中，完美!**『烂分恰完』**。

## 后记

做完这次课设，心里有太多感慨，很多次我都想放弃了，但是总有一股力量把我拉了回来，这其中有对朋友承诺的坚守也有自己那股不服输的劲，验收成功那一刻我有点想哭，是啊，这整个过程只有我自己这么看重吧，最后还在自我感动，但如果没有这自我感动，我不知道自己能否坚持下来。当然，课设整个过程也暴露了我的一些问题：我需要有更强大的精神力量，激励自己前进，也要学会如何带领团队前进。