Foi utilizado o GCC 9.3.0 no sistema operacional Ubuntu 20.04

Para compilar o programa, execute:
```
gcc main.c -lm -pthread
```
Para executar o programa, execute o comando abaixo substituindo os valores de *t* e *n* pelo número de threads e de trapézios desejados, respectivamente:
```
./a.out t n
```

Resultados de testes com algumas funções:
- f1: 
    - f(x) = log(x); 
    - a = 1;
    - b = 10;
    - real result: 6.0913
    - result by trapezoidal rule with 120 trapezoids: 6.091166

- f2:
    - f(x) = ln(x); 
    - a = 1;
    - b = 10;
    - real result: 14.026
    - result by trapezoidal rule with 200 trapezoids: 14.025699
