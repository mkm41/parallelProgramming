#include<stdio.h>
#include<conio.h>
#include<iostream>
#include<thread>
double f(double x)

void main()
{
int i,n;
double  a,b;
 
double x=0, s=0, xb=0;
double dx;
 
    cout<< "vvedite a";
     cin>>a;
     cout<< "vvedite b";
     cin>>b;
     cout<<"chislo otrezkov";
     cin>>n;
     
      dx=(b-a)/n;
          cout<<dx <<' ';
          xb=a+dx/2;
          cout<<xb<<' ';
 
           for(i=0;i<=n-1;i++)
           {
           x=xb+i*dx; s=s+f(x)*dx;
           }
           
           cout<<s;
            thread th(integral);  

           th.join();
 }

