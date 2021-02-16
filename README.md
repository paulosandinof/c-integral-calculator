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
    - b = 5;
    - real result: 1.7577
    - result by trapezoidal rule with 7 trapezoids: 1.74833577215
    - result by trapezoidal rule with 15 trapezoids: 1.75561915023
    - result by trapezoidal rule with 20 trapezoids: 1.75651586878

- f2:
    - f(x) = ln(x); 
    - a = 1;
    - b = 5;
    - real result: 4.0472
    - result by trapezoidal rule with 7 trapezoids: 4.02569188650
    - result by trapezoidal rule with 15 trapezoids: 4.04246248429
    - result by trapezoidal rule with 20 trapezoids: 4.04452725506