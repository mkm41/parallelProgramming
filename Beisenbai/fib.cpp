#include<iostream>
#include<mutex>
#include<thread>
#define N 10
 
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
	int j=1;
	int t=2;
	if (n == 2){
		mu.lock();
		std::cout<<"Indeksi taq bolatyn Fibonacci sandary: ";
		mu.unlock();
		for(int i=0;i<N;i++){
			if(i%2==0){
				std::cout<<"["<<j<<"]="<<fib()<<std::endl;
				j+=2;
			}
			else
				fib();
		}
		std::cout<<std::endl;
	}
	else{
		mu.lock();
		std::cout<<"Indeksi jup bolatyn Fibonacci sandary: ";
		mu.unlock();
		for(int i=0;i<N;i++){
			if(i%2!=0){
				std::cout<<"["<<t<<"]="<<fib()<<std::endl;
				t+=2;
			}
			else
				fib();
		}
		std::cout<<std::endl;
	}
}
	


int main() {
	Fib fib;

	for(int i=0;i<N;i++){
		std::cout<<fib()<<" ";
	}
	std::cout<<std::endl;
	std::cout<<std::endl;
	

	std::thread thSecond(ZhupTaq, 1);
	mu.lock();
	std::thread thFirst(ZhupTaq,2);
	mu.unlock();
	
	thFirst.join();
	thSecond.join();

return 0;
}

