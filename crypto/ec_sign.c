#include "hblk_crypto.h"

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t *sig)
{
	uint8_t *ptrLen = &sig->len;

	if(key == NULL || msg == NULL)
	{
		fprintf(stderr, "key or message is null\n");
		free(ptrLen);
		return NULL;
	}

	*ptrLen = ECDSA_size(key);
	if(!(ECDSA_sign(0,(const unsigned char *)msg,msglen,sig->sig,(unsigned int *)ptrLen,(EC_KEY *)key)))
	{
		fprintf(stderr, "failed to sign message\n");
		free(ptrLen);
		return NULL;
	}

	if(sig->sig == NULL)
	{
		fprintf(stderr, "unsigned signature\n");
		free(ptrLen);
		return NULL;
	}
	return sig->sig;

}
