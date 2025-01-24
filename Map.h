#ifndef MAP_H_
#define MAP_H_

// Extend List with Map operations

#define MAP_DECL(K, ALIAS)                                 \
typedef K _Map_##ALIAS##_K;                                \
List_##ALIAS* Map_##ALIAS##_find(List_##ALIAS *current_ptr,\
                                 _Map_##ALIAS##_K key);    \
_List_##ALIAS##_T*                                         \
Map_##ALIAS##_get(List_##ALIAS *const current_ptr,         \
                  _Map_##ALIAS##_K key);                   \
int Map_##ALIAS##_remove(List_##ALIAS *current_ptr,          \
                       _Map_##ALIAS##_K key,               \
                       _List_##ALIAS##_T *out);

#define MAP_IMPL(ALIAS, CMP)                                         \
List_##ALIAS *                                                       \
Map_##ALIAS##_find(List_##ALIAS *current_ptr, _Map_##ALIAS##_K key){ \
struct List_##ALIAS *current = *current_ptr;                         \
    while(current){                                                  \
        if(CMP(key, &current->val))                                  \
            return current_ptr;                                           \
        current_ptr = &current->next;                                \
        current = current->next;                                     \
    }                                                                \
    return NULL;                                                          \
}                                                                    \
_List_##ALIAS##_T*                                                   \
Map_##ALIAS##_get(List_##ALIAS *const map, _Map_##ALIAS##_K key) {   \
    List_##ALIAS *node = Map_##ALIAS##_find(map, key);               \
    if(!node) return NULL;                                               \
    return &(*node)->val;                                                 \
}                                                                    \
int Map_##ALIAS##_remove(List_##ALIAS *map,                            \
                       _Map_##ALIAS##_K key,                         \
                       _List_##ALIAS##_T* out){                      \
    List_##ALIAS *node = Map_##ALIAS##_find(map, key);               \
    if(!node) return -1;                                                 \
    if(out)                                                          \
        *out = List_##ALIAS##_pop(node);                             \
    else                                                             \
        List_##ALIAS##_pop(node);                                    \
    return 0;                                                             \
}

#endif // MAP_H_
