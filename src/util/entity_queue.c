#include <assert.h>
#include "entity_queue.h"
#include "types.h"
#include <stdlib.h>
#include "../constants.h"


void entity_queue_init(entity_queue_t *ent_queue) {
    ent_queue->entities = malloc(sizeof(entity_t) * MAX_ENTITIES);
    ent_queue->size = 0;
    ent_queue->top = MAX_ENTITIES - 1;
}


void entiy_queue_close(entity_queue_t *ent_queue) {
    free(ent_queue->entities);
}

entity_t entity_queue_pop(entity_queue_t* q) {
    assert(q->size < MAX_ENTITIES);
    const entity_t e = q->entities[q->top];
    q->top--;
    q->size++;
    return e;
}


void entity_queue_push(entity_queue_t *q, const entity_t e) {
    q->top++;
    q->entities[q->top] = e;
    q->size--;
}