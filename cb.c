// Type your code here, or load an example.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define CODE_ERROR 1
#define CODE_SUCCESS 0
typedef unsigned char BYTE;
typedef struct
{
    int value1;
    int value2;
} Item;

typedef struct
{
    BYTE *array;
    BYTE *head;
    BYTE *tail;
    int capacity;
    int size;
    int count;
    pthread_mutex_t lock;
} CircularBuffer;

int cb_init(CircularBuffer *cb, int capacity, int item_size)
{
    cb->array = (BYTE *)malloc(capacity * item_size);

    if (cb->array == NULL)
    {

        return CODE_ERROR;
    }
    else
    {
        cb->count = 0;
        cb->size = item_size;
        cb->capacity = capacity;
        cb->head = cb->array;
        cb->tail = cb->array;
        pthread_mutex_init(&cb->lock, NULL);
        return CODE_SUCCESS;
    }
}
char cb_is_empty(CircularBuffer *cb)
{
    return cb->count == 0;
}

inline void __shift_item(CircularBuffer *cb, BYTE **ptr)
{
    *ptr = cb->array + ((*ptr - cb->array + cb->size) % (cb->capacity * cb->size));
}

void *cb_dequeue(CircularBuffer *cb)
{
    pthread_mutex_lock(&cb->lock);
    void *result = NULL;
    if (cb_is_empty(cb))
        return result;
    else
    {
        result = cb->head;
        cb->count--;
        __shift_item(cb, &cb->head);
    }
    pthread_mutex_unlock(&cb->lock);
    return result;
}

void cb_enqueue(CircularBuffer *cb, void *item)
{
    pthread_mutex_lock(&cb->lock);
    memcpy(cb->tail, item, cb->size);
    __shift_item(cb, &cb->tail);
    if (cb->count < cb->capacity)
    {

        cb->count++;
    }
    else
    {

        __shift_item(cb, &cb->head);
    }
    pthread_mutex_unlock(&cb->lock);
}
void *__cb_get(CircularBuffer *cb, int index)
{

    void *result = NULL;
    if (cb->count > index)
    {
        result = cb->array + ((cb->head + index * cb->size - cb->array) % (cb->capacity * cb->size));
    }

    return result;
}
void *cb_get(CircularBuffer *cb, int index)
{
    void *result = NULL ;
    pthread_mutex_lock(&cb->lock);
    result = __cb_get(cb, index);
    pthread_mutex_unlock(&cb->lock) ;
    return result;
}
void cb_print(CircularBuffer *cb)
{
    int i;
    pthread_mutex_lock(&cb->lock);
    printf("cb count %d\n", cb->count);
    for (int i = 0; i < cb->count; i++)
    {
        Item *t = (Item *)__cb_get(cb, i);
        printf("%d %d \n", t->value1, t->value2);
    }
    pthread_mutex_unlock(&cb->lock);
}

int main()
{
    printf("Hello CB\n");
    CircularBuffer buf;
    cb_init(&buf, 3, sizeof(Item));

    Item t1 = {.value1 = 1, .value2 = 11};
    Item t2 = {.value1 = 2, .value2 = 22};
    Item t3 = {.value1 = 3, .value2 = 33};
    Item t4 = {.value1 = 4, .value2 = 44};
    Item t5 = {.value1 = 5, .value2 = 55};

    cb_enqueue(&buf, &t1);
    cb_print(&buf);
    cb_enqueue(&buf, &t2);
    cb_print(&buf);

    cb_dequeue(&buf);
    cb_print(&buf);

    cb_enqueue(&buf, &t3);
    cb_print(&buf);
    cb_enqueue(&buf, &t4);
    cb_print(&buf);
    cb_enqueue(&buf, &t5);
    cb_print(&buf);
}