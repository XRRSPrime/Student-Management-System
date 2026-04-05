# Student-Management-System
这是一个学生管理系统，使用单链表作为存储，包含两个独立的链表作为索引和值的存储。

## 一、项目概述
**学生管理系统**
   - 基于 C++ 的链表实现
   - 支持按学号升序和按总分降序两个视图
   - 支持新增、更新、删除、按学号查询、按姓名查询

## 二、学生管理系统设计

### 数据结构
使用两个独立的链表：

- `numberList`：按学号升序排列
- `scoreList`：按总分降序排列，分数相同时按学号升序

每个学生在两个列表中分别有独立节点，避免排序过程互相干扰。

### 关键函数

#### `Student* findPrevByNumber(string number, Student* list)`
- 目的：找到给定学号的前驱节点
- 作用：便于删除或重新插入节点

#### `Student* findStudentByNumber(string number, Student* numberList)`
- 目的：查找指定学号的学生节点
- 作用：用于修改、查询与判断是否存在

#### `Student* findNumOrder(string number, Student* numberList)`
- 目的：找到按学号升序插入的位置
- 作用：新增学生时保持 `numberList` 排序

#### `Student* findScoreOrder(Student* newStudent, Student* scoreList)`
- 目的：找到按总分降序插入的位置
- 作用：新增或修改后保持 `scoreList` 排序

#### `void addStudent(Student* numberList, Student* scoreList)`
- 功能：添加或更新学生信息
- 逻辑：
  1. 读取输入并计算总分
  2. 若学号已存在，则更新两个列表中的数据并重新排序成绩列表
  3. 若学号不存在，则在两个链表中分别插入新节点

#### `void modify(Student* numberList, Student* scoreList)`
- 功能：修改已有学生成绩与姓名
- 逻辑：
  1. 在 `numberList` 中定位学生节点并更新
  2. 在 `scoreList` 中重新定位并插入，保证排序关系

#### `void erase(string number, Student* numberList, Student* scoreList)`
- 功能：按学号删除学生
- 逻辑：分别从两个链表中删除对应节点

#### `void CoutInformation(Student* list)`
- 功能：打印当前链表内容
- 说明：可用于查看两种排序视图

#### `void clearStudentList(Student* list)`
- 功能：释放链表内存
- 说明：程序退出前调用，避免动态内存泄漏

### 主程序 `main.cpp`
- 增加了用户菜单
- 在每个操作后重新显示菜单
- 程序结束时释放动态内存
