#include "hash_map.h"
#include "iterator.h"
#include "vector.h"
#include <stdlib.h>


hash_map_t* hash_map_create(const size_t num_buckets, const size_t t_size) {
    hash_map_t* h = malloc(sizeof(hash_map_t));
    h->num_buckets = num_buckets;
    h->buckets = malloc(sizeof(vector_t*) * num_buckets);
    h->t_size = t_size;
    h->size = 0;
    for (int i = 0; i < num_buckets; i++) {
        h->buckets[i] = vector_create(sizeof(hash_node_t), 32);
    }
    return h;
}


void hash_map_destroy(hash_map_t* hash_map) {
    for (int i = 0; i < hash_map->num_buckets; i++) {
        vector_t* v = hash_map->buckets[i];
        iterator_t iter = vector_iterator(v);
        for (char* p = iter.begin; p != iter.end; p += iter.step) {
            hash_node_t* node = (hash_node_t*) p;
            free(node->value);
        }
        vector_destroy(v);
    }
    free(hash_map->buckets);
}


void* hash_map_at(hash_map_t* hash_map, const size_t key) {
    vector_t* v = hash_map->buckets[key % hash_map->num_buckets];
    iterator_t iter = vector_iterator(v);
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        hash_node_t* node = (hash_node_t*) p;
        if (node->key == key) {
            return node->value;
        }
    }
    hash_node_t* node = (hash_node_t*) vector_allocate(v);
    node->key = key;
    node->value = malloc(hash_map->t_size);
    hash_map->size++;
    return node->value;
}


void hash_map_erase(hash_map_t *hash_map, const size_t key) {
    vector_t* v = hash_map->buckets[key % hash_map->num_buckets];
    iterator_t iter = vector_iterator(v);
    size_t i = 0;
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        hash_node_t* node = (hash_node_t*) p;
        if (node->key == key) {
            free(node->value);
            hash_map->size--;
            vector_erase(v, i);
        }
        i++;
    }
}


void hash_map_clear(hash_map_t* hash_map) {
    for (int i = 0; i < hash_map->num_buckets; i++) {
        vector_t* v = hash_map->buckets[i];
        iterator_t iter = vector_iterator(v);
        for (char* p = iter.begin; p != iter.end; p += iter.step) {
            hash_node_t* node = (hash_node_t*) p;
            free(node->value);
        }
        vector_clear(v);
    }
    hash_map->size = 0;
}


hash_map_iterator_t hash_map_get_iterator(hash_map_t* hash_map) {
    hash_map_iterator_t iter;
    iter.iterators = malloc(sizeof(iterator_t) * hash_map->num_buckets);
    iter.num_iterators = hash_map->num_buckets;
    for (int i = 0; i < iter.num_iterators; i++) {
        *(iter.iterators + i) = vector_iterator(hash_map->buckets[i]);        
    }
    return iter;
}


void hash_map_iterator_destroy(hash_map_iterator_t* iterator) {
    free(iterator->iterators);
    free(iterator);
}


hash_map_query_t hash_map_contains(hash_map_t *hash_map, const size_t key) {
    hash_map_query_t q;
    q.success = 0;
    q.data = NULL;
    vector_t* v = hash_map->buckets[key % hash_map->num_buckets];
    iterator_t iter = vector_iterator(v);
    for (char* p = iter.begin; p != iter.end; p += iter.step) {
        hash_node_t* node = (hash_node_t*) p;
        if (node->key == key) {
            q.success = 1;
            q.data = node->value;
            return q;
        }
    }
    return q;
}
