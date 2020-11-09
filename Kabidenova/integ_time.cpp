#include<iostream>
#include<thread>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <math.h>
#include <cmath>

/*
Анықталған интегралды берілген интервалда n ағынмен есептеу
f(x) = 2x^6+3sin(x)-1,  x - [-3;1]
*/

double sum = 0;

double function(double x){
	return 2*pow(x, 2) + 3*sin(x*x) * x - 1*exp(2*x);
}

double Integ(double a, double b, int n) {
    const double width = (b-a)/n;

    double integral = 0;
    for(int step = 0; step < n; step++) {
        double x1 = a + step*width;
        double x2 = a + (step+1)*width;

        integral += 0.5*(x2-x1)*(function(x1) + function(x2)); 	
    }
    sum = sum + integral;
	return sum;
}
double sum1 = 0;
void Integ1(double a, double b, int n) {
    const double width = (b-a)/n;

    double integral = 0;
    for(int step = 0; step < n; step++) {
        double x1 = a + step*width;
        double x2 = a + (step+1)*width;

        integral += 0.5*(x2-x1)*(function(x1) + function(x2)); 	
    }
    sum1 = sum1 + integral;
}
int main(){
	using namespace std::literals; 
	int a = -3;
	int b = 1;
	int n = 1000;
	
	auto start = std::chrono::steady_clock::now();
	std::thread t1(Integ1, -3, -2, 1000);
	std::thread t2(Integ1, -2, -1, 1000);
	std::thread t3(Integ1, -1, 0, 1000);	
	std::thread t4(Integ1, 0, 1, 1000);
    auto end = std::chrono::steady_clock::now();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	std::cout << sum1 << std::endl;
	double agyn4 = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
    std::cout << "Time of 4 threads is " << agyn4 << " nanoseconds.\n"; 
	
	
	auto start2 = std::chrono::steady_clock::now();
	std::cout << Integ( -3, 1, 1000)<< std::endl;
	auto end2 = std::chrono::steady_clock::now();
	
	double agyn1 = std::chrono::duration_cast<std::chrono::nanoseconds>(end2 - start2).count();
	std::cout << "Time of one thread is " << agyn1 << " nanoseconds.\n";
	//std::cout << sum << std::endl;
	
	std::cout << agyn1/agyn4  << " ese tezirek"<< std::endl;
	
	return 0;
}