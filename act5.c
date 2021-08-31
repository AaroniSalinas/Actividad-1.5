// Desarrollar el código de paralelización para resolver de forma numérica ∫21dxx considerando 1×108 puntos en el intervalo de integración. Mostrar sus resultados en Github, junto con el número óptimo de threats para este ejercicio

#include<stdio.h>
#include "omp.h"

#define NUM_THREADS 160

static long num_pasos = 100000000;

double paso;



void main()
{
    printf("NUM_THREADS = %i\n",NUM_THREADS);
    int i;
    int nthreads;
    double pi;
    double sum[NUM_THREADS];
    double t1,t2,tiempo;
    double paso=2.0/num_pasos;
    omp_set_num_threads(NUM_THREADS);
    const double startTime = omp_get_wtime();
    //programa en paralelo omp
    {
        int i;
        int id;
        int nthrds;
        double x;
        
        id = omp_get_thread_num();
        nthrds = omp_get_num_threads();

        if (id==0){
            nthreads = nthrds;
        }
        
        for (i = 50000000, sum[id] = 0.0;  i < num_pasos; i = i+nthrds){
            x = (i+0.5)*paso;
            sum[id] += 1.0/(x);
        }

    }

    for (i=0,pi=0.0; i<nthreads; i++){
        pi+=sum[i]*paso;
    }

    const double endTime = omp_get_wtime();
    tiempo=t2-t1;
    printf("pi = (%lf)\n",pi);
    printf("tomo = (%lf) segundos\n",(endTime - startTime));
}