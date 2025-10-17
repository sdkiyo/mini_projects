#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


// 0 = nothing
// -1 = is not directory, or other error.
// 2 = good
int8_t findFile(const char *const pDirectory, const char *const pName, char *const pBuffer, const int pBuffer_len)
{
	DIR *pOpenDirectory;
	struct dirent *pDirent;

	errno = 0;
	pOpenDirectory = opendir(pDirectory);

	uint32_t item_count = 0;
	char** itemList = nullptr;

	if (pOpenDirectory == nullptr)
	{
		return -1;
	}

	while (true)
	{
		pDirent = readdir(pOpenDirectory);

		if (pDirent == nullptr )
		{
			break;
		}

		if (strcmp(pDirent->d_name, pName) == 0)
		{
			getcwd(pBuffer, pBuffer_len);
			strncat(pBuffer, "/", 1);
			strncat(pBuffer, pDirectory, strlen(pDirectory));
			strncat(pBuffer, "/", 1);
			strncat(pBuffer, pName, strlen(pName));
			return 2;
		}

		if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
		{
			continue;
		}

		item_count++;
	}
	seekdir(pOpenDirectory, 0);
	itemList = malloc(sizeof(itemList) * item_count);

	int i = 0;
	while (true)
	{
		pDirent = readdir(pOpenDirectory);

		if (pDirent == nullptr )
		{
			break;
		}

		if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
		{
			continue;
		}

		itemList[i] = malloc(sizeof(**itemList) * (strlen(pDirent->d_name)+1));

		memcpy(itemList[i], pDirent->d_name, strlen(pDirent->d_name)+1);

		i++;
	}

	closedir(pOpenDirectory);

	for (uint32_t i = 0; i < item_count; i++)
	{
		chdir(pDirectory);

		if (findFile(itemList[i], pName, pBuffer, 1024) == 2)
		{
			for (uint32_t i = 0; i < item_count; i++)
			{
				free(itemList[i]);
			}
			free(itemList);
			return 2;
		}
		if (strcmp(pDirectory, ".") != 0)
		{
			chdir("..");
		}
	}

	for (uint32_t i = 0; i < item_count; i++)
	{
		free(itemList[i]);
	}
	free(itemList);
	return 0;
}


int main(const int argc, const char *const *const argv)
{
	char buffer[1024];
	int return_value = findFile(argv[1], argv[2], buffer, 1024);
	if (return_value == 2)
	{
		fprintf(stderr, "file are find: \033[36m%s\033[0m\n", buffer);
	}
	if (return_value == 0)
	{
		fprintf(stderr, "nothing.\n");
	}
	if (return_value == -1)
	{
		fprintf(stderr, "Could not open the specified directory\n");
	}

	return 0;
}
