#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef enum
{
    TRUE,
    FALSE
} bool_t;

/*
    实现一个支持动态扩容的数组
    dynaic array 
 */

typedef char dyn_array_t;       /* could be char ,short, int, long or stucture ... */

bool_t dyn_array_create(dyn_array_t **p_dyn_array, int array_size);
bool_t dyn_array_extend(dyn_array_t **p_dyn_array, int old_array_size, int new_array_size);
bool_t dyn_array_destory(dyn_array_t *p_dyn_array);
bool_t dyn_array_test(void);

bool_t dyn_array_create(dyn_array_t **p_dyn_array, int array_size)
{
    *p_dyn_array = (dyn_array_t *)malloc(array_size * sizeof(dyn_array_t));
    if (*p_dyn_array == NULL)
    {
        printf("Can't malloc the %d size of memory", array_size);
        return FALSE;
    }
    memset(*p_dyn_array, 0, array_size * sizeof(dyn_array_t));

    return TRUE;
}
bool_t dyn_array_extend(dyn_array_t **p_dyn_array, int old_array_size, int new_array_size)
{
    dyn_array_t *p_new;
    dyn_array_t **p_temp;
    int i;

    if (new_array_size <= old_array_size)
        return TRUE;

    p_new = (dyn_array_t *)malloc(new_array_size * sizeof(dyn_array_t));
    if (p_new == NULL)
    {
        printf("Can't malloc the %d size of memory", new_array_size);
        return FALSE;
    }
    memcpy(p_new, *p_dyn_array, old_array_size * sizeof(dyn_array_t));
    memset(&p_new[old_array_size],0, sizeof(dyn_array_t) * (new_array_size-old_array_size));
    p_temp = p_dyn_array;
    free(*p_temp);
    *p_dyn_array = p_new;
    return TRUE;
}

bool_t dyn_array_destory(dyn_array_t *p_dyn_array)
{
    free(p_dyn_array);
    return TRUE;
}

bool_t dyn_array_test(void)
{
    dyn_array_t *my_dyn_array;
    int dyn_array_size = 8;
    int i;

    if (dyn_array_create(&my_dyn_array, dyn_array_size) == FALSE)
    {
        return FALSE;
    }

    for (i = 0; i < dyn_array_size; i++)
    {
        my_dyn_array[i] = i * 2;
        printf("%d ", my_dyn_array[i]);
    }
    printf("\r\n");

    if (dyn_array_extend(&my_dyn_array, dyn_array_size, dyn_array_size + 8) == FALSE)
    {
        return FALSE;
    }

    my_dyn_array[dyn_array_size] = 15;
    dyn_array_size = dyn_array_size + 8;

    for (i = 0; i < dyn_array_size; i++)
        printf("%d ", my_dyn_array[i]);
    printf("\r\n");

    dyn_array_destory(my_dyn_array);

    return TRUE;
}

/*
    实现一个大小固定的有序数组，支持动态增删改操作
    sequence array
 */

typedef struct
{
    int len; /* array length */
    int pos; /* current pos */
    int *p;  /* point to array */
} seq_array_t;

bool_t seq_array_create(seq_array_t **p_seq_array, int len);
bool_t seq_array_insert(seq_array_t *p_seq_array, int val);
bool_t seq_array_delete(seq_array_t *p_seq_array, int index);
bool_t seq_array_destory(seq_array_t *p_seq_array);
void seq_array_printf(seq_array_t *p_seq_array);
bool_t seq_array_test(void);

bool_t seq_array_create(seq_array_t **p_seq_array, int len)
{
    seq_array_t *p;
    if (len < 0)
        return FALSE;
    p = (seq_array_t *)malloc(sizeof(seq_array_t));
    if (p == NULL)
    {
        printf("can't malloc seq_array_t \r\n");
        return FALSE;
    }

    p->len = len;
    p->pos = 0;
    p->p = (int *)malloc(len * sizeof(int));

    if (p->p == NULL)
    {
        printf("can't malloc %d size of memory \r\n", len * sizeof(int));
        free(p);
        return FALSE;
    }
    memset(p->p, 0, len * sizeof(int));
    *p_seq_array = p;
    return TRUE;
}

