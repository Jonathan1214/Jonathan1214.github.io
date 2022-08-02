---
title: 邮件自动发送器
copyright: false
notshow: false
date: 2022-07-25 13:00:45
updated:
categories:
  - 学习
tags:
  - Python
  - cheatsheet
---

一个用 Python 实现的邮件自动发送器，代码不长，这再次展现了 Python 这个胶水语言的简洁。

网上有很多基于 Python 的邮件发送器实现，这里使用的是基于 smtplib 的方式：

<!-- more -->

```python
import smtplib
from email.mime.text import MIMEText

def send_mail(mail_content):
    message = MIMEText(mail_content,'html','utf-8')
    #邮件主题
    message['Subject'] = '[auto] simulation result'
    #发送方信息
    message['From'] = sender
    #接受方信息
    message['To'] = ";".join(receivers)
    # print(message.as_string())
    try:
        smtpObj = smtplib.SMTP()
        #连接到服务器
        smtpObj.connect(mail_host,25)
        #登录到服务器
        smtpObj.login(mail_user,mail_pass)
        #发送
        smtpObj.sendmail(
            sender,receivers,message.as_string())
        #退出
        smtpObj.quit()
        print('success')
    except smtplib.SMTPException as e:
        print('error',e) #打印错误
```

这里我们需要正确设置如下变量：

+ `mail_host -> str`：smtp 邮箱服务器，如 163 邮箱的 `smtp.163.com`
+ `mail_user -> str`：邮箱用户名，即登录时用的用户名，如 `kolinahr`
+ `mail_pass -> str`：密码（或授权码，请 STFW）
+ `sender`：发送方的邮箱地址，如 `kolinahr@163.com`
+ `receivers -> [str]`：邮箱接收者列表，如 `[wds00@qq.com, wgdgf01@qq.com]`
+ `message -> str`：待发送的信息，这里 `MIMEText` 指定了格式为 `html`，也可以使用纯文本，指定为 `plain` 即可

这就是全部内容了。如果需要更简单的方式，可以考虑使用 Python 库 `zmail`，请 STFW。

## 参考链接

[简单三步，用 Python 发邮件](https://zhuanlan.zhihu.com/p/24180606)
