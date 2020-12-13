---
title: LaTex笔记（一）——基本概念
date: 2020-03-27 12:13:12
updated:
toc: true
comment: false
categories:
  - 学习
tags:
  - LaTeX
---
## 概述

Tex是高德纳开发的排版文字和数学公式软件。TeX稳定，跨平台，支持多语言排版，其版本号非常有意思，无限趋近于pi，3.1415926...读作Tech，泰赫。

LaTex是一种格式，可以把LaTex理解成是对TeX的封装。LATeX使用TeX程序作为自己的排版引擎。设计目标是分离内容和格式。读作拉泰赫。
<!--more-->
## 第一份代码

```Tex
\documentclass{article}
\begin{document}
``Hello world!'' from \LaTeX
\end{document}
```

一份简短的程序，保存为`helloworld.tex`，然后在命令行下使用`xelatex helloworld`编译即可。

## LaTeX命令和代码结构

源代码为文本文件，包括了内容以及命令，可以控制样式，划分文档结构及排版公式。

### 命令和环境

同几乎所有的编程语言一样，LaTeX命令对**大小写敏感**，命令以`\`开头，有两种形式：

+ \ + 一串字母：如`\LaTex`，且任意非字母符号为界限。暂且称其为字母形式。
+ \ + 单个非字母符号：如`\$`。称其为字符形式。

字母形式的命令忽略其后的所有连续空格，所有的空格都被认为用来标志命令的结束，如果需要空格，使用`{}`，如`\TeX{} user`既可以把空格显示出来，类似于**转义**。

接受参数。包括可选参数和必选参数，可选参数用`[]`包裹，必选参数使用`{}`包裹。带`*`的命令可看为*特殊的可选参数*。

环境。可以使一些效果在局部生效，或是生成特殊的文档元素。用法：

```TeX
\begin{<environment name>}[<optional arguments>]{<mandatory arguments>}
...
\end{<environment name>}
```

分组。限制一些命令的作用范围。使用`{}`作为分组，分组中使用的命令限制在分组内。

### 源代码结构

以`\documentclass{...}`命令开头，花括号中指定了文档使用的文档类。有可选参数，可传递给指定文档类，最终作为文档类的参数。

然后在document环境中写文档正文。

```Tex
\begin{document}
...
\end{document}
```

在`documentclass`和`\begin`中间的部分称为导言区。一般在其中使用`\usepackage`调用宏包，对文档进行全局设置。

## 宏包和文档类

### 文档类

规定了LaTeX源代码说要生成的文档的性质。`documentclass[<options>]{class-name}`。

`class-name`即文档类名，包括LaTeX提供的article、book和report的**标准文档类**，还有派生出支持中文排版的ctexart，ctexbook，ctexrep，以及一些其他。

`options`为可选参数，指定文档类的选项，如字号、纸张大小和单双面等等。参数使用逗号分隔。`documentclass[11pt,twosides,a4paper]{article}`。

标准文档的选项包括：（略多，需要时查看即可）。

### 宏包

用来扩展LaTeX的功能，如插入复杂表格和图片，增加颜色或超链接等等。语法类似使用文档类：`usepackage[<options>]{package-names}`。可以一次性使用多个宏包，逗号分隔即可。

命令行使用`texdoc package-name`查看包的使用方法。

## LaTeX用到的文件

编译使用文件：

+ .sty：宏包文件。
+ .cls：文档类文件。
+ .bib：BiBTeX参考文献数据库文件。
+ .bst：BiBTeX用到的参考文献格式模板。

编译生成文件：

+ .log：日志
+ .aux：LaTeX生成的主辅助文件，记录交叉引用、目录、参考文献的引用。
+ .toc：LaTeX生成目录记录文件
+ .lof：LaTeX生成图片记录
+ .lot：LaTeX生成表格记录
+ .bbl
+ .blg
+ .idx
+ .ind
+ .ilg
+ .out

## 文件的组织方式

可将源文件分隔成若干个文件，如将没章的内容单独写在一个文件中，然后使用`\include{<filename>}`在源代码里引用即可。注意路径的书写。可以不带扩展名，默认为.tex。

使用`\include`会另起一页，使用`\input{filename}`避免这种情况。

导言区使用`includeonly{<filename1>,<filename2>...}`指定正文中可以引用的文件。

实用工具包：syntonly。然后在导言区使用`\syntaxonly`，不生成PDF文档，加快编译速度。

注释：使用`%`。和MATLAB一样。

## 术语和概念

引擎：XeTeX。
格式：定义了一组命令的代码集，LaTeX。
编译命令：实际调用的、结合引擎和格式的命令，xelatex。

---
链接：[lshort](https://mirrors.tuna.tsinghua.edu.cn/CTAN/info/lshort/chinese)
