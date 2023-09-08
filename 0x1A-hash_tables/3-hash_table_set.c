#include "hash_tables.h"

/**
 * hash_table_set - Add or update an element in a hash table.
 * @ht: A pointer to the hash table.
 * @key: The key to add - cannot be an empty string.
 * @value: The value associated with key.
 *
 * Return: Upon failure - 0.
 *         Otherwise - 1.
 */
int hash_table_set(hash_table_t *ht, const char *key, const char *value)
{
    if (ht == NULL || key == NULL || *key == '\0' || value == NULL)
        return 0;

    /* Allocate memory for a copy of 'value' */
    char *value_copy = strdup(value);
    if (value_copy == NULL)
        return 0;

    unsigned long int index = key_index((const unsigned char *)key, ht->size);
    hash_node_t *current = ht->array[index];

    /* Check if key already exists; update value if found */
    while (current)
    {
        if (strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = value_copy;
            return 1;
        }
        current = current->next;
    }

    /* Allocate memory for a new node */
    hash_node_t *new_node = malloc(sizeof(hash_node_t));
    if (new_node == NULL)
    {
        free(value_copy);
        return 0;
    }

    /* Allocate memory for a copy of 'key' */
    new_node->key = strdup(key);
    if (new_node->key == NULL)
    {
        free(value_copy);
        free(new_node);
        return 0;
    }

    new_node->value = value_copy;
    new_node->next = ht->array[index];
    ht->array[index] = new_node;

    return 1;
}
