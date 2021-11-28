#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define THREAD_NUM 8

struct thread_data {
    int thread_index;
    int sum;
    char *message;
};

void *ssu_printhello(void *arg);

struct thread_data thread_data_array[THREAD_NUM];
char *messages[THREAD_NUM];

int main(void) 
{
    pthread_t tid[THREAD_NUM];
    int sum;
    int i;

    sum = 0;
    messages[0] = "A";
    messages[1] = "B";
    messages[2] = "C";
    messages[3] = "D";
    messages[4] = "E";
    messages[5] = "F";
    messages[6] = "G";
    messages[7] = "H";

    for (i = 0; i < THREAD_NUM; i++) {
        sum = sum + i;
        thread_data_array[i].thread_index = i;
        thread_data_array[i].sum = sum;
        thread_data_array[i].message = messages[i];
        printf("Creating thread %d\n", i);

        if (pthread_create(&tid[i], NULL, ssu_printhello, (void *)&thread_data_array[i]) != 0) {
            fprintf(stderr, "pthread_create error\n");
            exit(1);
        }
    }

    sleep(5);
    exit(0);
}

void *ssu_printhello(void *arg) {
    struct thread_data *data;
    char *message;
    int thread_index;
    int sum;

    sleep(1);
    data = (struct thread_data *)arg;
    thread_index = data->thread_index;
    sum = data->sum;
    message = data->message;
    printf("Thread %d: %s Sum=%d\n", thread_index, message, sum);
    return NULL;
}
