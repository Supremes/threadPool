#include <iostream>
#include <vector>
#include "threadPool.h"
using namespace std;

int main(int argc, char const *argv[])
{
    int numThreads = 4;
    threadPool pool(numThreads);
    vector<func> tasks_;
    while(1){
        for(int i = 0; i < 20; i++){
            pool.enQueue(bind(runTest, to_string(i)));
        }
    }
    
    return 0;
}
