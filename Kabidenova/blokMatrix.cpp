#include <iostream>
#include <cstdlib> 
#include <thread>
#include<mutex>
#define N 6
#define n 6

std::mutex mu;
int a[N][N];
int b[N][N];
int c[N][N];

void blok(int i, int indexEnd){

	for (int i; i < indexEnd; i++) {
		for (int j=0; j < N; j++) {
			c[i][j] = 0;
			for (int k=0; k < N; k++) {
				c[i][j] = c[i][j] + a[i][k]*b[k][j];
			}
		}
	} 
}


int main(){
	std::cout << "A-matrix: " << std::endl;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			std::cin >> a[i][j];
		}
	}
	for (int i = 0; i < N; i++){
		std::cout << i << "-th line" << std::endl;
		for (int j = 0; j < N; j++){
			std::cout << a[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	
	std::cout << "B-matrix" << std::endl;
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			std::cin >> b[i][j];
		}	
	}
	for (int i = 0; i < N; i++){
		std::cout << i << "-th line" << std::endl;
		for (int j = 0; j < N; j++){
			std::cout << b[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	std::thread t1(blok, 0, 2);
	std::thread t2(blok, 2, 4);
	std::thread t3(blok, 4, 6);	
	//std::thread t4(blok, 6, 8);
	
	t1.join();
	t2.join();
	t3.join();
	//t4.join();
	
	for (int i = 0; i < N; i++){
		std::cout << i << "-th line" << std::endl;
		for (int j = 0; j < N; j++){
			std::cout << c[i][j] << '\t';
		}
		std::cout << std::endl;
	}
	return 0;
	
}