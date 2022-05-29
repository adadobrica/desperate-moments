// Copyright 2022 Dobrica Nicoleta Adriana 311CA
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

#define MAX_STRING_SIZE 256

int add_last(void **arr, int *len, data_structure *data)
{
	// creating a temporary generic array

	void *tmp;
	tmp = realloc(*arr, *len + sizeof(head) + data->header->len);
	if (tmp == NULL) {
		return -1;
	}
	*arr = tmp;

	// firstly, we add the information we need to know about our data (its type and length)

	memcpy(*arr + *len, data->header, sizeof(head));

	// then we put the actual data into our array

	memcpy(*arr + *len + sizeof(head), data->data, data->header->len);

	*len = *len + sizeof(head) + data->header->len;
	return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{

	void *tmp;
	tmp = realloc(*arr, *len + sizeof(head) + data->header->len);
	if (tmp == NULL) {
		return -1;
	}
	*arr = tmp;

	// we need a current to help us traverse our array

	void *current = *arr;

	for (int i = 0; i < index; i++) {
		current = current + ((head *)current)->len + sizeof(head);

		// if the current index is bigger than our array

		if (current > *arr + *len) {
			return add_last(arr, len, data);
		}
	}

	// we allocate memory for our temporary array

	tmp = malloc(*len + *arr - current);

	// adding a new element into our array

	memcpy(tmp, current, *len + *arr - current);
	memcpy(current + data->header->len + sizeof(head), tmp, *len + *arr - current);
	memcpy(current, data->header, sizeof(head));
	memcpy(current + sizeof(head), data->data, data->header->len);

	*len = *len + sizeof(head) + data->header->len;
	free(tmp);
	return 0;
}

void find(void *data_block, int len, int index) 
{	
	// we iterate through our array until we find the element we want to print

	void *current = data_block;
	for (int i = 0; i < index; i++) {
		current = current + ((head *)current)->len + sizeof(head);
	}
	
	// printing the data in the specified format, treating individually each type

	printf("Tipul %c\n", ((head *)current)->type);
	
	if (((head *)current)->type == '1') {
		char *name1 = current + sizeof(head);
		int8_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
		int8_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int8_t);
		char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) +  2 * sizeof(int8_t);
		printf("%s pentru %s\n", name1, name2);
		printf("%"PRId8"\n", *num1);
		printf("%"PRId8"\n", *num2);
		printf("\n");
	} else if (((head *)current)->type == '2') {	
		char *name1 = current + sizeof(head);
		int16_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
		int32_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t);
		char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t) + sizeof(int32_t);
		printf("%s pentru %s\n", name1, name2);
		printf("%"PRId16"\n", *num1);
		printf("%"PRId32"\n", *num2);
		printf("\n");
	} else {
		char *name1 = current + sizeof(head);
		int32_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
		int32_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int32_t);
		char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1)  + 2 * sizeof(int32_t);
		printf("%s pentru %s\n", name1, name2);
		printf("%"PRId32"\n", *num1);
		printf("%"PRId32"\n", *num2);
		printf("\n");
	}
}

int delete_at(void **arr, int *len, int index)
{
	// finding the element we want to delete
	void *current = *arr;
	for (int i = 0; i < index; i++) {
		current = current + ((head *)current)->len + sizeof(head);
	}

	void *tmp = malloc(*len + *arr - current - sizeof(head) - ((head *)current)->len);

	// copying the next element into our temporary array

	memcpy(tmp, current + ((head *)current)->len + sizeof(head), *len + *arr - current - sizeof(head) - ((head *)current)->len);
	
	unsigned int aux = ((head *)current)->len;

	// deleting our current element

	memcpy(current, tmp, *len + *arr - current - sizeof(head) - ((head *)current)->len);

	// changing the size our array and then decreasing its length

	void *tmp2 = realloc(*arr, *len - sizeof(head) - aux);
	*arr = tmp2;
	*len = *len - sizeof(head) - aux;
	free(tmp);
	return 0;
}

void print(void *arr, int len) 
{
	// we iterate through our array and then print the data in the given format
	void *current = arr;
	while (current < arr + len) {	
		printf("Tipul %c\n", ((head *)current)->type);

		if (((head *)current)->type == '1') {
			char *name1 = current + sizeof(head);
			int8_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
			int8_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int8_t);
			char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) +  2 * sizeof(int8_t);
			printf("%s pentru %s\n", name1, name2);
			printf("%"PRId8"\n", *num1);
			printf("%"PRId8"\n", *num2);
			printf("\n");
		} else if (((head *)current)->type == '2') {	
			char *name1 = current + sizeof(head);
			int16_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
			int32_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t);
			char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t) + sizeof(int32_t);
			printf("%s pentru %s\n", name1, name2);
			printf("%"PRId16"\n", *num1);
			printf("%"PRId32"\n", *num2);
			printf("\n");
		} else {
			char *name1 = current + sizeof(head);
			int32_t *num1 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1);
			int32_t *num2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1) + sizeof(int32_t);
			char *name2 = current + sizeof(head) + sizeof(char) * (strlen(name1) + 1)  + 2 * sizeof(int32_t);
			printf("%s pentru %s\n", name1, name2);
			printf("%"PRId32"\n", *num1);
			printf("%"PRId32"\n", *num2);
			printf("\n");
		}
		current = current + sizeof(head) + ((head *)current)->len;
	}
}

