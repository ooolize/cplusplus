### 需求
用字符串查询文本 例如 the & moon | key

列出 所在行的行号和文本
### 分析
+ 首先定义单个单词查询类TextQuery（内部有个query提供实际查找工作）,负责读取文件，保存每个单词的相关信息。使用QueryResult类保存查询的返回值

+ 然后定义基类Query_Base，基类定义了接口
```
QueryResult eval(TextQuery&t);//所有继承类都从该接口得到查找结果
string rep();//返回要查找的单词
```
+ 由基类派生了NotQuery,AndQuery,OrQuery,其中每个类的eval()都完成自己的工作。
+ 每个string需要封装，封装成什么呢?用TextQuery吗？

我们需要定义一个接口类Query，里面有一个数据指针成员指向基类，这样我们就可以实现多态了，但是传递过来的是一个字符串，我们需要使用一个构造函数，
“将字符串纳入继承体系中”，这个操作就需要新定义一个类WordQuery继承自Query_Base.它含有一个string成员,而正是这个成员被TextQuery所使用。

string--->WordQuery--->Query

所有的string,先是WordQuery再是Query

### 拓展
+ 封装命令解析。
+ 将TextQuery设计成单例模式
