简介：
>创建固定数量的线程，来处理多个任务，线程执行完一个任务后不销毁而是继续执行下一个任务，这样就避免了线程的频繁创建和销毁，大大提高了效率

一个基本的线程池需要包含以下部分：
- 工作线程：
>项目中使用RAII机制封装了thread, mutex, condition,工作线程是一个thread类型的vector容器（vector<thread>）
- 任务队列：
 ```
  typedef std::function<void(string)> func;
  queue<func> tasks_;
```
>定义了每个任务函数的类型，任务队列是一个func类型的queue

- 用于添加任务的接口函数(threadPool::enQueue()):
>工作线程运行该函数，不断的从任务队列汇总取出任务并执行.



