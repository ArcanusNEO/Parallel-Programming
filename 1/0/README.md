# 体系结构相关及性能测试 - 向量内积

- 使用 cmake 构建

- C++17 标准

- 二进制文件位于 build/bin/

- 由 gen-data 生成的测试数据位于 res/，文件名为 n.in，矩阵内数字的范围为 [0, 100]

- 输入配置文件位于 conf/in.conf，要求其路径作为第一个参数传入程序

  写法

  - 第一行为输入文件目录路径
  - 余下每一行为测试输入文件名和重复测试次数，空格隔开

- ordinary 采用 *逐列访问的平凡算法*

- cache 采用 *cache 优化算法* 

- x86 架构的一次测试结果保存在 res/*.out.txt

- 为了便于调整数据规模的同时保证数据分布紧凑，矩阵采用一维数组模拟

- 使用 chrono 计时库

- 实验报告位于 doc/

运行测试方式：

```sh
build/bin/ordinary conf/in.conf | tee misc/ordinary.out.txt
build/bin/cache conf/in.conf | tee misc/cache.out.txt
```

