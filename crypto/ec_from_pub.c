#include "hblk_crypto.h"

EC_KEY *ec_from_pub(uint8_t const pub[EC_PUB_LEN])
{
	EC_KEY *key = NULL;
	EC_POINT *pubPnt = NULL;
	const EC_GROUP *group = NULL;
	if(!pub || NULL == (key = EC_KEY_new_by_curve_name(EC_CURVE)))
	{

		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
		return NULL;

	}
	group = EC_KEY_get0_group(key);
	pubPnt = EC_POINT_new(group);
	if(!pubPnt)
	{

		EC_KEY_free(key);
                EC_POINT_free(pubPnt);
                EC_GROUP_free((EC_GROUP*)group);
                return NULL;

	}
	if(!(EC_POINT_oct2point(group,pubPnt,pub,EC_PUB_LEN,NULL)))
	{

		
		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
		return NULL;

	}
	if(1 != EC_KEY_set_public_key(key, pubPnt))
	{

		EC_KEY_free(key);
		EC_POINT_free(pubPnt);
		EC_GROUP_free((EC_GROUP*)group);
                return NULL;

	}
	return key;
}
