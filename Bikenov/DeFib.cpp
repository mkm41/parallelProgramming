#include<iostream>
#include<mutex>
#include<thread>
 
unsigned long const hardware_threads=std::thread::hardware_concurrency();

std::mutex mu;
class Fib {
    public:
	 Fib() : a0_(1),a1_(1) {}
	 int operator ()();
    private:
	 int a0_,a1_;
		
};

int Fib::operator ()(){
	int temp=a0_;
	a0_=a1_;
	a1_=temp+a0_;
	return temp;
}

void evenfib(int n){
	int summa1=0;
	Fib evensum;
		for(int i=0;i<n;i++){
		if(i%2!=0){
			evensum();
			continue;
		}
		
		summa1+=evensum();
	}
	std::cout<<"summa even fibonacci numbers-"<<summa1<<std::endl;
}



void ThreadFunction(int number){
mu.lock();
std::cout<<"Hi,world from "<<number<<"-th thread id: "<<std::this_thread::get_id()<<std::endl;
mu.unlock();
}

int main() {
	std::cout<<std::endl;
	Fib fib;

	for(int i=0;i<10;i++){
		std::cout<<fib()<<",";
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
	
std::cout<<std::endl;
std::cout<<std::endl;

std::cout<<"Hi,world from main thread"<<std::endl;
std::cout<<" Main thread id: "<<std::this_thread::get_id()<<std::endl;
std::cout<<"we have "<<hardware_threads<<" processors"<<std::endl;

std::thread Evenfib(evenfib,10);
std::thread thFirst(ThreadFunction,1);
mu.lock();
std::cout<<" First thread id: "<<thFirst.get_id()<<std::endl;
mu.unlock();
std::thread thSecond(ThreadFunction,2);
mu.lock();
std::cout<<" Second thread id: "<<thSecond.get_id()<<std::endl;
mu.unlock();
std::thread thThird(ThreadFunction,3);
mu.lock();
std::cout<<" Third thread id: "<<thThird.get_id()<<std::endl;
mu.unlock();

Evenfib.join();

thFirst.join();
thThird.join();
thSecond.join();

return 0;
}

