#include"hblk_crypto.h"

int ec_save(EC_KEY *key, char const *folder)
{
	char pubKeyPath[PATH_MAX] ;
	char privKeyPath[PATH_MAX];
	char separ = '/';
	struct stat st = {0};
	int dirExist ;
	FILE *fpub;
	FILE *fpri;

	if(key == NULL)
	{
		return 0;
	}
	dirExist = stat(folder, &st);
	#ifdef _WIN32

		separ='\\';
		if(dirExist == -1 )
		{
			if(!_mkdir(folder))
			{
				fprintf(stderr, "folder creation failed\n");
				return 0;
			}
		}

	#elif __linux__

		if(dirExist == -1 )
		{
			if(mkdir(folder, 0755) == -1)
			{
				fprintf(stderr, "folder creation failed\n");
				return 0;
			}
		}

	#endif

	snprintf(pubKeyPath, PATH_MAX, "%s%c%s", folder,separ,PUB_FILENAME);
	snprintf(privKeyPath, PATH_MAX, "%s%c%s", folder,separ,PRI_FILENAME);
	fprintf(stderr, "1save----------------->%d\n%s\n",EC_KEY_check_key(key),pubKeyPath);
	fpub = fopen(pubKeyPath, "w+");
	if(!(PEM_write_EC_PUBKEY(fpub, key)))
	{
		fprintf(stderr, "public key creation failed\n");
		fclose(fpub);
		return 0;
	}
	fclose(fpub);

	fpri = fopen(privKeyPath, "w+");
	if(!(PEM_write_ECPrivateKey(fpri,key,NULL,NULL,0, NULL,NULL)))
	{
		fprintf(stderr, "private creation failed\n");
                fclose(fpri);
                return 0;
	}
	fprintf(stderr, "----------------->%d\n",EC_KEY_check_key(key));
	fclose(fpri);
	return 1;
}


