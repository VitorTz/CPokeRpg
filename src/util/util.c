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

size_t hash_zindex(const void* z) {
    const size_t k = *((zindex_t*)z);
    return k;
}


size_t hash_component_t(const void* data) {
    const size_t i = *((component_t*)data);
    return i;
}


size_t hash_scene_id(const void* data) {
    const size_t k = *((scene_id_t*)data);
    return k;
}


int equal_component_t(const void* l, const void* r) {
    return *((component_t*)l) == *((component_t*)r);
}

int equal_entity_t(const void* l, const void* r) {
    return *((entity_t*)l) == *((entity_t*)r);
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

double dclamp(double d, double min, double max) {
    const double t = d < min ? min : d;
    return t > max ? max : t;
}


float fclamp(float d, float min, float max) {
    const float t = d < min ? min : d;
    return t > max ? max : t;
}


void random_file_from_dir(const char* dir, string_t* str) {
    DIR* folder = opendir(dir);

    if (!folder) {
        perror("Erro ao abrir a pasta");
        return NULL;
    }

    struct dirent* entry;
    int file_count = 0;
    char* file_names[256]; // Limite de 256 arquivos para simplificar o exemplo

    // Contar e armazenar os nomes dos arquivos
    while ((entry = readdir(folder)) != NULL) {
        if (entry->d_type == DT_REG) { // Apenas arquivos regulares
            file_names[file_count] = strdup(entry->d_name);
            file_count++;
        }
    }
    closedir(folder);

    if (file_count == 0) {
        printf("Nenhum arquivo encontrado na pasta.\n");
        return NULL;
    }

    // Selecionar um arquivo aleatório
    srand(time(NULL));
    int random_index = rand() % file_count;
    char* chosen_file = strdup(file_names[random_index]);

    // Limpar memória dos nomes dos arquivos
    for (int i = 0; i < file_count; i++) {
        free(file_names[i]);
    }
    string_clear(str);
    string_append(str, dir);
    string_append(str, chosen_file);
    free(chosen_file);    
}