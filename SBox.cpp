#include "header.h"

long var;
long NF = 0, DF = 0;
long Lin_Br, Diff_Br;

vector <vector <long> > CO_ORDINATE;
vector <vector <long> > COMPONENT;
vector <vector <long> > Bin_SBox;
vector <long> S_Box;
vector <vector <long> > DDT;
vector <long> Comp_Deg;
long Bin_dec_1(vector <long> V)
{
    long j=0;
	long Dec = 0;
	for(long i=7; i>=0 ; i--)
	{
		Dec = Dec + ( V[i] * pow(2,j) );
		j++;
	}
	
return Dec;	
	
}

vector <long> Dec_bin(long m)
{
	long rem=0;
	vector <long> z(var, 0);
	long i= var-1;
  	 while(m != 0) 
	 {
               
		rem = m%2;
        m = m/2;
        z[i]=rem;
        i--;
    }
return z;
}
long Dot_prod(long a, long b)
{
	long dot = 0, n;
	vector <long> x;
	vector <long> y;
	x = Dec_bin(a);
	y = Dec_bin(b);
	n = x.size();
	for(long i=0; i< x.size(); i++ )
	{
		dot = dot + (x[i] * y[i]);
	}
	
	dot = dot % 2;
return dot;
}

long Xor(long x, long y)
{
	return x^y ;
}
long Hamm_wt(vector <long> x)
{
	long wt = 0;
	for(long i=0; i < x.size(); i++)
	{
		wt = wt + x[i];
	}
return wt;	
}
long Comp_fun(long n)
{
  long size, k, sum;
  vector <long> x;
  vector <long> y;
  vector <long> z;
  fstream out;
  size = pow(2, n);	
  for(long i=0; i < size; i++)
  {
	  x = Dec_bin(i);
	  for(long j=0; j < Bin_SBox.size(); j++)
	   {
		  y = Bin_SBox[j];
		  sum = 0;
		  for(long k=0; k < y.size(); k++)
		  {
			 sum = sum + (x[k] * y[k]);
	  	  }
		   sum = sum % 2;
		   z.push_back(sum);
		   y.clear();
	   }
	   COMPONENT.push_back(z);
	   z.clear();
	   x.clear();
   }	
    
 return 0;  
}
vector <long> Comp(vector <long> x)
{
	vector <long> z;
	long k;
	for(long i=0; i < x.size(); i++)
	{
		k = (x[i] + 1) % 2;
		z.push_back(k);
	}
return z;	
	
}
long is_Bijective(long n)
{
	vector <long> x;
	long a, count = 0;
	long size = pow(2, n);
	for(long i=1; i < COMPONENT.size(); i++)
	{
		x = COMPONENT[i];
		a = is_Balanced(x, n);
		 if (a == 1)
		      count++;
	   	x.clear();
	}
	if (count == size-1)
	   return 1;
	else 
	   return 0;   
	
}
long Dec_Bin_SBox(vector <long> Z, long n)
{
	vector <long> x;
	for(long i=0; i < Z.size(); i++)
	{
		x = Dec_bin(Z[i]);
		Bin_SBox.push_back(x);
		x.clear();
	}
}
long Nonlinearity(long n)
{
	long max, j=0, k;
	long sum = 0, nl, avg_nl;
	long NL, min_NL;
	vector <long> x;
	vector <long> z;
	vector <long> y;
	max = 0;
		
	for(long i=1; i < COMPONENT.size(); i++)
	{
		x = COMPONENT[i];
		z = Walsh_spectra(x, n);
	   for(long j=0; j < z.size(); j++)
	   {
		  k = abs(z[j]);
		  if (max < k)
		  {
		  	 max = k;
		  	 NF = 1;
		  }
		  else if(max == k)
		  {
		  	 NF++;
		  }
		}
		x.clear();
		z.clear();
		
	}
    NL = pow(2, n-1) - max/2;

return NL;
} 
long Diff_uniformity(long n)
{
	long max = 0;
	long diff;
	vector <long> D;
	for(long i=1; i < DDT.size(); i++)
	{
		D = DDT[i];
		for(long j=0; j < D.size(); j++)
		{
			diff = D[j];
			if(max < diff)
			{
				max = diff;
				DF = 1;
			}
			else if(max == diff)
			{
				DF++;
			}
			  
		}
		D.clear();
	}
		
	
 return max; 
}
long AD()
{
	long min_wt = 10, wt;
	cout<<endl;
	for(long i=1; i < COMPONENT.size(); i++)
	{
		wt = Alg_deg(COMPONENT[i], var);
		Comp_Deg.push_back(wt);
		if(min_wt > wt)
		  min_wt = wt;
	}
	cout<<endl;
return min_wt;	
	
}
long Const_DDT()
{
	long size, counter, diff_br;
	long wt1, wt2;
	long min = 20;
	long k1, k2, k3, Diff;
	vector <long> a;
	vector <long> b;
	vector <long> D, D1;
	vector <long> z;
	size = pow(2, var);
	for(long a=0; a < size; a++)
	{
		z = Dec_bin(a);
		wt1 = Hamm_wt(z);
		z.clear();
		for(long b = 0; b < size; b++)
		{
			counter = 0;
			z = Dec_bin(b);
			wt2 = Hamm_wt(z);
			for(long x = 0; x < size; x++)
			{
				k1 = S_Box[x];
				k2 = Xor(x, a);
				k3 = S_Box[k2];
				Diff = Xor(k1, k3);
				if(Diff == b)
				   counter++;	
			}
			D.push_back(counter);
		}
		DDT.push_back(D);
		D.clear();
	
	}
	for(long i=1; i < DDT.size(); i++)
	{
		D =DDT[i];
		a = Dec_bin(i);
		for(long j=1; j < D.size(); j++)
		{
			if(D[j] != 0)
			{
				b = Dec_bin(j);
				wt1 = Hamm_wt(a);
				wt2 = Hamm_wt(b);
				diff_br = wt1 + wt2;
			}
			if(min > diff_br)
			{
				min = diff_br;
			}
				
		}
		D.clear();
	}
	Diff_Br = min;
return 	0; 
}

