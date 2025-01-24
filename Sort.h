#ifndef SORT_H_
#define SORT_H_

#include <stddef.h>
#define SORT_DECL(ALIAS)                                            \
typedef int (*_Sort_##ALIAS##_f)(const _List_##ALIAS##_T *a,          \
                               const _List_##ALIAS##_T *b);         \
void List_##ALIAS##_sort(List_##ALIAS *node, _Sort_##ALIAS##_f cmp);

#define SORT_IMPL(ALIAS)                                            \
    void _List_##ALIAS##_merge_sort(List_##ALIAS *node,             \
                                    size_t length,                  \
                                    _Sort_##ALIAS##_f cmp)          \
{                                                                   \
    if(length<2){                                                   \
        (*node)->next = NULL;                                       \
        return;                                                          \
    }                                                               \
    List_##ALIAS a = *node, b, *ptr = node;                         \
    size_t step = length/2;                                         \
    while(step--) ptr=&(*ptr)->next;                                \
    b=*ptr;                                                         \
    _List_##ALIAS##_merge_sort(&a, length/2, cmp);                  \
    _List_##ALIAS##_merge_sort(&b, length-(length/2), cmp);         \
                                                                    \
    while( a&&b ){                                                   \
        if(cmp(&a->val, &b->val)){                                  \
            *node = a;                                              \
            node = &a->next;                                        \
            a = a->next;                                            \
        }else{                                                      \
            *node = b;                                              \
            node = &b->next;                                        \
            b = b->next;                                            \
        }                                                           \
    }                                                               \
    while(a){                                                       \
        *node = a;                                                  \
        node = &a->next;                                            \
        a = a->next;                                                \
    }                                                               \
    while(b){                                                       \
        *node = b;                                                  \
        node = &b->next;                                            \
        b = b->next;                                                \
    }                                                               \
}                                                                   \
void List_##ALIAS##_sort(List_##ALIAS *node, _Sort_##ALIAS##_f cmp) \
{                                                                   \
 size_t length = List_##ALIAS##_length(node);                       \
 if(length<2) return;                                                    \
_List_##ALIAS##_merge_sort(node, length, cmp);                      \
}

#endif // SORT_H_
