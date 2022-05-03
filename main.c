#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

int sumMatrix = 0;
int matrixTamanho = 0;
void *sumMatrixLine(void *args);
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

struct arguments {
        int line;
        int *actualLine;
};

int main() {

        scanf(" %d", &matrixTamanho);

        int matrix[matrixTamanho][matrixTamanho];
        pthread_t threads[matrixTamanho];

        for (int i = 0; i < matrixTamanho; i++) {
                for (int j = 0; j < matrixTamanho; j++) {
                        scanf(" %d", &matrix[i][j]);
                }  
        }

        for (int i = 0; i < matrixTamanho; i++) {
                struct arguments *args = malloc(sizeof(struct arguments));
                args->line = i;
                args->actualLine = malloc(matrixTamanho * sizeof(int));

                for (int j = 0; j < matrixTamanho; j++) {
                        args->actualLine[j] = matrix[i][j];
                }
                
                pthread_create(&(threads[i]), NULL, sumMatrixLine, (void *)args);
        }

        for (int i = 0; i < matrixTamanho; i++) {
                pthread_join(threads[i], NULL);
        }
        

        printf("\nTotal sum: %d\n", sumMatrix);
}

void *sumMatrixLine(void *args) {

        pthread_mutex_lock(&mutex);

        struct arguments *argsCasted = (struct arguments *) args;

        printf("\n- Line %d: ", argsCasted->line);
        int x = 0;
        for (int i = 0; i < matrixTamanho; i++) {
                x += argsCasted->actualLine[i];
        }
        sumMatrix += x;
        printf("%d", x);

        pthread_mutex_unlock(&mutex);

        return args;
}