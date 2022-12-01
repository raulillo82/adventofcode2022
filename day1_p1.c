#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day1_p1_data.txt"

void num_lines_and_blak_lines_file (char *file_name, int *lines, int *blank_lines);
int find_index_max (int *list, int num_elems);

void num_lines_and_blak_lines_file (char *file_name, int *lines, int *blank_lines){
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int count_lines = 0, count_blank_lines = 0;
	//Open file, handle errors
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);
	while ((read = getline(&line, &len, fp)) != -1) {
		count_lines ++;
		if (!strcmp(line, "\n"))
			count_blank_lines ++;		
	}
	//Close file
	fclose(fp);
	//Free memory
	if (line)
		free(line);
	*lines = count_lines;
	*blank_lines = count_blank_lines;
}

int find_index_max (int *list, int num_elems){
	int index = 0;
	int max = 0;
	for (int i = 0; i < num_elems; i ++)
		if (*(list + i) > max){
			index = i;
			max = *(list + i);
		}
	return (index);
}
int main (){
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int lines, blank_lines;
	int *elfs_calories = NULL;
	int index = 0, index_max;

	//Count number of lines in file & number of blank lines in file
	num_lines_and_blak_lines_file (FILENAME, &lines, &blank_lines);

	//Reserve memory according to number of elfs = blank_lines + 1
	elfs_calories = malloc (sizeof(int)*(blank_lines+1));
	//Initialize array, each elf carries 0 calories at the beginning
	for (int i = 0; i < blank_lines + 1; i ++)
		*(elfs_calories + i) = 0;

	//Open file, handle errors
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//Probably to be moved into its own function
	//Read one line and stop in EOF (-1)
	while ((read = getline(&line, &len, fp)) != -1) {
		//If line is not blank, add its value to already stored value
		if (strcmp(line, "\n"))
			*(elfs_calories + index) += atoi(line);	
		//Otherwise, ignore the line and increase the index
		else
			index ++;
		//printf("Retrieved line of length %zu:\n", read);
		//printf("%s", line);
	}
	
	//Print array
	/*
	for (int i = 0; i < index; i++)
		printf ("Elf number %d is carrying %d calories\n", i, *(elfs_calories + i));
	*/

	//Find index of elf with max calories
	index_max = find_index_max (elfs_calories, blank_lines + 1);
	
	printf ("Elf with index %d has the most calories, which are %d\n", index_max, *(elfs_calories + index_max));

	//Close file
	fclose(fp);
	//Free memory
	if (line)
		free(line);
	if (elfs_calories)
		free(elfs_calories);
	exit(EXIT_SUCCESS);
}
