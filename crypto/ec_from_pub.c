#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;
	EC_POINT *pubPnt = NULL;
	const EC_GROUP *group = NULL;
	if(!pub || NULL == (key = EC_KEY_new_by_curve_name(EC_CURVE)))
	{
		fprintf(stderr, "public key or ec key is null\n");
		EC_KEY_free(key);
		return NULL;
	}
	fprintf(stderr, "public key or ec key is null\n");
	group = EC_KEY_get0_group(key);
	pubPnt = EC_POINT_new(group);

	if(!pubPnt)
	{
		fprintf(stderr, "failde to create point\n");
		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
		return NULL;
	}
	
	if(!(EC_POINT_oct2point(group,pubPnt,pub,EC_PUB_LEN,NULL)))
	{
		fprintf(stderr, "failed to convert the point\n");
		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
		return NULL;
	}

	if(1 != EC_KEY_set_public_key(key, pubPnt))
	{
		fprintf(stderr, "filed to set the private key\n");
		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
		return NULL;
	}
	return key;
}