bool_t seq_array_insert(seq_array_t *p_seq_array, int val)
{
    int i, j;
    if (p_seq_array == NULL)
        return FALSE;
    if (p_seq_array->p == NULL)
        return FALSE;
    if (p_seq_array->len <= p_seq_array->pos)
    {
        printf("can't insert the value %d, the array is full\r\n", val);
        return FALSE;
    }
    //add the value the array
    if (p_seq_array->pos == 0)
        p_seq_array->p[p_seq_array->pos++] = val;
    else
    {
        if (p_seq_array->p[p_seq_array->pos - 1] <= val)
            p_seq_array->p[p_seq_array->pos++] = val;
        else
        {
            for (i = 0; i < p_seq_array->pos; i++)
                if (p_seq_array->p[i] > val)
                {
                    for (j = p_seq_array->pos; j > i; j--)
                        p_seq_array->p[j] = p_seq_array->p[j - 1];
                    p_seq_array->p[i] = val;
                    p_seq_array->pos++;
                    break;
                }
        }
    }
    return TRUE;
}

bool_t seq_array_delete(seq_array_t *p_seq_array, int index)
{
    int i;
    if (p_seq_array == NULL)
        return FALSE;
    if (p_seq_array->p == NULL)
        return FALSE;

    if ((index < p_seq_array->pos) && (index >= 0))
    {
        for (i = index; i < p_seq_array->pos-1; i++)
            p_seq_array->p[i] = p_seq_array->p[i + 1];

        p_seq_array->p[--p_seq_array->pos] = 0;
    }
    return TRUE;
}
bool_t seq_array_destory(seq_array_t *p_seq_array)
{
    if (p_seq_array != NULL)
    {
        if (p_seq_array->p != NULL)
            free(p_seq_array->p);
        free(p_seq_array);
    }
    return TRUE;
}
void seq_array_printf(seq_array_t *p_seq_array)
{
    int i;
    for (i = 0; i < p_seq_array->len; i++)
        printf("%02d:%-8d  ", i, p_seq_array->p[i]);
    printf("\r\n");
}
bool_t seq_array_test(void)
{
    seq_array_t *my_seq_array;
    int seq_array_len = 16;
    int i;

    if (seq_array_create(&my_seq_array, seq_array_len) == FALSE)
        return FALSE;

    for (i = 0; i < my_seq_array->len; i++)
        seq_array_insert(my_seq_array, rand());
    seq_array_printf(my_seq_array);

    seq_array_insert(my_seq_array, rand());

    seq_array_delete(my_seq_array, 5);
    seq_array_printf(my_seq_array);
    seq_array_delete(my_seq_array, 9);
    seq_array_insert(my_seq_array, rand());
    seq_array_printf(my_seq_array);

    seq_array_destory(my_seq_array);

    return TRUE;
}

/*
    实现两个有序数组合并为一个有序数组
    a b 数组都是 从小到大排列的 合并成一个行的数组 c
    merge array
 */
int* merge_array(int *a, int size_a, int *b, int size_b);
bool_t merge_array_test();

int* merge_array(int *a, int size_a, int *b, int size_b)
{
    int *c;
    int i = 0, j = 0, k = 0;
    c = (int *)malloc((size_a + size_b) * sizeof(int));

    while (i < size_a && j < size_b)
        if (a[i] <= b[j])
            c[k++] = a[i++];
        else
            c[k++] = b[j++];
    while(i<size_a)
        c[k++]=a[i++];
    while(j<size_b)
        c[k++]=b[j++];

    return c;
}
bool_t merge_array_test()
{
    seq_array_t *my_seq_array_a;
    seq_array_t *my_seq_array_b;
    int *c;
    int i;
    int seq_array_a_len = 9;
    int seq_array_b_len = 13;
    if (seq_array_create(&my_seq_array_a, seq_array_a_len) == FALSE)
        return FALSE;
    if (seq_array_create(&my_seq_array_b, seq_array_b_len) == FALSE)
        return FALSE;

    for (i = 0; i < my_seq_array_a->len; i++)
        seq_array_insert(my_seq_array_a, rand());
    for (i = 0; i < my_seq_array_b->len; i++)
        seq_array_insert(my_seq_array_b, rand());    

    printf("array_a : \r\n");
    seq_array_printf(my_seq_array_a);
    printf("array_b : \r\n");
    seq_array_printf(my_seq_array_b);

    c = merge_array(my_seq_array_a->p,seq_array_a_len,my_seq_array_b->p,seq_array_b_len);

    printf("array_c : \r\n");
    for(i = 0; i< seq_array_a_len + seq_array_b_len;i++)
        printf("%02d:%-8d  ", i,c[i]);

    seq_array_destory(my_seq_array_a);
    seq_array_destory(my_seq_array_b);
    free(c);

    return TRUE;
}
int main(int argc, char *argv[])
{
    printf("\r\ndynamic array test:\r\n");
    dyn_array_test();
    printf("\r\nseq array test:\r\n");
    seq_array_test();
    printf("\r\nmerge array test:\r\n");
    merge_array_test();
    return 0;
}

