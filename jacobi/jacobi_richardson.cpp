#include <iostream>
#include <math.h>
/*Se a matriz de entrada não convergir, o progama vai rodar infinatamente sem parar!!! Coloque um matriz válida para testes, exemplo:

n=2
a[0,0]=4
a[0,1]=2
a[1,0]=1
a[1,1]=3
b[0,0]=1
b[1,0]=-1
e=0.001

*/
using namespace std;
int main()
{
    int N;
    int i;
    int j;
    int l=0;
    cout<<"Qual o tamanho da matriz quadrada:" << endl;
    cin>>N;
    double A[N][N],b[N][1],x[N][1],T[N][1],epsilon,k;
    cout<<"[A]*[x]=[b]"<<endl;
    cout<<"Diga os valores da Matriz A:"<<endl;
    for(i=0;i<N;i++)
    for(j=0;j<N;j++)
    {
        cout<<"A["<<i<<","<<j<<"] = ";
        cin>>A[i][j];
    }
    cout<<"Diga os valores de b:"<<endl;
    for(j=0;j<N;j++)
    {
        cout<<"b[0,"<<j<<"] = ";
        cin>>b[0][j];
    }
    cout<<"Entre a taxa de erro(epsilon) desejado:" <<endl;
    cin>>epsilon;
    for (i=0;i<N;i++)
        T[i][0]=0;

    while (l!=N)
    {
        l=0;
        for (i=0;i<N;i++)
        {
            x[i][0]=(1/A[i][i])*(b[i][0]);
            for (j=0;j<N;j++)
            {
                if (j!=i)
                x[i][0]=x[i][0]-(1/A[i][i])*(A[i][j]*T[j][0]);
            }
        }
        for(i=0;i<N;i++)
        {
            k=fabs(x[i][0]-T[i][0]); // fabs = módulo
            if (k<=epsilon)
            {
                l=l+1;
            }
        }
    for (i=0;i<N;i++)
        T[i][0]=x[i][0];
    }
    cout << "Vetor X encontrado: " << endl;
    for (i=0;i<N;i++)

        cout<<"x"<<i+1<<"="<<x[i][0]<<endl;

    return 0;
}
