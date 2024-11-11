#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define FILENAME "punkte.dat"

void print_vector(int *v, int n);
int* read_vector(FILE *inputfile, int n);
double Lagrange(int n, int k,int value);
double Calculate(int n, int x);
int* y_werte;
int* x_werte;

int main() {

    int point;
    int counter = 0;
    FILE* ptr;
    char c;

    ptr = fopen(FILENAME,"r");

    c = fgetc(ptr);

    while(c != EOF)
    {
        if(c == '\n')
        {
            counter++;
        }
        c = fgetc(ptr);
    }

    rewind(ptr);

    printf("%d\n",counter);

    x_werte = malloc(counter * sizeof(int));
    y_werte = malloc(counter*sizeof(int));
    int * stützwerte = read_vector(ptr,counter*2);

    for(int i = 0; i<counter;i++)
    {
        x_werte[i] = stützwerte[i+1*i];
        y_werte[i] = stützwerte[1+2*i];
    }

    printf("X-werte\n");
    print_vector(x_werte,counter);
    printf("y-werte\n");
    print_vector(y_werte,counter);
    printf("\n");
    printf("Please enter point to calculate:\n");
    scanf("%d", &point);

    /*double IVec[counter];
    for (int i = 1; i <= counter; i++)
    {
        IVec[i] = Calculate(counter,i);
    }
    double IMat[counter][counter];
    for (int i = 0; i <counter;i++)
    {
        for (int j = 0; j < counter; ++j) {
            IMat[i][j] = pow(i,counter-1-(1*j));
        }
    }

    for (int i = 1; i < counter; ++i) {
        for (int j = 0; j < counter; ++j) {
            printf("%lf ",IMat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < counter; ++i) {
        printf("%lf\n",IVec[i]);
    }*/
    printf("Result =====> f(%d) = %5.4lf\n",point, Calculate(counter, point));
    printf("\n");

    return 0;
}

int* read_vector(FILE *inputfile, int n)
{
    int i;

    int *b;
    b = (int *) malloc(n * sizeof(double));
    if (b == NULL) return NULL;


    for (i = 0; i < n; i++ )
    {
        fscanf(inputfile,"%d", &(b[i]) );
    }
    print_vector(b, n);

    return b;
}

void print_vector(int *v, int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        printf("%d", v[i]);
        printf("\n");
    }
}

double Lagrange(int n, int k, int val)
{
    double result = 1;
    for (int i = 0; i < n; i++)
    {
        if (i!=k)
            result = result * (double)((val - x_werte[i]) / (x_werte[k] - x_werte[i]));
    }
    return result;
}

double Calculate(int n,int x)
{
    double intPolasyon = 0;
    double *L = (double*)malloc(sizeof(double)*n);
    for (int i = 0; i < n; i++)
    {
        L[i] = Lagrange(n, i, x);
        intPolasyon += y_werte[i] * L[i];
        printf("L(%d) = %5.3lf\n", i, L[i]);
    }

    printf("\n");
    return intPolasyon;
}



