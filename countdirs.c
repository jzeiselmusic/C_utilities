#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>



int main (int argc, char **argv){

	// this function will count the number of files in the provided folder path.

	// will count folders as files 
	// ignores hidden files

	// if no argument is provided, will look for generic files in current folder

	// otherwise, first argument should be folder path and 
	// second argument (optional) should be type of file to scan for.
	// if provided '.jpg' will only return number of jpg files etc etc

	struct dirent **namelist;
	int n;
	int count = 0;

	if (argc < 1) {
		exit(EXIT_FAILURE);
	}
	else if (argc == 1) {
		n = scandir(".",&namelist,NULL,alphasort);
		if (n < 0) {
			perror("scandir");
			exit(EXIT_FAILURE);
		}
		else {
			while (n--) {
				if ((strcmp(namelist[n]->d_name,".DS_Store") != 0 ) && \
				(strcmp(namelist[n]->d_name, ".")!=0) && \
				(strcmp(namelist[n]->d_name,"..")!=0) && \
				(namelist[n]->d_name[0] != '.')){
								
					count ++;
				}
			}
			printf("number of files here is: %d\n",count);
		}
	}
	else if (argc == 2) {
		n = scandir(argv[1],&namelist,NULL,alphasort);
		if (n < 0) {
			perror("scandir");
			exit(EXIT_FAILURE);
		}
		else {
			while (n--) {
				if ((strcmp(namelist[n]->d_name,".DS_Store")!=0) && \
				(strcmp(namelist[n]->d_name,".")!=0) && \
				(strcmp(namelist[n]->d_name,"..")!=0) && \
				(namelist[n]->d_name[0] != '.')){

				count ++;

				}
			}
		printf("number of files is in folder is: %d\n",count);
		}
	}
	else if (argc == 3) {
		n = scandir(argv[1], &namelist, NULL, alphasort);
		if (n < 0) {
			perror("scandir");
			exit(EXIT_FAILURE);
		}
		else {

			while (n--) {
				if ((strcmp(namelist[n]->d_name,".DS_Store")!=0) && \
				(strcmp(namelist[n]->d_name,".")!=0) && \
				(strcmp(namelist[n]->d_name,"..")!=0) && \
				(namelist[n]->d_name[0] != '.')) {
					
					char *name = namelist[n]->d_name;
					char *filetype = argv[2];
					int filetype_len = strlen(filetype);
					int name_len = strlen(name);
					int i = 0;		
					while (filetype_len) {
						if (name[name_len - filetype_len] == filetype[i]) {
							i++;
							filetype_len --;
						}
						else {
							break;
						}
					}
					if (filetype_len==0) {
						count ++;
					}
				}
			}
		printf("number of files (in this location, of this type) is: %d\n",count);
		}
	}

	exit(EXIT_SUCCESS);

}
