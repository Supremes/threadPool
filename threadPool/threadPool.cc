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
	//唤醒所有阻塞的线程
	cond_.notifyAll();
	for(auto &thread: threads_)
		thread.join();
	cout << "~threadPool" << endl;

}

bool threadPool::enQueue(threadFun func){
	//操作工作队列时加锁，因为这是所有线程所共享的
	MutexLockGuard lock(mutex_);
	tasks_.push(func);
	cond_.notifyOne();
	return true;
}

void threadPool::run(){
	while(!stop){
		threadFun temp = take();
		if(temp)
			temp("ok");
	}
}

threadPool::threadFun threadPool::take(){
	threadFun funcTemp;
	if(!tasks_.empty()){
		MutexLockGuard lock(mutex_);
		cond_.wait();
		funcTemp = tasks_.front();
		tasks_.pop();
	}
	return funcTemp;
}
