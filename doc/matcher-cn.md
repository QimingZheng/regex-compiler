[中文版](matcher-cn.md) [English](matcher.md)

matcher在compiler得到的nfa上运行，

matcher 控制流：

    1. matcher CPU版本包含两种matcher，naive matcher直接在nfa state上运行，而table-based在构造阶段需要初始化table
    2. states 为bit-array，表示每个state的状态
    3. final_states 为bit-array，表示每个state是否为final state
    4. begin_index_of_states 大小恒为256， 表示读到输入字符ch后incoming condition 为 ch的 连续的若干个state的第一个的下标。
    5. begin_index_of_pre 大小为state数，表示每个state的incoming state的第一个在pre_states的下标
    6. pre_states 大小为跳转数，通过begin_index_of_pre只向到pre_states中的一段，值为state的id，作为查找states的索引


注意，由于states为未初始化的，因此matcher的第一步总是需要设置init-state的状态为1。后续如果想自己实现更为高效的matcher需要注意这一步。


无限优化改进空间。。