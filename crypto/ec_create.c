#include "hblk_crypto.h"

EC_KEY *ec_create(void)
{

        EC_KEY *ek = NULL;
        ek = EC_KEY_new_by_curve_name(NID_secp256k1);
        if(ek == NULL)
        {

                return NULL;

        }
        if (!(EC_KEY_generate_key(ek)))
        {
                EC_KEY_free(ek);
                return NULL;

        }
        return ek;

}

