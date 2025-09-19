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
// 2 = good;
int8_t findFile(const char *const directory, const char *const name, char *const buffer, const int buffer_len)
{
	//fprintf(stderr, "Start with:\033[0m dir: \033[33m%s \033[0mname: \033[35m%s\033[0m\n", directory, name);
	DIR *pOpenDirectory;
	struct dirent *pDirent;

	errno = 0;
	pOpenDirectory = opendir(directory);

	uint32_t item_count = 0;
	char** itemList = nullptr;

	if (pOpenDirectory == nullptr)
	{
	//	fprintf(stderr, "\033[34m%s \033[0m%s\n", directory, strerror(errno));
	}
	else
	{
		while (true)
		{
			pDirent = readdir(pOpenDirectory);
			if (pDirent == nullptr )
			{
				break;
			}
			else
			{
				if (strcmp(pDirent->d_name, name) == 0)
				{
					getcwd(buffer, buffer_len);
					strncat(buffer, "/", 1);
					strncat(buffer, directory, strlen(directory));
					strncat(buffer, "/", 1);
					strncat(buffer, name, strlen(name));
					return 2;
				}
				if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
				{
					continue;
				}
				item_count++;
			}
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
			else
			{
				if (strcmp(pDirent->d_name, ".") == 0 || strcmp(pDirent->d_name, "..") == 0)
				{
					continue;
				}
				itemList[i] = malloc(sizeof(**itemList) * (strlen(pDirent->d_name)+1));
			//	fprintf(stderr, "\033[35md_name\033[0m %ld: %s\n", sizeof(**itemList) * (strlen(pDirent->d_name)), pDirent->d_name);
				memcpy(itemList[i], pDirent->d_name, strlen(pDirent->d_name)+1);
			//	fprintf(stderr, "\033[35mitemList\033[0m %ld: \033[2m\033[35m%s\033[0m\n", strlen(itemList[i]), itemList[i]);
			}
			i++;
		}
		closedir(pOpenDirectory);
	}

	for (uint32_t i = 0; i < item_count; i++)
	{
	//	fprintf(stderr, "\033[33m%s \033[34m%d \033[35m%s\033[0m\n", directory, i, itemList[i]);
		chdir(directory);
		if (findFile(itemList[i], name, buffer, 1024) == 2)
		{
			return 2;
		}
		if (strcmp(directory, ".") != 0)
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

	return 0;
}
