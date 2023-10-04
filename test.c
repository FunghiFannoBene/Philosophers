#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define N 5  // Number of philosophers

pthread_mutex_t fork_locks[N];  // Mutexes for each fork

void pickLeftFork(int philosopher) {
    printf("Philosopher %d picks up left fork\n", philosopher);
}

void pickRightFork(int philosopher) {
    printf("Philosopher %d picks up right fork\n", philosopher);
}

void eat(int philosopher) {
    printf("Philosopher %d eats\n", philosopher);
}

void putLeftFork(int philosopher) {
    printf("Philosopher %d puts down left fork\n", philosopher);
}

void putRightFork(int philosopher) {
    printf("Philosopher %d puts down right fork\n", philosopher);
}

void* wantsToEat(void* philosopher_ptr) {
    int philosopher = *(int*)philosopher_ptr;
    int left_fork_id = philosopher % N;
    int right_fork_id = (philosopher + 1) % N;

    if (philosopher % N == 1) {
        pthread_mutex_lock(&fork_locks[right_fork_id]);
        pthread_mutex_lock(&fork_locks[left_fork_id]);
        
        pickRightFork(philosopher);
        pickLeftFork(philosopher);
        
        eat(philosopher);
        
        putLeftFork(philosopher);
        putRightFork(philosopher);
        
        pthread_mutex_unlock(&fork_locks[left_fork_id]);
        pthread_mutex_unlock(&fork_locks[right_fork_id]);
    } else {
        pthread_mutex_lock(&fork_locks[left_fork_id]);
        pthread_mutex_lock(&fork_locks[right_fork_id]);
        
        pickLeftFork(philosopher);
        pickRightFork(philosopher);
        
        eat(philosopher);
        
        putRightFork(philosopher);
        putLeftFork(philosopher);
        
        pthread_mutex_unlock(&fork_locks[right_fork_id]);
        pthread_mutex_unlock(&fork_locks[left_fork_id]);
    }

    return NULL;
}

int main() {
    for (int i = 0; i < N; i++) {
        pthread_mutex_init(&fork_locks[i], NULL);
    }

    pthread_t philosophers[N];
    int philosopher_ids[N];

    for (int i = 0; i < N; i++) {
        philosopher_ids[i] = i;
        pthread_create(&philosophers[i], NULL, wantsToEat, &philosopher_ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        pthread_mutex_destroy(&fork_locks[i]);
    }

    return 0;
}
