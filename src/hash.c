#include "../include/hash.h"
#include <string.h>

/*
 * MurmurHash3 (32-bit)
 * Extremely fast, excellent collision resistance.
 * Processes 4 bytes at a time instead of 1 byte.
 */
uint32_t Hash(const char *key)
{
    int len = strlen(key);
    const uint8_t *data = (const uint8_t *)key;

    uint32_t h1 = 0x9747b28c;

    const uint32_t c1 = 0xcc9e2d51;
    const uint32_t c2 = 0x1b873593;

    const int nblocks = len / 4;
    const uint32_t *blocks = (const uint32_t *)(data);

    for (int i = 0; i < nblocks; i++)
    {
        uint32_t k1 = blocks[i];

        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;

        h1 ^= k1;
        h1 = (h1 << 13) | (h1 >> (32 - 13));
        h1 = h1 * 5 + 0xe6546b64;
    }

    const uint8_t *tail = (const uint8_t *)(data + nblocks * 4);
    uint32_t k1 = 0;

    switch (len & 3)
    {
    case 3:
        k1 ^= tail[2] << 16;
    case 2:
        k1 ^= tail[1] << 8;
    case 1:
        k1 ^= tail[0];
        k1 *= c1;
        k1 = (k1 << 15) | (k1 >> (32 - 15));
        k1 *= c2;
        h1 ^= k1;
    }

    h1 ^= len;
    h1 ^= h1 >> 16;
    h1 *= 0x85ebca6b;
    h1 ^= h1 >> 13;
    h1 *= 0xc2b2ae35;
    h1 ^= h1 >> 16;

    return h1;
}

/*
 * FNV-1a Hashing algorithm
 */
// uint32_t HashString(const char *key)
// {
//     uint32_t hash = 2166136261u;
//     for (int i = 0; key[i] != '\0'; i++)
//     {
//         hash ^= (uint8_t)key[i];
//         hash *= 16777619;
//     }
//     return hash;
// }