int main() {
	void *arr = NULL;
	int len = 0, index;
	char *line = malloc(MAX_STRING_SIZE * sizeof(char *));
	char *name1, *name2, *num1, *num2, *type;
	char *command = malloc(MAX_STRING_SIZE * sizeof(char *));
	data_structure *manele_master = malloc(sizeof(data_structure));
	manele_master->header = malloc(sizeof(head));
	while (1) {
		scanf("%s", command);
		if (strcmp(command, "insert") == 0) {
			fgets(line, MAX_STRING_SIZE - 1, stdin);
			type = strtok(line, " ");
			if (type[0] - '0' == 1) {
				manele_master->header->type = '1';
			} else if (type[0] - '0' == 2) {
				manele_master->header->type = '2';
			} else {
				manele_master->header->type = '3';
			}
			name1 = strtok(NULL, " ");
			num1 = strtok(NULL, " ");
			num2 = strtok(NULL, " ");
			name2 = strtok(NULL, "\n");
			if (manele_master->header->type == '1') {
				int8_t n1 = atoi(num1);
				int8_t n2 = atoi(num2);
				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int8_t) + sizeof(int8_t);

				manele_master->data = malloc(manele_master->header->len);

				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int8_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int8_t), &n2, sizeof(int8_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + 2 * sizeof(int8_t), name2, sizeof(char) * (strlen(name2) + 1));
			} else if (manele_master->header->type == '2') {
				int16_t n1 = atoi(num1);
				int32_t n2 = atoi(num2);

				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t);

				manele_master->data = malloc(manele_master->header->len);
				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int16_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t), &n2, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t) + sizeof(int32_t), name2, sizeof(char) * (strlen(name2) + 1));
			} else {
				int32_t n1 = atoi(num1);
				int32_t n2 = atoi(num2);

				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int32_t) + sizeof(int32_t);

				manele_master->data = malloc(manele_master->header->len);
				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int32_t), &n2, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + 2 * sizeof(int32_t), name2, sizeof(char) * (strlen(name2) + 1));
			}
				
			add_last(&arr, &len, manele_master);
			free(manele_master->data);
		} else if (strcmp(command, "insert_at") == 0) {
			scanf("%d", &index);
			fgets(line, MAX_STRING_SIZE - 1, stdin);
			type = strtok(line, " ");
			if (type[0] - '0' == 1) {
				manele_master->header->type = '1';
			} else if (type[0] - '0' == 2) {
				manele_master->header->type = '2';
			} else {
				manele_master->header->type = '3';
			}
			name1 = strtok(NULL, " ");
			num1 = strtok(NULL, " ");
			num2 = strtok(NULL, " ");
			name2 = strtok(NULL, "\n");

			if (manele_master->header->type == '1') {
				int8_t n1 = atoi(num1);
				int8_t n2 = atoi(num2);
				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int8_t) + sizeof(int8_t);

				manele_master->data = malloc(manele_master->header->len);

				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int8_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int8_t), &n2, sizeof(int8_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + 2 * sizeof(int8_t), name2, sizeof(char) * (strlen(name2) + 1));
			} else if (manele_master->header->type == '2') {
				int16_t n1 = atoi(num1);
				int32_t n2 = atoi(num2);

				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int16_t) + sizeof(int32_t);

				manele_master->data = malloc(manele_master->header->len);
				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int16_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t), &n2, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int16_t) + sizeof(int32_t), name2, sizeof(char) * (strlen(name2) + 1));
			} else {
				int32_t n1 = atoi(num1);
				int32_t n2 = atoi(num2);

				manele_master->header->len = (strlen(name1) + 1) * sizeof(char) +
				(strlen(name2) + 1) * sizeof(char) + sizeof(int32_t) + sizeof(int32_t);

				manele_master->data = malloc(manele_master->header->len);
				memcpy(manele_master->data, name1, sizeof(char) * (strlen(name1) + 1));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1), &n1, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + sizeof(int32_t), &n2, sizeof(int32_t));
				memcpy(manele_master->data + sizeof(char) * (strlen(name1) + 1) + 2 * sizeof(int32_t), name2, sizeof(char) * (strlen(name2) + 1));
			}	


			add_at(&arr, &len, manele_master, index);
			free(manele_master->data);
		} else if (strcmp(command, "delete_at") == 0) {
			scanf("%d", &index);
			delete_at(&arr, &len, index);
		} else if (strcmp(command, "find") == 0) {
			scanf("%d", &index);
			find(arr, len, index);
		} else if (strcmp(command, "print") == 0) {
			print(arr, len);
		} else if (strcmp(command, "exit") == 0) {
			free(arr);
			free(manele_master->header);
			free(manele_master);
			free(line);
			free(command);
			break;
		}
	}
	return 0;
}