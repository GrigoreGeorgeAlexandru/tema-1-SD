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
void countsortforradix (long long int v[],int n,int maxi,int p,int baza)
{

    int countnr[baza]={0},i;
long long int* output=new  long long int [n+1];
for(i=1;i<=n;i++)
    {
        countnr[(v[i]/p)%baza]++;}

for(i=1;i<baza;i++)
    countnr[i]+=countnr[i-1];
    for (i = n; i>=1;i--)
    {
        output[countnr[(v[i]/p)%baza]] = v[i];
        countnr[(v[i]/p)%baza]--;
    }
for(i=1;i<=n;i++)
    v[i]=output[i];
delete[] output;
}
int getMax(long long int v[], int n)
{
    int mx = v[1];
    for (int i = 2; i <= n; i++)
        if (v[i] > mx)
            mx = v[i];
    return mx;
}
void radixsort (long long int v[],int n,int maxi)
{ int baza=10;
    int m = getMax(v, n);
for(int p=1;m/p>0;p*=baza)
    countsortforradix(v,n,maxi,p,baza);
}

void merges(long long int v[],int l,int m,int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 =  r - m;
    int L[n1], R[n2];

     for (i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (j = 0; j < n2; j++)
        R[j] = v[m + 1+ j];
        i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            v[k] = L[i];
            i++;
        }
        else
        {
            v[k] = R[j];
            j++;
        }
        k++;
    }
  while (i < n1)
    {
        v[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        v[k] = R[j];
        j++;
        k++;
    }

}
void mergesort(long long int v[],int l,int r)
{
    if(l<r)
    {
        int m=l+(r-l)/2;
        mergesort(v,l,m);
        mergesort(v,m+1,r);
        merges(v,l,m,r);
    }
}
void swapi( long long int& e1,long long int& e2)
{
    int aux = e1;
    e1 = e2;
    e2 = aux;
}
int pivot (long long int v[],int mini,int maxi)
{
    int pivot = v[maxi];
    int i =mini;

    for (int j = mini; j <= maxi - 1; j++)
    {

        if (v[j] < pivot)
        {

            swapi(v[i], v[j]);  i++;
        }
    }
    swapi(v[i],v[maxi]);
    return i;
}
int pivot2(long long int v[],int mini,int maxi)
{

}
void quicksort(long long int v[],int mini,int maxi)
{
    if(mini<maxi)
    {
        int piv=pivot(v,mini,maxi);
        quicksort(v, mini,piv - 1);
        quicksort(v, piv + 1, maxi);
    }



}



int main()
{int t,n,maxi;
ifstream f("test.txt");
f>>t;
int i;
fnct functions[]={bubblesort,
    countsort,radixsort,mergesort,quicksort};
string fctname[]={"bubblesort",
"countsort","radixsort","mergesort","quicksort"};
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


   sort(v2+1,v2+n+1);


    auto stop = high_resolution_clock::now();


    auto duration = duration_cast<microseconds>(stop - start);

    cout << "functia din c++ a durat: "
         << duration.count() << " microseconds" << endl;
         int flag=test(v2,n);
         if(flag==1)
            cout<<"numerele au fost sortate corect"<<endl;
         else
            cout<<"numerele nu au fost sortate corect"<<endl;

for(int w=0;w<5;w++)
       {for(int j=1;j<=n;j++)
        v2[j]=v1[j];auto start2 = high_resolution_clock::now();

//sort(v1+1,v1+n+1);
if(w>=3)functions[w](v2,1,n);
    else
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
