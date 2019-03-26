#include "threadPool.h"
#include <iostream>
using namespace std;

threadPool::threadPool(int num):mutex_(), cond_(mutex_), numThreads(num), stop(false){
	for(int i = 0; i < numThreads; i++){
		string name = "djkThread" + to_string(i + 1);
		// Thread t(bind(&threadPool::run, this), name);
		// threads_.push_back(t);

		threads_.emplace_back(bind(&threadPool::run, this), name);
	}
}

threadPool::~threadPool(){
	{
		MutexLockGuard lock(mutex_);
		stop = true;
	}
	cond_.notifyAll();
	for(auto &thread: threads_)
		thread.join();
	cout << "~threadPool" << endl;

}

bool threadPool::enQueue(funcThread func){
	//操作工作队列时加锁，因为这是所有线程所共享的
	MutexLockGuard lock(mutex_);
	tasks_.push(func);
	cond_.notifyOne();
	return true;
}

void threadPool::run(){
	MutexLockGuard lock(mutex_);
	while(!stop){
		cond_.wait();
	    //cout << "in" << endl;
		if(tasks_.empty())		
			continue;
		else{
			funcThread funcTemp = tasks_.front();
			tasks_.pop();
			if(funcTemp)
				funcTemp("ok");
		}
	}
}
