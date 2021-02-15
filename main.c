#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

float a = 0.0;
float b = 2.0 * M_PI;
float total_area = 0.0;
float height = 0.0;

float function_1(float x);

float function_2(float x);

void *hello_world(void *thread_parameter)
{
    int trapezoids_per_thread = (int)(size_t)thread_parameter;

    printf("Trapézios na thread: %i \n", trapezoids_per_thread);

    for (int i = 1; i < trapezoids_per_thread; i++)
    {
        float x_i = a + i * height;
        total_area += function_2(x_i);
    }
    total_area = height * total_area;
}

int main(int argc, char *argv[])
{
    printf("Número de threads: %s \n", argv[1]);
    printf("Número de trapézios: %s \n", argv[2]);

    printf("\n");

    int number_of_threads = atoi(argv[1]);
    int number_of_trapezoids = atoi(argv[2]);

    // Validate inputs

    pthread_t threads[number_of_threads];
    int status;
    void *thread_return;

    int trapezoids_per_thread = number_of_trapezoids / number_of_threads;

    int module = number_of_trapezoids % number_of_threads;

    height = (b - a) / number_of_trapezoids;

    total_area = (function_2(a) + function_2(b)) / 2;

    for (int i = 0; i < number_of_threads; i++)
    {
        printf("Criando thread #%i \n", i + 1);
        status = pthread_create(&threads[i], NULL, hello_world, (module == 1 && i == 0) ? (void *)(size_t)trapezoids_per_thread + 1 : (void *)(size_t)trapezoids_per_thread);

        if (status != 0)
        {
            printf("Erro na criação da thread. Codigo de erro: %i \n", status);
            return 1;
        }
    }

    for (int i = 0; i < number_of_threads; i++)
    {
        printf("Esperando thread #%i finalizar \n", i + 1);
        pthread_join(threads[i], &thread_return);
        printf("Thread #%i finalizada \n", i + 1);
    }

    printf("\n");

    printf("Area da funcao: %.2e \n", total_area);

    return 0;
}

float function_1(float x)
{
    return 5.0;
}

float function_2(float x)
{
    return sin(2.0 * x) + cos(5.0 * x);
}