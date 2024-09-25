#include <stdio.h>
#include <stdlib.h> #include <pthread.h> #include <time.h>

#deﬁne SIZE 100
#deﬁne THREAD_COUNT 2

int array[SIZE];
int max_values[THREAD_COUNT] = {0};

// Função que será executada pelas threads void* ﬁnd_max(void* arg) {
int thread_id = *(int *)arg;
int start = thread_id * (SIZE / THREAD_COUNT);
int end = (thread_id + 1) * (SIZE / THREAD_COUNT);

// Inicializa o maior valor local int local_max = array[start];

for (int i = start; i < end; i++) {
  if (array[i] > local_max) {
    local_max = array[i];
  }
}
max_values[thread_id] = local_max;
pthread_exit(NULL);
}

int main() {
  srand(time(NULL));

  // Preencher o vetor com números aleatórios for (int i = 0; i < SIZE; i++) {
  array[i] = rand() % 1000; // Números aleatórios entre 0 e 999
}

// Imprimir o vetor printf("Vetor gerado:  "); for (int i = 0; i < SIZE; i++) {
printf("%d ", array[i]);
}
printf("\n");

// Criar as threads
pthread_t threads[THREAD_COUNT];
int thread_ids[THREAD_COUNT];

for (int i = 0; i < THREAD_COUNT; i++) {
  thread_ids[i] = i;
  pthread_create(&threads[i], NULL, ﬁnd_max, (void *)&thread_ids[i]);
}

// Aguardar as threads terminarem
for (int i = 0; i < THREAD_COUNT; i++) {
  pthread_join(threads[i], NULL);
}

// Encontrar o maior valor entre os resultados das threads int global_max =
// max_values[0];
for (int i = 1; i < THREAD_COUNT; i++) {
  if (max_values[i] > global_max) {
    global_max = max_values[i];
  }
}

// Exibir o maior elemento encontrado
printf("O maior elemento no vetor é: %d\n", global_max);

return 0;
