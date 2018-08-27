#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

FILE * open_file(char * input_file_name)
{
	FILE * f_ptr;
	if(input_file_name == NULL)
		return NULL;
	
	f_ptr = fopen(input_file_name, "r");
	
	if(f_ptr == NULL)
	{
		perror("Error");
		exit(EXIT_FAILURE);
	}
	
	return f_ptr;
}

char ** init_array(int array_current_size, int word_current_size)
{
	int i = 0;
	
	char ** files_data = (char **)calloc(array_current_size , sizeof(char *));
	if(files_data == NULL)
	{
		fprintf(stderr, "calloc(...) failed.");
		exit(EXIT_FAILURE);
	}
	
	
	for(i = 0; i < array_current_size; i++)
	{
		files_data[i] = (char *)calloc(word_current_size, sizeof(char));
		if(files_data[i] == NULL)
		{
			fprintf(stderr, "calloc(...) failed.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	return files_data;
}

char ** read_file(FILE * f_ptr)
{
	int array_current_size = 100;
	int word_current_size = 256;
	
	int char_pos = 0;
	int array_pos = 0;
	
	int copy_data = 0;
	
	int c = 0;
	
	char ** files_data = init_array(array_current_size, word_current_size);
	
	while((c = fgetc(f_ptr))  != EOF)
	{
		if(c == '\n' || c == ' ')
		{
			copy_data = 0;
		}
		else
		{
			copy_data = 1;
		}
		
		if(copy_data == 1)
		{
			files_data[array_pos][char_pos] = c;
			char_pos++;
			copy_data = 0;
		}
		
	}
	
	c = 0;
	while(c < array_current_size)
	{
		printf("%s\n", files_data[c]);
		c++;
	}
	
	fclose(f_ptr);
}


int main(int argc, char ** argv)
{
	FILE * f_ptr;
	char ** files_data;
	if(argc != 1)
	{
		f_ptr = open_file(argv[1]);
		files_data = read_file(f_ptr);
	}
	else
	{
		fprintf(stdout, "Usage : ./run input_file_name\n");
	}
	return 0;
}