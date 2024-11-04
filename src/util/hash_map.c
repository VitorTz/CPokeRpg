#include "hash_map.h"
#include "iterator.h"
#include "vector.h"
#include <stdlib.h>


void hash_map_init(hash_map_t* h, const size_t num_buckets, const size_t t_size) {
    h->num_buckets = num_buckets;
    h->buckets = malloc(sizeof(vector_t) * num_buckets);
    h->t_size = t_size;
    h->size = 0;
    hash_map_iterator_t iter = hash_map_get_iterator(h);
    for (vector_t* p = iter.begin; p != iter.end; p += iter.step) {
        vector_init(p, sizeof(size_t) + t_size, 16);
    }    
}


void hash_map_close(hash_map_t* h) {
    hash_map_iterator_t iter = hash_map_get_iterator(h);
    for (vector_t* p = iter.begin; p != iter.end; p += iter.step) {
        vector_close(p);
    }    
    free(h->buckets);
}


void* hash_map_at(hash_map_t* h, const size_t key) {
    vector_t* v = h->buckets + (key % h->num_buckets);
    iterator_t iter = vector_get_iterator(v);
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        const size_t* p_key = (size_t*) p;
        if (*p_key == key) {
            return p + sizeof(size_t);
        }
    }
    h->size++;
    char* p = vector_allocate(v);
    *((size_t*) p) = key;    
    return p + sizeof(size_t);    
}


int hash_map_erase(hash_map_t *h, const size_t key) {
    vector_t* v = h->buckets + (key % h->num_buckets);
    iterator_t iter = vector_get_iterator(v);
    size_t i = 0;
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        const size_t* p_key = (size_t*) p;
        if (*p_key == key) {
            vector_erase(v, i);
            return 1;
        }
        i++;
    }
    return 0;
}


void hash_map_clear(hash_map_t* h) {
    hash_map_iterator_t iter = hash_map_get_iterator(h);
    for (vector_t* p = iter.begin; p != iter.end; p += iter.step) {
        vector_clear(p);
    }    
    h->size = 0;
}


hash_map_iterator_t hash_map_get_iterator(hash_map_t* h) {
    hash_map_iterator_t iter;
    iter.begin = h->buckets;
    iter.end = h->buckets + h->num_buckets + 1;
    iter.step = 1;
    return iter;
}


hash_map_query_t hash_map_contains(hash_map_t *h, const size_t key) {
    hash_map_query_t q;
    q.success = 0;
    q.data = NULL;
    vector_t* v = h->buckets + (key % h->num_buckets);
    iterator_t iter = vector_get_iterator(v);
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        const size_t* p_key = (size_t*) p;
        if (*p_key == key) {
            q.success = 1;
            q.data = p + sizeof(size_t);
            return q;
        }
    }
    return q;
}
