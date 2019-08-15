/* 实现一个基于链表法解决冲突问题的散列表 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct _hashtbl_node_t
{
    void *key;
    void *data;
    struct _hashtbl_node_t *next;
} hashtbl_node_t;

typedef struct _hashtbl_t
{
    hashtbl_node_t **htables;
    int size;
    int cur_cnt;
    int (*hash_value)(struct _hashtbl_t *h, const void *key);
    int (*keycmp)(struct _hashtbl_t *h, const void *key1, const void *key2);
    void (*hash_node_free)(hashtbl_node_t *node);
} hashtbl_t;

#define hashtbl_t_MAX_NODES (0xffffffff)

typedef int (*hash_key_func)(struct _hashtbl_t *h, const void *key);
typedef int (*keycmp_func)(struct _hashtbl_t *h, const void *key1, const void *key2);
typedef void (*hash_node_free_func)(hashtbl_node_t *node);

#define offsetof(TYPE, MEMBER) ((size_t) & ((TYPE *)0)->MEMBER)
#define container(ptr, type, member) ({\
  const typeof( ((type *)0)->member) *__mptr = (ptr);\
  (type *) ( (char *)__mptr - offsetof(type,member)); })

hashtbl_t *hashtbl_t_create(int size, hash_key_func hash_value,
                            keycmp_func keycmp, hash_node_free_func hash_node_free);
void hashtbl_t_destory(hashtbl_t *h);
int hashtbl_t_insert(hashtbl_t *h, void *key, void *data);
hashtbl_node_t *hashtbl_t_delete(hashtbl_t *h, void *key);
void *hashtbl_t_search(hashtbl_t *h, void *key);

hashtbl_t *hashtbl_t_create(int size, hash_key_func hash_value,
                            keycmp_func keycmp, hash_node_free_func hash_node_free)
{
    hashtbl_t *h = NULL;
    int i = 0;

    if ((size < 0) || (hash_value == NULL) || (keycmp == NULL))
    {
        return NULL;
    }

    h = (hashtbl_t *)malloc(sizeof(hashtbl_t));
    if (h == NULL)
    {
        return NULL;
    }

    h->htables = (hashtbl_node_t **)malloc(size * sizeof(hashtbl_node_t *));
    if (h->htables == NULL)
    {
        return NULL;
    }

    h->size = size;
    h->cur_cnt = 0;
    h->hash_value = hash_value;
    h->keycmp = keycmp;
    h->hash_node_free = hash_node_free;

    for (i = 0; i < size; i++)
    {
        h->htables[i] = NULL;
    }

    return h;
}

void hashtbl_t_destory(hashtbl_t *h)
{
    int i = 0;
    hashtbl_node_t *cur = NULL;
    hashtbl_node_t *tmp = NULL;

    if (h == NULL)
    {
        return;
    }

    for (i = 0; i < h->size; i++)
    {
        cur = h->htables[i];
        while (cur != NULL)
        {
            tmp = cur;
            cur = cur->next;
            h->hash_node_free(tmp);
        }
        h->htables[i] = NULL;
    }

    free(h->htables);
    free(h);
    return;
}

int hashtbl_t_insert(hashtbl_t *h, void *key, void *data)
{
    unsigned int hvalue = 0;
    int i = 0;
    hashtbl_node_t *cur = NULL;
    hashtbl_node_t *prev = NULL;
    hashtbl_node_t *newnode = NULL;

    if ((h == NULL) || (key == NULL) || (data == NULL))
    {
        return 1;
    }

    hvalue = h->hash_value(h, key);
    cur = h->htables[hvalue];

    while ((cur != NULL) && (h->keycmp(h, key, cur->key) > 0))
    {
        prev = cur;
        cur = cur->next;
    }

    if ((cur != NULL) && (h->keycmp(h, key, cur->key) == 0))
    {
        return 2;
    }

    newnode = (hashtbl_node_t *)malloc(sizeof(hashtbl_node_t));
    if (newnode == NULL)
    {
        return 3;
    }

    newnode->key = key;
    newnode->data = data;
    if (prev == NULL)
    {
        newnode->next = h->htables[hvalue];
        h->htables[hvalue] = newnode;
    }
    else
    {
        newnode->next = prev->next;
        prev->next = newnode;
    }

    h->cur_cnt++;
    return 0;
}

hashtbl_node_t *hashtbl_t_delete(hashtbl_t *h, void *key)
{
    int hvalue = 0;
    int i = 0;
    hashtbl_node_t *cur = NULL;
    hashtbl_node_t *prev = NULL;

    if ((h == NULL) || (key == NULL))
    {
        return NULL;
    }

    hvalue = h->hash_value(h, key);
    cur = h->htables[hvalue];

    while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0))
    {
        if (h->keycmp(h, key, cur->key) == 0)
        {
            if (prev == NULL)
            {
                h->htables[hvalue] = cur->next;
            }
            else
            {
                prev->next = cur->next;
            }
            return cur;
        }
        prev = cur;
        cur = cur->next;
    }

    return NULL;
}

void *hashtbl_t_search(hashtbl_t *h, void *key)
{
    int hvalue = 0;
    int i = 0;
    hashtbl_node_t *cur = NULL;

    if ((h == NULL) || (key == NULL))
    {
        return NULL;
    }

    hvalue = h->hash_value(h, key);
    cur = h->htables[hvalue];

    while ((cur != NULL) && (h->keycmp(h, key, cur->key) >= 0))
    {
        if (h->keycmp(h, key, cur->key) == 0)
        {
            return cur->data;
        }
        cur = cur->next;
    }

    return NULL;
}

void hashtbl_t_dump(hashtbl_t *h)
{
    int i = 0;
    hashtbl_node_t *cur = NULL;

    if (h == NULL)
    {
        return;
    }

    printf("\r\n----start--size[%d],cur_cnt[%d]------------", h->size, h->cur_cnt);
    for (i = 0; i < h->size; i++)
    {
        printf("\r\n htables[%d]:", i);
        cur = h->htables[i];
        while ((cur != NULL))
        {
            printf("key[%s],data[%s] ", cur->key, cur->data);
            cur = cur->next;
        }
    }

    printf("\r\n----end--size[%d],cur_cnt[%d]------------", h->size, h->cur_cnt);
}

struct test_node
{
    char key[80];
    char data[80];
};

unsigned int siample_hash(const char *str)
{
    register unsigned int hash = 0;
    register unsigned int seed = 131;

    while (*str)
    {
        hash = hash * seed + *str++;
    }

    return hash & (0x7FFFFFFF);
}

int hashtbl_t_hvalue(hashtbl_t *h, const void *key)
{
    return (siample_hash(key) % h->size);
}

int hashtbl_t_keycmp(hashtbl_t *h, const void *key1, const void *key2)
{
    return strcmp(key1, key2);
}

void hashtbl_node_t_free(hashtbl_node_t *node)
{
    struct test_node *ptmp = NULL;

    ptmp = container(node->key, struct test_node, key);

    free(ptmp);
    free(node);
}

int main()
{

    int i = 0;
    int res = 0;
    char *pres = NULL;
    hashtbl_node_t *node = NULL;
    struct test_node *p = NULL;
    hashtbl_t *h = NULL;

    h = hashtbl_t_create(5, hashtbl_t_hvalue, hashtbl_t_keycmp, hashtbl_node_t_free);
    assert(h != NULL);
    while (1)
    {
        p = (struct test_node *)malloc(sizeof(struct test_node));
        assert(p != NULL);
        printf("\r\n Please input key & value, or \"quit\" to exit \r\n");
        scanf("%s", p->key);
        scanf("%s", p->data);

        if (strcmp(p->key, "quit") == 0)
        {
            free(p);
            break;
        }

        res = hashtbl_t_insert(h, p->key, p->data);
        if (res != 0)
        {
            free(p);
            printf("\r\n key[%s],data[%s] insert failed %d", p->key, p->data, res);
        }
        else
        {
            printf("\r\n key[%s],data[%s] insert success %d", p->key, p->data, res);
        }
    }

    hashtbl_t_dump(h);

    while (1)
    {
        p = (struct test_node *)malloc(sizeof(struct test_node));
        assert(p != NULL);
        printf("\r\n Please input key to search, or \"quit\" to exit \r\n");
        scanf("%s", p->key);

        if (strcmp(p->key, "quit") == 0)
        {
            free(p);
            break;
        }
        pres = hashtbl_t_search(h, p->key);
        if (pres == NULL)
        {
            printf("\r\n key[%s] search data failed", p->key);
        }
        else
        {
            printf("\r\n key[%s],search data[%s] success", p->key, pres);
        }
        free(p);
    }
    hashtbl_t_dump(h);
    while (1)
    {
        p = (struct test_node *)malloc(sizeof(struct test_node));
        assert(p != NULL);
        printf("\r\n Please input key to delete , or \"quit\" to exit \r\n");
        scanf("%s", p->key);

        if (strcmp(p->key, "quit") == 0)
        {
            free(p);
            break;
        }
        node = hashtbl_t_delete(h, p->key);
        if (node == NULL)
        {
            printf("\r\n key[%s] delete node failed ", p->key);
        }
        else
        {
            printf("\r\n key[%s],delete data[%s] success", node->key, node->data);
            h->hash_node_free(node);
        }
        free(p);
        hashtbl_t_dump(h);
    }

    hashtbl_t_destory(h);

    return 0;
}