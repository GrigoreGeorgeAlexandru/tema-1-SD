#include <iostream>
#include <fstream>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;
typedef void (*fnct) (long long int v[],int n,int m);

int test(long long int v[],int n)
{
    int i,flag=1;
    for (i=1; i<n; i++)
        if(v[i]>v[i+1])
    {flag=0;
    break;

    }

    return flag;
}

void bubblesort(long long int v[],int n,int maxi)
{
    int i,j;
    for (i=1; i<n; i++)
        for(j=1; j<=n-i; j++)
            if(v[j]>v[j+1])
           {
               int aux = v[j];
    v[j] = v[j+1];
    v[j+1] = aux;
           }

}

void countsort (long long int v[],int n,int maxi)
{

    int countnr[maxi+1]={0},i;
long long int* output=new  long long int [n+1];
for(i=1;i<=n;i++)
    {
        countnr[v[i]]++;}

for(i=1;i<=maxi;i++)
    countnr[i]+=countnr[i-1];
    for (i = 1; i<=n;i++)
    {
        output[countnr[v[i]]] = v[i];
        countnr[v[i]]--;
    }
for(i=1;i<=n;i++)
    v[i]=output[i];
delete[] output;
}
void countsortforradix (long long int v[],int n,int maxi,int p)
{

    int countnr[10]={0},i;
long long int* output=new  long long int [n+1];
for(i=1;i<=n;i++)
    {
        countnr[(v[i]/p)%10]++;}

for(i=1;i<=maxi;i++)
    countnr[i]+=countnr[i-1];
    for (i = 1; i<=n;i++)
    {
        output[countnr[(v[i]/p)%10]] = v[i];
        countnr[(v[i]/p)%10]--;
    }
for(i=1;i<=n;i++)
    v[i]=output[i];
delete[] output;
}
int getMax(int v[], int n)
{
    int mx = v[0];
    for (int i = 1; i < n; i++)
        if (v[i] > mx)
            mx = v[i];
    return mx;
}
void radixsort (long long int v[],int n,int maxi)
{
    int m = getMax(v, n);
for(int p=1;m/p>0;p*=10)
    countsortforradix(v,n,maxi,p);
}




int main()
{int t,n,maxi;
ifstream f("test.txt");
f>>t;
int i;
fnct functions[]={bubblesort,countsort,radixsort};
string fctname[]={"bubblesort","countsort","radixsort"};
for(i=1;i<=t;i++)
{
    f>>n>>maxi;
  long long int* v1=new  long long int [n+1];
  long long int* v2=new long long int [n+1];
   auto generator = [maxi]() -> int { return rand()%(maxi+1); };
    generate(&v1[1],&v1[n+1],generator);
    cout<<"N="<<n<<"  M="<<maxi<<endl;
    for(int j=1;j<=n;j++)
        v2[j]=v1[j];

   auto start = high_resolution_clock::now();


   sort(v1+1,v1+n+1);


    auto stop = high_resolution_clock::now();


    auto duration = duration_cast<microseconds>(stop - start);

    cout << "functia din c++ a durat: "
         << duration.count() << " microseconds" << endl;
         int flag=test(v1,n);
         if(flag==1)
            cout<<"numerele au fost sortate corect"<<endl;
         else
            cout<<"numerele nu au fost sortate corect"<<endl;

for(int w=0;w<3;w++)
       {auto start2 = high_resolution_clock::now();

//sort(v1+1,v1+n+1);

   functions[w](v2,n,maxi);



   auto stop2 = high_resolution_clock::now();


  auto duration2 = duration_cast<microseconds>(stop2 - start2);

    cout <<"functia "<<fctname[w]<<" a durat:"
         << duration2.count() << " microseconds" << endl;
          int flag=test(v2,n);
         if(flag==1)
            cout<<"numerele au fost sortate corect"<<endl;
         else
            cout<<"numerele nu au fost sortate corect"<<endl;
       }
delete[] v1;
delete[] v2;}

return 0;
}
