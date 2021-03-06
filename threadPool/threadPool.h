#include "Thread.h"
#include "Condition.h"
#include <thread>
#include "MutexLock.h"
#include <vector>
#include <queue>
using namespace std;

class threadPool{
public:
	typedef std::function<void(string)> threadFun;
	threadPool(int num);
	~threadPool();
	/*往任务队列里添加任务*/
	bool enQueue(threadFun func);
	/*工作线程需要运行的函数,不断的从任务队列中取出并执行*/
	void run();
	threadFun take();
private:
	MutexLock mutex_;
	Condition cond_;
	int numThreads;
	bool stop;
	//vector<std::thread> threads_;
	vector<Thread> threads_;
	queue<threadFun> tasks_;
};