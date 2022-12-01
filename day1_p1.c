#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day1_p1_data.txt"

void num_lines_and_blank_lines_file (char *file_name, int *lines, int *blank_lines);
int find_index_max (int *list, int num_elems);
void find_index_3_max (int *list, int num_elems, int *index_3_max);

/*Count the number of total lines and blank lines of a file*/
void num_lines_and_blank_lines_file (char *file_name, int *lines, int *blank_lines){
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

/*Find the index containing the maximum of a (positive) int array*/
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

/*Find the indexes of the 3 biggest (positive) int elements in the array, store them in "index_3_max"*/
void find_index_3_max (int *list, int num_elems, int *index_3_max){
	int first = 0, second = 0, third = 0;
	for (int i = 0; i < 3; i ++)
		*(index_3_max + i) = 0;
	for (int i = 0; i < num_elems; i ++){
		//If bigger than the (so far) biggest element
		if (*(list+i) > first){
			third = second;
			*(index_3_max+2) = *(index_3_max+1);
			second = first;
			*(index_3_max+1) = *index_3_max;
			first = *(list+i);
			*index_3_max = i;
		}
		//If smaller than the biggest element but bigger than the second
		else if (*(list+i) > second){
			third = second;
			*(index_3_max+2) = *(index_3_max+1);
			second = *(list+i);
			*(index_3_max+1) = i;
		}
		//If smaller than the second biggest element but bigger than the third
		else if (*(list+i) > third){
			third = *(list+i);
			*(index_3_max+2) = i;
		}
		//In all cases, values and indexes are stored. Values won't be used after this function as their value can be easily retrieved
	}
}

int main (){
	FILE *fp;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int lines, blank_lines;
	int *elves_calories = NULL;
	int index = 0, index_max;
	int *index_3_max = NULL; //Indexes of the 3 biggest elements
	
	index_3_max = malloc(sizeof(int) * 3);

	//Count number of lines in file & number of blank lines in file
	num_lines_and_blank_lines_file (FILENAME, &lines, &blank_lines);

	//Reserve memory according to number of elfs = blank_lines + 1
	elves_calories = malloc (sizeof(int)*(blank_lines+1));
	//Initialize array, each elf carries 0 calories at the beginning
	for (int i = 0; i < blank_lines + 1; i ++)
		*(elves_calories + i) = 0;

	//Open file, handle errors
	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	//Probably to be moved into its own function
	//Read one line and stop in EOF (-1)
	while ((read = getline(&line, &len, fp)) != -1) {
		//If line is not blank, add its value to already stored value
		if (strcmp(line, "\n"))
			*(elves_calories + index) += atoi(line);	
		//Otherwise, ignore the line and increase the index
		else
			index ++;
		//printf("Retrieved line of length %zu:\n", read);
		//printf("%s", line);
	}
	
	//Print array
	/*
	for (int i = 0; i < index; i++)
		printf ("Elf number %d is carrying %d calories\n", i, *(elves_calories + i));
	*/

	//Find index of elf with max calories
	index_max = find_index_max (elves_calories, blank_lines + 1);
	
	printf ("Elf with index %d has the most calories, which are %d\n", index_max, *(elves_calories + index_max));

	//Find indexes of elves with maximum calories
	find_index_3_max (elves_calories, blank_lines + 1, index_3_max);
	for (int i = 0; i < 3; i++)
		printf ("Elf with index %d is one of the top 3 with most calories, which are %d\n", *(index_3_max+i), *(elves_calories + *(index_3_max+i)));
	printf ("Total calories carried by the top 3 elves are %d\n", *(elves_calories + *(index_3_max)) + 
			*(elves_calories+*(index_3_max+1)) + *(elves_calories+*(index_3_max+2)));

	//Close file
	fclose(fp);
	//Free memory
	if (line)
		free(line);
	if (elves_calories)
		free(elves_calories);
	if (index_3_max)
		free(index_3_max);
	exit(EXIT_SUCCESS);
}
