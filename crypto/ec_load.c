#include "hblk_crypto.h"

EC_KEY *ec_load(char const *folder)
{
	EC_KEY *key = NULL;
	char pubKeyPath[PATH_MAX];
	char privKeyPath[PATH_MAX];
	struct stat st = {0};
	char separ = '/';
	int Exist ;
	FILE *fpub = NULL;
	FILE *fpri = NULL;
	
	Exist = stat(folder, &st);
	if(Exist == -1)
	{
		fprintf(stderr, "folder does not exist\n");
		return NULL; 
	}

	#ifdef _WIN32
		separ="\\";
	#endif

	snprintf(pubKeyPath, PATH_MAX , "%s%c%s", folder,separ,PUB_FILENAME);
	snprintf(privKeyPath, PATH_MAX, "%s%c%s", folder,separ,PRI_FILENAME);

	if(stat(pubKeyPath, &st) == -1 || stat(privKeyPath, &st) == -1)
	{
		fprintf(stderr, "publik key or private key files does not exist\n");
		EC_KEY_free(key);
		return NULL;
	}

	if(NULL == (key = EC_KEY_new_by_curve_name(EC_CURVE)))
	{
		fprintf(stderr, "failed to create key\n");
		return NULL;
	}

	fpri = fopen(privKeyPath,"r");
	if(!(PEM_read_ECPrivateKey(fpri,&key,NULL, NULL)))
	{
		fprintf(stderr, "failed to read private key\n");
		fclose(fpri);
		EC_KEY_free(key);
		return NULL;
	}
	fclose(fpri);
	
	fpub = fopen(pubKeyPath,"r");
	if(!(PEM_read_EC_PUBKEY(fpub,&key,NULL, NULL)))
	{
		fprintf(stderr, "failed to read public key\n");
		fclose(fpub);
		EC_KEY_free(key);
		return NULL;
	}
	fclose(fpub);
	return key;	
}

