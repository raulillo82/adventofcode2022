#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "day3_data.txt"
#define LENGTH 300
#define LINE 50

void split_line (char *line, char *subline1, char *subline2);
char lookup_common_char (const char *subline1, const char *subline2);
char lookup_common_char3 (const char *line1, const char *line2, const char *line3);

void split_line (char *line, char *subline1, char *subline2){
	int len = strlen (line), i;
	//First substring, copied char by char
	for (i = 0; i < len / 2; i ++)
		*(subline1 + i) = *(line + i);
	//Add termination char
	*(subline1 + i) = '\0';
	//Second substring
	for (i = 0; i < len / 2; i ++)
		*(subline2 + i) = *(line + i + len / 2);
	//Add termination char
	*(subline2 + i) = '\0';
	//subline2 = (line + len / 2);
	//printf ("Substring 1 is %s and substring 2 is %s\n", subline1, subline2);
}
char lookup_common_char (const char *subline1, const char *subline2){
	char common_char = '\0';
	int found = 0, len = strlen(subline1), i = 0, j = 0;
	printf ("Substring 1 is %s and substring 2 is %s\n", subline1, subline2);
	while (!found && i < len){
		//printf ("Checking for char in position %d of substring1 which is %c\n", i, *(subline1 + i));
		j = 0;
		while (!found && j < len){
			//printf ("Comparing to char in position %d of substring2 which is %c\n", j, *(subline2 + j));
			if (*(subline1 + i) == *(subline2 + j)){
				common_char = *(subline1 + i);
				found = 1;
				printf ("Common char found!\n");
			}
			else
				j ++;
		}
		if (!found)
			i ++;
	}
	printf ("Common character found was %c\n", common_char);
	return (common_char);
}

char lookup_common_char3 (const char *line1, const char *line2, const char *line3){
	char common_char = '\0';
	printf ("Common character found was %c\n", common_char);
	return (common_char);
}
int main(void)
{
	FILE * fp;
	char * line = NULL;
	size_t len = 0;
	ssize_t read;
	int total_points = 0, num_lines = 0;
	char ** lines;

	lines = malloc (sizeof(char*) * LENGTH); 
	for (int i = 0; i < LENGTH; i ++)
		*(lines + i) = malloc (sizeof(char) * LINE);


	fp = fopen(FILENAME, "r");
	if (fp == NULL)
		exit(EXIT_FAILURE);

	while ((read = getline(&line, &len, fp)) != -1) {
		strcpy (*(lines + num_lines), line);
		num_lines ++;
		printf("Retrieved line of length %zu:\n", read);
		printf("%s", line);
		int line_points = 0;
		char common_char = '\0';
		//Split line in two equal parts
		char *subline1, *subline2;
		subline1 = malloc (sizeof(char) * len / 2);
		subline2 = malloc (sizeof(char) * len / 2);
		split_line (line, subline1, subline2);
		//Look for common item in both parts
		common_char = lookup_common_char (subline1, subline2);
		//Compute points
		if (common_char >= 'a' && common_char <= 'z')
		       line_points = ((int) (common_char - 'a')) + 1;	
		else if (common_char >= 'A' && common_char <= 'Z')
		       line_points = ((int) (common_char - 'A')) + 27;	
		else
			exit(EXIT_FAILURE);

		total_points += line_points;

		printf ("Line points given for common char %c are %d. Accumulated points are %d\n", common_char, line_points, total_points);



		if (subline1)
			free (subline1);
		if (subline2)
			free (subline2);
	}

	printf ("\nTotal points are: %d\n", total_points);

	//Second part of the game to be implemented here
	//Create new functions that look up common char in three lines

	/*for (int i = 0; i < num_lines; i ++)
		printf ("%s", *(lines + i));*/
	fclose(fp);
	if (line)
		free(line);
	for (int i = 0; i < LENGTH; i ++)
		if (*(lines + i))
			free (*(lines + i));
	if (lines)
		free (lines);
	exit(EXIT_SUCCESS);
}
