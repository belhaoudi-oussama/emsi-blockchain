#include"hblk_crypto.h"

int ec_save(EC_KEY *key, char const *folder)
{
	char pubKeyPath[PATH_MAX] ;
	char privKeyPath[PATH_MAX];
	char separ = '/';
	struct stat st = {0};
	int dirExist ;
	FILE *fpub = NULL;
	FILE *fpri = NULL;
	
	
	dirExist = stat(folder, &st);
	#ifdef _WIN32

		separ='\\';
		if(dirExist == -1 )
		{
			if(!_mkdir(folder))
			{
				free(fpub);
				free(fpri);
				return 0;
			}	
		}

	#elif __linux__

		if(dirExist == -1 )
		{
			if(mkdir(folder, 0755) == -1)
			{
				free(fpub);
				free(fpri);
				return 0;
			}
		}
	
	#endif
	
	snprintf(pubKeyPath, PATH_MAX + 1, "%s%c%s", folder,separ,PUB_FILENAME);
	snprintf(privKeyPath, PATH_MAX + 1, "%s%c%s", folder,separ,PRI_FILENAME);

	fpub = fopen (pubKeyPath, "w+");
	if(!(PEM_write_EC_PUBKEY(fpub, key)))
	{
		free(fpub);
		free(fpri);
		return 0;
	}
	fclose(fpub);

	fpri = fopen (privKeyPath, "w+");
	if(!(PEM_write_ECPrivateKey(fpri,key,NULL,NULL,0, NULL,NULL)))
	{
		free(fpri);
		return 0;
	}
	fclose(fpri);
	return 1;
	
}
