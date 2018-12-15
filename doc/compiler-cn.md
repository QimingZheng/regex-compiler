[中文版](compiler-cn.md) [English](compiler.md)

compiler 将 ast 转换为 GlushKov NFA

compiler 控制流：

    1. 遍历ast，标记上每个叶节点（含有实际字符）的ids，并创建对应的state
    2. 创建init-state
    3. 计算ast的V-set，如果接受空串，init-state (is_final = 1）
    4. 顺次计算 P-set， D-set， F-set，并连接nfa graph的state，标记final state的is_final变量

后续需要完善的地方：

    1. 同parser，规范化一些变量/exception的命名与处理
    2. 看看是否有低效的部分会导致编译时间较长（一些多层for是否必要，能否换种数据结构实现而不增加可读性/使用性难度）