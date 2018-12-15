[中文版](parser-cn.md) [English](parser.md)

parser 主要负责了从原始的用户输入rule到ast的部分，给后续compiler提供了构造操作的基础。

parser 控制流：

    1. 对输入的rule串进行extension，补全缺省的concate操作符，补全方法是在 )-char，char-char， )-(，*-X 之间添加concate操作
    2. 完成从中缀表达式到后缀表达式的转换，栈操作实现，根据优先级决定每个操作符的pop/push顺序，具体算法请自行查阅
    3. 完成从后缀表达式到ast的构建，栈操作实现，具体算法请自行查阅
    4. 如果2/3步骤的构造过程中发现rule不合法，会exit，但目前还未完善提前检查rule合法性的检测函数。

parser的ast_node成员包含了一些compiler需要使用的成员变量，parser不作处理。ast_node的ids变量为一个helper变量，在运行时没有实际的意义，因此不要使代码依赖ids的预设值，例如，compiler中使用带ids作为ast遍历时的序号标记，需要先从0开始遍历ast树。

后续parser需要完善的地方有：

    1. 添加输入rule的合法性检测
    2. 通过设置转写规则来支持更完善的语法
    3. 规范化常数变量命名，用枚举类型/宏定义，保证代码的可读性
    4. exception code 的统一化