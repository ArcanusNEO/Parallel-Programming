# 体系结构相关及性能测试 - 超标量优化

- 使用 cmake 构建
- C++17 标准
- 由 `gen-data` 生成的测试数据位于 `res/`，文件名为 `n.in`，n为 2 的幂，数组元素的范围为 [-100, 100]
- 输入配置文件位于 `conf/in.conf`，要求其路径作为第一个参数传入程序

  - 第一行为输入文件目录路径
- 余下每一行为测试输入文件名和重复测试次数，空格隔开
- ordinary 采用 *链式求和的平凡算法*
- recursion 采用 *递归求和的算法*
- recur-eliminate 采用 *消除尾递归求和的算法*
- unroll-* 采用 *循环展开的算法*
- x86 架构下 Linux 中的一次测试结果保存在 `misc/*-x86-linux.out.txt`
- 使用 chrono 计时库
- 实验报告位于 `doc/`
