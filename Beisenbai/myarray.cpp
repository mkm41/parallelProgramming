#include <iostream>
#include <thread>
#include<chrono>
using namespace std;

void dowork(int m){
	int arr[9]={9,8,7,6,5,4,3,2,1};
/*	for (int i=0; i < n; i++)
    {
    	cout<<"["<<i<<"]="<<"\t";
        cin >> arr[i];
    }*/
    cout<<"Array elements: ";
    for (int i=0; i < 9; i++)
    {	cout << arr[i] << " ";}
    cout<<endl;
    for(int i=0;i<9;i++){
		if(m==arr[i]){
			cout<<"we found "<<m<<" in array elements"<<endl;
	        break;
		}
	}
}

int main(){
	thread th(dowork,4);
	
	th.join();
}
