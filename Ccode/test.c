
typedef struct { int bits; struct hlist_head *ht; } map_t;
struct hlist_node { struct hlist_node *next, **pprev; };
struct hlist_head { struct hlist_node *first; };
struct hash_key {
    int key;
    void *data;
    struct hlist_node node;
};

struct hlist_node {
    struct hlist_node *next;
    struct hlist_node **pprev;
};

// deletes entry from hlist
void __hlist_del(struct hlist_node* entry)
{
    struct hlist_node *next = entry->next; // step1
    struct hlist_node **pprev = entry->pprev; //step2
    *pprev = next; //step3
    if (next)
      next->pprev = pprev; //step4
}