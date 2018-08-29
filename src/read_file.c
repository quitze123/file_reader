#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#define SPACE 32
#define DEL 127

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
		perror("calloc(...) failed");
		exit(EXIT_FAILURE);
	}
	
	
	for(i = 0; i < array_current_size; i++)
	{
		files_data[i] = (char *)calloc(word_current_size, sizeof(char));
		if(files_data[i] == NULL)
		{
			perror("calloc(...) failed");
			exit(EXIT_FAILURE);
		}
	}
	
	return files_data;
}

void resize_row(char ** files_data, int word_current_size)
{
	word_current_size = word_current_size * 2;
	
	char * temp = realloc(*files_data, word_current_size * sizeof(char));
	if(temp == NULL)
	{
		perror("malloc(...) failed");
		exit(EXIT_FAILURE);
	}
	
	*files_data = temp;
}

char ** resize_col(char ** files_data, int * array_current_size, int current_pos)
{
	int i = 0;
	int word_size = 100;
	
	*array_current_size = *array_current_size * 2;
	
	char ** temp = (char **)realloc(files_data, *array_current_size * sizeof(char *));
	if(temp == NULL)
	{
		perror("realloc(...) failed");
		exit(EXIT_FAILURE);
	}
	
	files_data = temp;
	
	for(i = current_pos; i < *array_current_size; i++)
	{
		files_data[i] = calloc(word_size, sizeof(char));
		if(files_data[i] == NULL)
		{
			perror("calloc(...) failed");
			exit(EXIT_FAILURE);
		}
	}
	
	return files_data;
}

int resize_col_test(char *** files_data, int array_current_size, int current_pos)
{
	int i = 0;
	int word_size = 100;
	
	array_current_size = array_current_size * 2;
	
	char ** temp = (char **)realloc((*files_data), array_current_size * sizeof(char *));
	if(temp == NULL)
	{
		perror("realloc(...) failed");
		exit(EXIT_FAILURE);
	}
	
	(*files_data) = temp;
	
	for(i = current_pos; i < array_current_size; i++)
	{
		(*files_data)[i] = calloc(word_size, sizeof(char));
		if((*files_data)[i] == NULL)
		{
			perror("calloc(...) failed");
			exit(EXIT_FAILURE);
		}
	}
	
	return array_current_size;
}

char ** read_words(FILE * f_ptr)
{
	int array_current_size = 2;
	int word_current_size = 100;
	
	int array_pos = 0;
	int char_pos = 0;
	
	int c = 0;
	int i = 0;
	
	char ** files_data = init_array(array_current_size, word_current_size);
	
	while(1)
	{	
		c = fgetc(f_ptr);
		
		if(c > SPACE && c < DEL)
		{
			while(c > SPACE && c < DEL)
			{
				files_data[array_pos][char_pos] = c;
				char_pos++;
				
 				if(char_pos == word_current_size)
					resize_row(&files_data[array_pos], word_current_size);
				
				c = fgetc(f_ptr);
			}
			
			files_data[array_pos][char_pos] = '\0';
			
			array_pos++;
			
 			if(array_pos == array_current_size)
			{
				//files_data = resize_col(files_data, &array_current_size, array_pos);
				array_current_size = resize_col_test(&files_data, array_current_size, array_pos);
			}
			char_pos = 0;
		}
		
		if(c == EOF)
			break;
	}
	
	fclose(f_ptr);
	
	c = 0;
	while(c < array_current_size)
	{
		printf("%s\n", files_data[c]);
		c++;
	}
	
	return files_data;
}


int main(int argc, char ** argv)
{
	FILE * f_ptr;
	char ** files_data;
	if(argc != 1)
	{
		f_ptr = open_file(argv[1]);
		files_data = read_words(f_ptr);
	}
	else
	{
		fprintf(stdout, "Usage : ./run input_file_name\n");
	}
	return 0;
}