#include<iostream>
//#include<conio.h>
#include <stdio.h>
using namespace std;

int main(void)
{
    float a[10][10], b[10], x[10], y[10];
    int n = 0, m = 0, i = 0, j = 0;
    cout << "Digite o tamanho da matriz 2d (matriz quadrada) : ";
    cin >> n;
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            cout << "Digite os valores no :(" << i << ", " << j << ") ";
            cin >> a[i][j];
        }
    }
    cout << "\n Insira os valores no lado direito da equação \n";
    for (i = 0; i < n; i++)
    {
        cout << "Digite os valores no :(" << i << ", " << j << ") ";
        cin >> b[i];
    }
    cout << "Insira valores inicias de x\n";
    for (i = 0; i < n; i++)
    {
        cout << "Digite valores no :(" << i<<"):";
        cin >> x[i];
    }
    cout << "\nDigite o nº de iteração : ";
    cin >> m;
    while (m > 0)
    {
        for (i = 0; i < n; i++)
        {
            y[i] = (b[i] / a[i][i]);
            for (j = 0; j < n; j++)
            {
                if (j == i)
                    continue;
                y[i] = y[i] - ((a[i][j] / a[i][i]) * x[j]);
                x[i] = y[i];
            }
            printf("x%d = %f    ", i + 1, y[i]);
        }
        cout << "\n";
        m--;
    }
    return 0;
}
