#include "parser.h"


void test_foo()
{
	printf(TRANSPARENT_COLOR "test_foo() start\n" RESET_COLOR);

	FILE* fp = fopen("../test.csv", "r");

	// type array[ROWS][COLUMNS];

	uint32_t result_rows = 0;
	const uint32_t RESULT_COLUMNS = 60;

	uint16_t itr = 0;
	char buf[256];
	while(fgets(buf, 256, fp) != NULL)
	{
		if (itr == RESULT_COLUMNS)
		{
			itr = 0;
			result_rows++;
		}

		itr++;
	}

	if (itr != 0)
	{
		result_rows++;
		itr = 0;
	}

	for (uint16_t i = 0; i < 256; i++)
	{
		buf[i] = '\0';
	}

	rewind(fp);

	uint32_t** result = malloc(sizeof(result) * result_rows);
	for (uint32_t i = 0; i < result_rows; i++)
	{
		result[i] = malloc(sizeof(*result) * RESULT_COLUMNS);
	}


	uint32_t temp_rows = 0;
	uint32_t temp_columns = 0;
	char bitcoin_value_str[34];
	while(fgets(buf, 256, fp) != NULL)
	{
	//	printf(YELLOW "buffer:" RESET_COLOR " %s", buf);

		itr = 0;
		for (uint16_t i = 11; i < 256; i++)
		{
			if (buf[i] == ',')
			{
				buf[itr] = '\0';
				break;
			}
			bitcoin_value_str[itr] = buf[i];
			itr++;
		}

	//	printf(YELLOW "bitcoin value:" RESET_COLOR " %s\n", bitcoin_value_str);

		if (temp_columns == RESULT_COLUMNS)
		{
			temp_columns = 0;
			temp_rows++;
		}
	//	printf("old rows: %d\n", result_rows);
	//	printf("new rows: %d\n", temp_rows);
	//	printf("old columns: %d\n", RESULT_COLUMNS);
	//	printf("new columns: %d\n\n", temp_columns);

		result[temp_rows][temp_columns] = strtol(bitcoin_value_str, nullptr, 10);
	//	printf(YELLOW "(pre) result[%d]:" RESET_COLOR " %d\n\n", line_counter, result[line_counter]);

		for (uint16_t i = 0; i < 256; i++)
		{
			if (i < 34)
			{
				bitcoin_value_str[i] = '\0';
			}

			buf[i] = '\0';
		}

		temp_columns++;
	}


	fclose(fp);

	for (uint32_t i = 0; i < result_rows; i++)
	{
		for (uint32_t j = 0; j < RESULT_COLUMNS; j++)
		{
			printf(YELLOW "(after) result[%d][%d]:" RESET_COLOR " %d\n", i, j, result[i][j]);
		}
	}

	for (uint32_t i = 0; i < result_rows; i++)
	{
		free(result[i]);
	}
	free(result);

	printf("RESULT_COLUMNS: %d\n", result_rows);
	printf("RESULT_COLUMNS: %d\n", RESULT_COLUMNS);


	printf(TRANSPARENT_COLOR "test_foo() end\n" RESET_COLOR);
}
