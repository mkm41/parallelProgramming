#include<iostream>
#include<mutex>
#include<thread>
#define N 16
 
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
	a0_ = a1_;
	a1_ = temp + a0_;
	return temp;
}

void ZhupTaq(int n){
	Fib fib;
	if (n == 2){
		std::cout<<"Indeksi taq bolatyn Fibonacci sandary: ";
		for(int i=0;i<N;i++){
			if(i%2==0){
				std::cout<<fib()<<" ";
			}
			else 
				fib();
		}
	}
	else{
		std::cout<<"Indeksi zhup bolatyn Fibonacci sandary: ";
		for(int i=0;i<N;i++){
			if(i%2!=0){
				std::cout<<fib()<<" ";
			}
			else
				fib();
		}
	}
}
	


int main() {
	Fib fib;

	for(int i=0;i<N;i++){
		std::cout<<fib()<<" ";
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
	
	mu.lock();
	std::thread thSecond(ZhupTaq, 1);
	mu.unlock();
	mu.lock();
	std::thread thFirst(ZhupTaq,2);
	mu.unlock();
	
	thFirst.join();
	thSecond.join();

return 0;
}

