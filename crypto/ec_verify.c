#include "hblk_crypto.h"

int ec_verify(EC_KEY const *key, uint8_t const *msg, size_t msglen, sig_t const *sig)
{

	int res = 0;
	if(key == NULL || msg == NULL || sig == NULL)
	{

		return 0;

	}

	res = ECDSA_verify(0,(unsigned char *)msg,msglen,sig->sig,sig->len, (EC_KEY *)key);
	return res;
	
}
