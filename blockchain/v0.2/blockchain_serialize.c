#include "blockchain.h"

/**
 * blockchain_serialize - serializes blockchain to file
 * @blockchain: pointer to the blockchain to be serialized
 * @path: path to save file
 * Return: 0 on success else -1 on failure
 */

int blockchain_serialize(blockchain_t const *blockchain, char const *path)
{
	header_t header;
	FILE *fp = NULL;
	block_t *block = NULL;
	int i = 0;

	if (!blockchain || !path)
		return (-1);
	memcpy(header.hblk_magic, HBLK_MAGIC, HBLK_MAGIC_LEN);
	memcpy(header.hblk_version, HBLK_VERSION, HBLK_VERSION_LEN);
	header.hblk_endian = _get_endianness();
	header.hblk_blocks = llist_size(blockchain->chain);
	fp = fopen(path,"w");
	if (fp == NULL)
		return (-1);
	fwrite(&header, sizeof(header), 1, fp);
	for (i = 0; i < header.hblk_blocks; i++)
	{
		block = llist_get_node_at(blockchain->chain, i);
		if (!block)
		{
			fclose(fp);
			return (-1);
		}
		fwrite((void *)&block->info, sizeof(block->info), 1, fp);
		fwrite((void *)&block->data.len, sizeof(block->data.len), 1, fp);
		fwrite(block->data.buffer, block->data.len, 1, fp);
		fwrite((void *)&block->hash, sizeof(block->hash), 1, fp);
	}
	fclose(fp);
	return (0);
}

