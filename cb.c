// Type your code here, or load an example.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CODE_ERROR 1
#define CODE_SUCCESS 0

typedef struct
{
    int value1;
    int value2;
} Item;

typedef struct
{
    void *array;
    void *head;
    void *tail;
    int capacity;
    int size;
    int count;
} CircularBuffer;

int cb_init(CircularBuffer *cb, int capacity, int item_size)
{
    cb->array = malloc(capacity * item_size);

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

        return CODE_SUCCESS;
    }
}
char cb_is_empty(CircularBuffer *cb)
{
    return cb->count == 0;
}

void *cb_dequeue(CircularBuffer *cb)
{
    void *result = NULL;
    if (cb_is_empty(cb))
        return result;
    else
    {
        result = cb->head;
        cb->count--;
       __shift_item(cb, &cb->head);
    }
    return result;
}

inline void __shift_item(CircularBuffer* cb, void **ptr )
{
    *ptr = cb->array + ((*ptr - cb->array + cb->size) % (cb->capacity * cb->size));

}
void cb_enqueue(CircularBuffer *cb, void *item)
{

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
}
void *cb_get(CircularBuffer *cb, int index)
{
    void *result = NULL;
    if (cb->count > index)
    {
        result = cb->array + ((cb->head + index * cb->size - cb->array) % (cb->capacity * cb->size));
    }

    return result;
}
void cb_print(CircularBuffer *cb)
{
    int i;
    printf("cb count %d\n", cb->count);
    for (int i = 0; i < cb->count; i++)
    {
        Item *t = (Item *)cb_get(cb, i);
        printf("%d %d \n", t->value1, t->value2);
    }
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