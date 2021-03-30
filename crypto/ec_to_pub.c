#include "hblk_crypto.h"

uint8_t *ec_to_pub(EC_KEY const *key, uint8_t pub[EC_PUB_LEN])
{

	const EC_POINT *pubPnt = NULL;
	const EC_GROUP *group = NULL;
	if(!key || !pub)
	{

		fprintf(stderr, "key null or pub\n");
		return NULL;

	}
	pubPnt = EC_KEY_get0_public_key(key);
	group = EC_KEY_get0_group(key);
	if(!(EC_POINT_point2oct(group,pubPnt,POINT_CONVERSION_UNCOMPRESSED,pub,EC_PUB_LEN,NULL)))
	{

		fprintf(stderr, "poin2bn does not work\n");
		return NULL;

	}
	return pub;
	
}
