#ifndef PK_ENTITY_QUEUE_H
#define PK_ENTITY_QUEUE_H
#include "types.h"


typedef struct entity_queue {
    entity_t* entities;
    size_t top;
    size_t size;
} entity_queue_t;

void entity_queue_init(entity_queue_t* ent_queue);

void entiy_queue_close(entity_queue_t* ent_queue);

entity_t entity_queue_pop(entity_queue_t* q);

void entity_queue_push(entity_queue_t* q, entity_t e);


#endif