long Cord_fun(long n)
{
	long k;
	vector <long> x;
	for(long i=0; i < n ; i++)
	{
		for(long j=0; j < Bin_SBox.size(); j++)
		{
			k = Bin_SBox[j][i];
			x.push_back(k);
			
		}
		CO_ORDINATE.push_back(x);
		x.clear();
	}
return 0;	
}
long Opp_Fixed_point()
{
	long n, c = 0;
	vector <long> x;
	vector <long> y;
	vector <long> z;
	//cout<<"hello";
	for(long i=0; i < Bin_SBox.size(); i++)
	{
	    x = Bin_SBox[i];
	    y = Dec_bin(i);
		z = Comp(y); 
		if(x == z)
		  c++;
		
		x.clear();
		y.clear();
		z.clear();   
		
		
	}
return c;	
}
long Fixed_point()
{
	long n, c = 0;
	for(long i=0; i < S_Box.size(); i++)
	{
		if(S_Box[i] == i)
		   c++;
	}
return c;	
}
long Print_SBox(vector <long> Z, long n)
{
	long NL, DU, flag, fp, opp_fp, ad;
	fstream out;
	out.open("out.txt", ios::app);
	S_Box = Z;
   	Dec_Bin_SBox(S_Box, n);
   	Cord_fun(n);
   	Comp_fun(n);
   	flag = is_Bijective(n);
   	NL = Nonlinearity(n);
   	DU = Diff_uniformity(n);
   	fp = Fixed_point(); 
	opp_fp = Opp_Fixed_point();  
	ad = AD();
   	for(long j=0; j < S_Box.size(); j++)
   	  {
   	  	  cout<<S_Box[j]<<" ";
   	  	  out<<S_Box[j]<<" ";
   	  	  
	  }
	cout<<endl;
	out<<endl;

	cout<<"Bijective: "<<flag<<" ";
	out<<"Bijective: "<<flag<<" ";
	
	cout<<" NL: "<<NL<<" ";
   	//cout<<"NF: "<<NF<<" ";
   	//cout<<"Linear Bran: "<<Lin_Br<<" ";
   
   	
   	out<<"NL: "<<NL<<" ";
   	//out<<"NF: "<<NF<<" ";
   	//out<<"Linear Bran: "<<Lin_Br<<" ";
   	  	
   	cout<<"DU: "<<DU<<" ";
	//cout<<"DF: "<<DF<<" ";
	//cout<<"Diff Bran: "<<Diff_Br<<endl;
	
	out<<"DU: "<<DU<<" ";
	//out<<"DF: "<<DF<<" ";
	//out<<"Diff Bran: "<<Diff_Br<<endl;
	
	cout<<"No of fixed points: "<<fp<<endl;
   	out<<"No of fixed points: "<<fp<<endl;
   	
   	cout<<"Opposite fixed points: "<<opp_fp<<" ";
   	out<<"Opposite fixed points: "<<opp_fp<<" ";
   	
  	cout<<"Alg deg: "<<ad<<endl;
	out<<"Alg deg: "<<ad<<endl;   
	
	cout<<"\n-------------------------------\n";
	out<<"\n---------------------------------------\n"<<endl; 
   
   	S_Box.clear();
   	Bin_SBox.clear();
   	COMPONENT.clear();
   	//LAT.clear();
   	DDT.clear();
   	CO_ORDINATE.clear();
return 0;  	
}
long S_Box_eval()
{
	long n, m, k, size, dec, var;
	long sum, c= 0;
	char ch;
	vector <vector <long> > CF;
	vector <vector <long> > Init;
	vector <long> z;
	vector <long> y;
	ifstream out;
	vector <vector <long> > X_S;
	out.open("input.txt", ios::in);
	cout<<"Enter size of n \n";
	cin>>n;
	cout<<"Enter size of m \n";
	cin>>m;
	size = pow(2, n);
	var = n;
	
    while(out>>k)
    {
    	z.push_back(k);
    	     
    }
    Print_SBox(z, n);

	 
   cout<<"\n Execution completed";
return 0;	
}
