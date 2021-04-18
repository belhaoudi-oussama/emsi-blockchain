#include "blockchain.h"

/**
 * block_hash - Computes the hash of a Block
 * @block: pointer to block to hash
 * @hash_buf: buffer to store hash
 *
 * Return: pointer to @hash_buf
 */

uint8_t *block_hash(block_t const *block,
			uint8_t hash_buf[SHA256_DIGEST_LENGTH])
{
	SHA256((const unsigned char *)&block->info, sizeof(block->info), hash_buf); 
	return (hash_buf);
}

