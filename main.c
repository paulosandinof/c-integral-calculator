#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <unistd.h>

double a = 1.0;
double b = 10.0;
int number_of_trapezoids;
int number_of_threads;

double *thread_return_array;

double f(double x);

void *calculate_area(void *params)
{
    int thread_number = (int)(size_t)params;

    double height = (b - a) / number_of_trapezoids;
    int trapezoids_per_thread = number_of_trapezoids / number_of_threads;

    double local_a = a + (thread_number * trapezoids_per_thread * height);
    double local_b = local_a + trapezoids_per_thread * height;

    if ((thread_number == (number_of_threads - 1)) && ((number_of_trapezoids % number_of_threads) != 0))
    {
        trapezoids_per_thread += number_of_trapezoids % number_of_threads;
        local_b = b;
    }

    printf("Thread %i local a: %f \n", thread_number, local_a);
    printf("Thread %i local b: %f \n", thread_number, local_b);

    printf("Trapézios na thread: %i \n", trapezoids_per_thread);

    double total_area = (f(local_a) + f(local_b)) / 2;

    for (int i = 1; i < trapezoids_per_thread; i++)
    {
        double x_i = local_a + i * height;
        total_area += f(x_i);
    }

    total_area = height * total_area;

    printf("Total area: %f \n", total_area);

    thread_return_array[thread_number] = total_area;

    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    printf("Número de threads: %s \n", argv[1]);
    printf("Número de trapézios: %s \n", argv[2]);

    printf("\n");

    number_of_threads = atoi(argv[1]);
    number_of_trapezoids = atoi(argv[2]);

    // Validate inputs

    pthread_t threads[number_of_threads];
    int status;
    void *thread_return;

    thread_return_array = malloc(sizeof(double) * number_of_threads);

    for (int i = 0; i < number_of_threads; i++)
    {
        printf("Criando thread #%i \n", i);
        status = pthread_create(&threads[i], NULL, calculate_area, (void *)(size_t)i);

        if (status != 0)
        {
            printf("Erro na criação da thread. Codigo de erro: %i \n", status);
            return 1;
        }
    }

    for (int i = 0; i < number_of_threads; i++)
    {
        printf("Esperando thread #%i finalizar \n", i);
        pthread_join(threads[i], &thread_return);
        printf("Retorno da thread %i: %f \n", i, thread_return_array[i]);
        printf("Thread #%i finalizada \n", i);
    }

    printf("\n");

    double sum_of_areas = 0.0;

    for (int i = 0; i < number_of_threads; i++)
    {
        sum_of_areas += thread_return_array[i];
    }

    printf("Area da funcao: %f \n", sum_of_areas);

    free(thread_return_array);

    return 0;
}

double f(double x)
{
    // return log10(x);
    return log(x);
    // return 5.0;
    // return sin(2.0 * x) + cos(5.0 * x);
}