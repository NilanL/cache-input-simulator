#ifndef CACHE_SET_H_INCLUDED
#define CACHE_SET_H_INCLUDED

//** Structure for the sets within a cache **//
struct cache_set_struct {
    bool is_full;
    unsigned short LRU_index;
    short *blocks;
};

typedef struct cache_set_struct cache_set;

#endif // CACHE_SET_H_INCLUDED
