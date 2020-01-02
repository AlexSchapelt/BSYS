#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <assert.h>
#include <time.h>

typedef struct __node_t {
	int key;
	struct __node_t *next;
	pthread_mutex_t lock;
} node_t;

typedef struct __args_t {
        node_t *head;
        int id;
} args_t;

void nodeInit(node_t *n) {
	n->next = NULL;
	assert(pthread_mutex_init(&n->lock, NULL) == 0);
}

void List_Insert(node_t *head, int key) {
	//printf("try to  insert key: %d\n", key);
	node_t *newNode = malloc(sizeof(node_t));
	if (newNode == NULL) {
	        perror("malloc");
		 return;
	}
	//printf("init node\n");
	nodeInit(newNode);
        newNode->key = key;
	//printf("aquire lock\n");
	pthread_mutex_t *l = &head->lock;
	node_t *insert = head;
	while(pthread_mutex_trylock(l)) {
		insert = head->next;
		l = &insert->lock;
	}
	newNode->next = insert->next;
	insert->next = newNode;5
	pthread_mutex_unlock(&insert->lock);

	/*pthread_mutex_lock(&head->lock);
	newNode->next = head->next;
	head->next = newNode;
        pthread_mutex_unlock(&head->lock);*/
	//printf("releas lock\n");
	//printf("head is: %d\n", head->key);
}

int List_Lookup(node_t *head, int key) {
	int rv =-1;
        pthread_mutex_lock(&head->lock);
	node_t *curr = head;
	//printf("Test\n");
	while (curr->next) {
		//printf("test\n");
		//printf("visited node with key: %d\n", curr->key);
		if (curr->key == key) {
   	             rv = curr->key;
		     break;
	        }
		pthread_mutex_lock(&curr->next->lock);
		pthread_mutex_unlock(&curr->lock);
        	curr = curr->next;
        }
	pthread_mutex_unlock(&curr->lock);
	return rv; // now both success and failure 
}

void printAll(node_t *head) {
	pthread_mutex_lock(&head->lock);
        node_t *curr = head;
        //printf("Test\n");
        while (curr->next) {
                printf("%d\n", curr->key);
                pthread_mutex_lock(&curr->next->lock);
                pthread_mutex_unlock(&curr->lock);
                curr = curr->next;
        }
        pthread_mutex_unlock(&curr->lock);
}

void *threads(void *arg) {
	args_t *args = (args_t *) arg;
        for(int i = 0; i < 1500; ++i) {
               List_Insert(args->head, i+args->id*1000);
        }
        return NULL;
}


int main (void) {
	struct timespec start, end;
	node_t list;
	/*node_t mid;
	nodeInit(&mid);
	mid.key = 1500;
	list.next = &mid;*/
	nodeInit(&list);
	pthread_t t1;
	pthread_t t2;
	pthread_t t3;
	args_t a1;
	a1.head = &list;
	//a1.head = &mid;
	a1.id = 1;
	args_t a2;
	a2.head = &list;
	a2.id = 2;
	args_t a3;
	a3.head = &list;
	a3.id = 3;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start);
	assert(pthread_create(&t1, NULL, threads, &a1) == 0);
        assert(pthread_create(&t2, NULL, threads, &a2) == 0);
	//assert(pthread_create(&t3, NULL, threads, &a3) == 0);
	assert(pthread_join(t1, NULL) == 0);
	assert(pthread_join(t2, NULL) == 0);
	//assert(pthread_join(t3, NULL) == 0);
	clock_gettime(CLOCK_MONOTONIC_RAW, &end);
	printAll(&list);
	unsigned long time = (end.tv_sec - start.tv_sec) * 1000000000 + end.tv_nsec - start.tv_nsec;
        printf("took: %lu ns\n", time);
	return 0;
}
