#include<iostream>
#include<fstream>
#include<cmath>
#include<thread>
 
using namespace std;
 
double integral(int a,int b,double h){
	
	double sum = 0;
	double x = a;
	while(x < b) {
    sum += (x*x + (x+h)* (x+h));
    x = x + h;
  }
    sum = sum*h/2;
    cout << endl << "The integration is: " << sum << endl;
    return sum;
};
 
int main()
{
	//a=0,b=1,h=0.001
	//integral function x*x
  thread th(integral,0,1,0.001);  

 th.join();
}
