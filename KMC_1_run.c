#include <stdio.h>
#include <stdlib.h>
# include <time.h>
# include <math.h>


int main() {

double Wa;
double Wd;
double n;   /* Probability number to decide whether or not to perform an action at a particular site */
int rA=1;
int rD=2;
int i;
int j;
int M;
int Lx=100;
int Ly=100;
int N=Lx*Ly;
int rAt;
int rDt;
int Rt;
int Rx;    /*Random Rumbering in X Axis */
int Ry;	   /*Random Rumbering in Y Axis */
srand ( time(NULL) );
int T;

/* Declaration of arrays t and theta and space allocation through mallock */
double *Theta;
double *t;
double *R;


t=(double*)malloc(10000000*sizeof(double));
Theta=(double*)malloc(10000000*sizeof(double));
R=(double*)malloc(10000000*sizeof(double));
double tsum;


/* Dynamical Heirarchy for Transition Probabilities */ 
if(rA>rD)
	{
		Wa=1.0;
		Wd=rD/rA;
	}
else
	{
		Wd=1.0;
		Wa=rA/rD;
	}

/* Creating a Cubic Lattice */

int site[Lx][Ly];

/* Initially No adsorption is present */
for (i=0; i<Lx; i++)
{
	for (j=0;j<Ly;j++)
	{
	site[i][j]=0;
	}
}

/* Occupied Sites */

/* The Real game begines */
 /*
Steps of the game
1) Finding Occupancy thetaby search algorithm in Our Array matrix
2) Finding rAi and rDi
3)Hence,finding Ri
4)time increment=logU/Ri
5) Repeat

 Till now, 
1)We have given some Average adsorption and desorption rates rA and rD. 
2) Also, We have devised a techniquefor Dynamical Heirarchy for Transition Probabilities wA and wD 
3) We have defined a lattice arrangement for the surface in a matrix
4) Initially occupancy has been set to zero
5)  
*/
M=0;
t[0]=0;
T=0;
i=0;
Theta[i]=0.0;

while ( t[i]<3)
{

Rx=rand()%Lx;
Ry=rand()%Ly;

/* Whether the site contains an atom or not */
if ( site[Rx][Ry]==0)  /* No atom*/
{
n=(double)(rand()%1000);
n=n/1000;
	if (n<=Wa)
	{	
		site[Rx][Ry]=1;
		n=(double)(rand()%1000);
		n=n/1000.0;
		while(n==0 || n==1)
			{
			n=(double)(rand()%1000);
		        n=n/1000.0;
			}
		M=M+1;
	}		
		i=i+1;
		
		Theta[i]=M/N;
		R[i]=(rA*(1-Theta[i]))+(rD*Theta[i]);
		t[i]=t[i-1]-(log(n)/(R[i]));
		
	
T=T+1;
}

else
	{

	n=(double)(rand()%1000);
	n=n/1000;
	if (n<=Wd)
	{
		
		site[Rx][Ry]=0;
		n=(double)(rand()%1000);
		n=n/1000.0;
		while(n==0 || n==1)
			{
			n=(double)(rand()%1000);
		        n=n/1000.0;
			}
		M=M-1;
	}		
	
		i=i+1;
		
		Theta[i]=M/N;
		R[i]=(rA*(1-Theta[i]))+(rD*Theta[i]);
		t[i]=t[i-1]-(log(n)/(R[i]));
		
	
	T=T+1;

	

	}
}
/* Writing in the file */
FILE *PTR=fopen("Plot.txt","w");

if (PTR==NULL)
{
printf("\nUnable to create the file\n");
}
else
{
printf("\nfile opened successfully\n");
}

/*Writing the Theta vs Time arrray */
	for(j=0;t[j]<3;j++)
	{
			printf(" %f %f \n", t[j], Theta[j]);
	}


fclose(PTR);
		

free (t);
free (Theta);
free(R);
                                       
return 0;

}
