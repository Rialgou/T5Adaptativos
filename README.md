# T5Adaptativos
Heurísticas Greedy para el 2-Optimality Consensus Problem

## Integrantes
- Vanessa Suazo
- Richard González
- Vicente Cser

## Compilacion
```bash
make
```
### dependencias:
- GNU make
- g++

## Modo de uso
```bash
./grasp.out -i <instancia-problema> -t <tiempo-maximo-en-segundos> [probabilidad]
```
- para instancia-problema escribe la ruta donde se encuentra el dataset
- para el tiempo maximo ingresa un valor númerico, este estara representado en segundos
- para probabilidad ingresar un entero del 0 al 100, que definira la posibilidad de elegir un nucleotido aleatorio en el algoritmo greedy
### Tests
```bash
make test
```



