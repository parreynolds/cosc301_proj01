/*
 *
 * Parker Reynolds
 * 28 September 2014
 * Worked wtih: Courtney McGill
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "list.h"

void process_data(FILE *input_file) {
    // !! your code should start here.  the input_file parameter
    // is an already-open file.  you can read data from it using
    // the fgets() C library function.  close it with the fclose()
    // built-in function

    struct rusage usage;


    struct node *list = malloc(sizeof(struct node*));
    list = list->next;

    char filestream[2000000];

    if (input_file == stdin){
	printf("Input a list of numbers \n");
	while(fgets(filestream, 2000000, stdin)!= NULL){
		int slen = strlen(filestream);
		filestream[slen-1] = '\0';

		char *token = strtok(filestream, " \t\n");
    		if(token!=NULL){
			int counter = 0;
			for(int i=0; i<strlen(token); i++){
				if(i==0 && (isdigit(token[i]) || token[i]=='-')){
					counter++;
				}
				else if(isdigit(token[i])){
					counter++;
				}
			}
			if (counter == strlen(token)){
				int num = atoi(token);
				list_append(num, &list);
			}
    		}
    
    		while(token!=NULL){
			token = strtok(NULL," \t\n");
			if (token!=NULL){
				int counter = 0;
				for(int i=0; i<strlen(token); i++){
					if(i==0 && (isdigit(token[i]) || token[i]=='-')){
						counter++;
					}
					else if(isdigit(token[i])){
						counter++;
					}
				}
				if (counter == strlen(token)){
					int num = atoi(token);
				        list_append(num, &list);
				}
			}
    		}
	}
	fflush(stdout);
    }

    else{
        while(fgets(filestream, 2000000, input_file)!=NULL){
		int slen = strlen(filestream);
		filestream[slen-1] = '\0';

		char *token = strtok(filestream," \t\n");
    		if(token!=NULL){
			int counter = 0;
			for(int i=0; i<strlen(token); i++){
				if(i==0 && (isdigit(token[i]) || token[i]=='-')){
					counter++;
				}
				else if(isdigit(token[i])){
					counter++;
				}
			}
			if (counter == strlen(token)){
				int num = atoi(token);
				list_append(num, &list);
			}
                        if (token[0] == '#'){
				token = strtok(NULL, "\n");
			}
    		}
    
    		while(token!=NULL){
			token = strtok(NULL," \t\n");
			if (token!=NULL){
				int counter = 0;
				for(int i=0; i<strlen(token); i++){
					if(i==0 && (isdigit(token[i]) || token[i]=='-')){
						counter++;
					}
					if(isdigit(token[i])){
						counter++;
					}
				}
				if (counter == strlen(token)){
					int num = atoi(token);
				        list_append(num, &list);
				}
				if (token[0] == '#'){
					token = strtok(NULL, "\n");
				}
			}
    		}
	}
	fflush(stdout);
    }
    
    list_sort(&list);
    list_print(list);
    list_clear(list);
  
    getrusage(RUSAGE_SELF, &usage);
    if (getrusage(RUSAGE_SELF, &usage) == -1){
	fprintf(stderr, "Error with getrusage");
        exit(1);
    }
    printf("User time: %ld.%09ld\n", usage.ru_utime.tv_sec, usage.ru_utime.tv_usec);
    printf("System time: %ld.%09ld\n", usage.ru_stime.tv_sec, usage.ru_utime.tv_usec);
   
}


void usage(char *program) {
    fprintf(stderr, "usage: %s [<datafile>]\n", program);
    exit(1);
}

#ifndef AUTOTEST
int main(int argc, char **argv) {
    FILE *datafile = NULL;

    /* find out how we got invoked and deal with it */
    switch (argc) {
        case 1:
            /* only one program argument (the program name) */ 
            /* just equate stdin with our datafile */
            datafile = stdin;        
            break;

        case 2:
            /* two arguments: program name and input file */
            /* open the file, assign to datafile */
            datafile = fopen(argv[1], "r");
            if (datafile == NULL) {
                printf("Unable to open file %s: %s\n", argv[1], strerror(errno));
                exit(-1);
            }
            break;

        default:
            /* more than two arguments?  throw hands up in resignation */
            usage(argv[0]);
    }

    /* 
     * you should be able to just read from datafile regardless 
     * whether it's stdin or a "real" file.
     */
    process_data(datafile);
    fclose(datafile);
    return 0;
}
#endif
