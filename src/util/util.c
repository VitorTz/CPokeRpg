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


void random_file_from_dir(const char* dir, mstring_t* result) {
    DIR* folder = opendir(dir);    

    if (!folder) {
        perror("ERROR: Erro o abrir pasta");
        return NULL;
    }

    struct dirent* entry;
    int file_count = 0;
    char* file_names[256];
    
    while ((entry = readdir(folder)) != NULL) {
        if (entry->d_type == DT_REG) {
            file_names[file_count] = strdup(entry->d_name);
            file_count++;
        }
    }
    closedir(folder);

    if (file_count == 0) {
        printf("Nenhum arquivo encontrado na pasta.\n");
        return NULL;
    }
    
    srand(time(NULL));
    int random_index = rand() % file_count;
    char* chosen_file = strdup(file_names[random_index]);
    
    mstring_clear(result);
    mstring_append(result, dir);
    mstring_append(result, chosen_file);

    for (int i = 0; i < file_count; i++) {
        free(file_names[i]);
    }

    free(chosen_file);
    return result;
}