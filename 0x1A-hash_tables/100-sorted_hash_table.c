#include "hash_tables.h"

/**
 * shash_table_t - Sorted hash table data structure
 * @size: The size of the hash table
 * @array: An array of pointers to hash nodes
 * @shead: Pointer to the head of the sorted linked list
 * @stail: Pointer to the tail of the sorted linked list
 */
typedef struct shash_table_s
{
    unsigned long int size;
    shash_node_t **array;
    shash_node_t *shead;
    shash_node_t *stail;
} shash_table_t;

/**
 * shash_table_create - Creates a sorted hash table.
 * @size: The size of new sorted hash table.
 *
 * Return: If an error occurs - NULL.
 *         Otherwise - a pointer to the new sorted hash table.
 */
shash_table_t *shash_table_create(unsigned long int size)
{
    shash_table_t *ht;
    unsigned long int i;

    ht = malloc(sizeof(shash_table_t));
    if (ht == NULL)
        return (NULL);

    ht->size = size;
    ht->array = malloc(sizeof(shash_node_t *) * size);
    if (ht->array == NULL)
    {
        free(ht);
        return (NULL);
    }
    
    for (i = 0; i < size; i++)
        ht->array[i] = NULL;
    ht->shead = NULL;
    ht->stail = NULL;

    return (ht);
}

// Rest of the functions (shash_table_set, shash_table_get, shash_table_print, etc.) remain unchanged.

/**
 * shash_table_delete - Deletes a sorted hash table.
 * @ht: A pointer to the sorted hash table.
 */
void shash_table_delete(shash_table_t *ht)
{
    if (ht == NULL)
        return;

    shash_node_t *node, *tmp;

    node = ht->shead;
    while (node)
    {
        tmp = node->snext;
        free(node->key);
        free(node->value);
        free(node);
        node = tmp;
    }

    free(ht->array); // Free the hash table array
    free(ht);
}
