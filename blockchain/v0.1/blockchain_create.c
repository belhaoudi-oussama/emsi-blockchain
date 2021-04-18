#include "blockchain.h"

/**
 * blockchain_create - Creates a Blockchain structure, and initializes it
 *
 * Return: pointer to the blockchain structure
 **/

blockchain_t *blockchain_create(void)
{
	block_t const _ginesis_init = GENESIS_INIT_BLOCK;
	blockchain_t *blockchain;
	block_t *block;

	blockchain = malloc(sizeof(*blockchain));
	block = malloc(sizeof(*block));
	
	memcpy(block, (block_t*) &_ginesis_init, sizeof(block_t));
	blockchain->chain = llist_create(MT_SUPPORT_TRUE);
	if ((llist_add_node(blockchain->chain,block,ADD_NODE_FRONT)) != 0)
	{
		return (NULL);
	}
	return (blockchain);
}
