#include "util.h"
#if defined(_WIN32) || defined(_WIN64)
    #include "../../lib/dirent-1.24/dirent-1.24/include/dirent.h"
#elif defined(__unix__) || defined(__unix) || defined(__APPLE__) && defined(__MACH__)
    #include <dirent.h>    
#endif


size_t hash_str(const void* s) {
	const char* str = (const char*) s;
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

size_t hash_size_t(const void* k) {
    const size_t i = *((size_t*)k);
    return i;
}


size_t hash_entity_t(const void* e) {
    const size_t i = *((entity_t*) e);
    return i;
}


int is_prime(const size_t n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;

    size_t limit = sqrt(n);
    for (size_t i = 5; i <= limit; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return 1;
    }
    return 1;
}


size_t next_prime(const size_t n) {
    size_t m = n + 1;
    while (!is_prime(m)) {
        m++;
    }
    return m;
}