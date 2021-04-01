#include "hblk_crypto.h"

uint8_t *ec_sign(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t *sig)
{
	uint8_t *ptrLen = &sig->len;

	if(key == NULL || msg == NULL)
	{

		free(ptrLen);
		return NULL;

	}

	*ptrLen = ECDSA_size(key);
	if(!(ECDSA_sign(0,(const unsigned char *)msg,msglen,sig->sig,(unsigned int *)ptrLen,(EC_KEY *)key)))
	{

		free(ptrLen);
		return NULL;

	}

	if(sig->sig == NULL)
	{

		free(ptrLen);
		return NULL;

	}

	return sig->sig;

}
