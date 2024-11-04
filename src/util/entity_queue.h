#ifndef PK_ENTITY_QUEUE_H
#define PK_ENTITY_QUEUE_H
#include "../constants.h"
#include "types.h"


typedef struct entity_queue {
    entity_t q[MAX_ENTITIES];
    size_t top;
    size_t size;
} entity_queue_t;


entity_queue_t* entity_queue_create();

void entity_queue_destroy(entity_queue_t* q);

entity_t entity_queue_pop(entity_queue_t* q);

void entity_queue_push(entity_queue_t* q, entity_t e);


#endif