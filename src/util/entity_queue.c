#include <assert.h>
#include "entity_queue.h"
#include "types.h"
#include <stdlib.h>


entity_queue_t* entity_queue_create() {
    entity_queue_t* q = malloc(sizeof(entity_queue_t));
    for (entity_t e = 0; e < MAX_ENTITIES; e++) {
        q->q[e] = e;
    }    
    q->size = 0;
    q->top = MAX_ENTITIES - 1;
    return q;
}


void entity_queue_destroy(entity_queue_t *q) {
    free(q);
}


entity_t entity_queue_pop(entity_queue_t* q) {
    assert(q->size < MAX_ENTITIES);
    const entity_t e = q->q[q->top];
    q->top--;
    q->size++;
    return e;
}


void entity_queue_push(entity_queue_t *q, const entity_t e) {
    q->top++;
    q->q[q->top] = e;
    q->size--;
}