#include "header.h"

using namespace std;


int main() 
{
	int ch;
	cout<<"Enter your choice:\n";
	cout<<"1. Analyzing Boolean function Crypto Proerties \n";
	cout<<"2. Analyzing S-Box Crypto Properties\n";
	cin>>ch;
	 clock_t t; 
	switch(ch)
	{
		case 1: 
		   t = clock(); 
           Boolean_func();
           t = clock() - t; 
           break;
		case 2:
		     S_Box_eval();
			 break;   
		         
		
	}	
	double time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds 
	cout<<"Time taken by function in sec: "<<time_taken;
	cout<<endl; 
	return 0;
}
