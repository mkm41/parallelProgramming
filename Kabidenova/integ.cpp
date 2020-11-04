#include<iostream>
#include<thread>

/*
Анықталған интегралды берілген интервалда n ағынмен есептеу
f(x) = 2x^2+3x-1,  x - [-3;1]
*/

double sum = 0;

double function(double x){
	return 2*x*x + 3*x - 1;
}

void Integ(double a, double b, int n) {
    const double width = (b-a)/n;

    double integral = 0;
    for(int step = 0; step < n; step++) {
        double x1 = a + step*width;
        double x2 = a + (step+1)*width;

        integral += 0.5*(x2-x1)*(function(x1) + function(x2)); 	
    }
    sum = sum + integral;
}

int main(){
	int a = -3;
	int b = 1;
	int n = 1000;
	
	std::thread t1(Integ, -3, -2, 1000);
	std::thread t2(Integ, -2, -1, 1000);
	std::thread t3(Integ, -1, 0, 1000);	
	std::thread t4(Integ, 0, 1, 1000);
	
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	std::cout << sum << std::endl;
	return 0;
}