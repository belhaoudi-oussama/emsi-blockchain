#include "blockchain.h"

/**
 * block_create - Creates a block structure and initializes it
 * @prev: pointer to the previous Block in the Blockchain
 * @data: memory area to duplicate in the Block’s data
 * @data_len: number of bytes to duplicate in data
 *
 * Return: a pointer to the allocated Block, NULL upon failure
 */

block_t *block_create(block_t const *prev, int8_t const *data, uint32_t data_len)
{
	block_t *block;
	
	if (!prev || !data)
		return (NULL);

	block = malloc(sizeof(*block));
	block->info.index = (prev->info.index + 1);
	block->info.difficulty = 0;
	block->info.timestamp = time(NULL);
	block->info.nonce = 0;
	memcpy(&(block->info.prev_hash), prev->hash, SHA256_DIGEST_LENGTH);
	if (data_len < BLOCKCHAIN_DATA_MAX)
		block->data.len = data_len;
	else
		block->data.len = BLOCKCHAIN_DATA_MAX;

	memcpy(&(block->data.buffer), data ,block->data.len);
	memset(block->hash, 0, SHA256_DIGEST_LENGTH);
	return (block);	
}

