#include <stdio.h>
#include <string.h>
#include <dirent.h> //header file especially Linux
#include <stdlib.h>
#include <ctype.h>

static char buf[1000];
static int count = 0;
static char *dir_filenames[100];

int directory_files(){

    int length[20];     //file name length for all files
    int i = 0;
    int j = 0;
    int counter  = 0;   //number of files in dir

    DIR *d;             //pointer to wd
    struct dirent *dir;

    d = opendir(".");
	
    //this piece of code stores directory filenames in the dir_filenames
    if (d) {
        while ((dir = readdir(d)) != NULL){
            if(dir->d_name[0] != '.'){
                 dir_filenames[i] = dir->d_name;
                 i++;
            }
            counter=i;

        }
        closedir(d);
    }
    j = 0;
    for(i = 0 ; i<counter ; i++){
        length[i] = strlen(dir_filenames[i]);
	    
	//Among all the directory files and folders, we only select the required text files only
        if(dir_filenames[i][length[i]-1] == 't' && dir_filenames[i][length[i]-2] == 'x' && dir_filenames[i][length[i]-3] == 't'){
	  //set argv to files with txt only
	  dir_filenames[j] = dir_filenames[i];
	  printf("%s\n",dir_filenames[j]);
	  j++;
	}
    }

    counter = j;

    return counter;
    //checked and is true
}

//Comparing the entered string with each condition matching strings of text files
int compare_word(char *test_string, char *file_path,int init_count){

    int word_start = 0;
    int j = 0;
    count = 0;

    while(buf[j]){

        if(j == 0 || buf[j-1] == ' ' || buf[j-1] == '\n'){
            word_start = 1;
        }
        else word_start = 0;

        if(word_start){
            int m = j;
            int k = 0;
            while (test_string[k]){
                if(test_string[k] == buf[m]){
                    k++;
                    m++;
                }
                else break;
            }

            if (k == strlen(test_string)){
                count++;
            }
        }
        j++;
    }
    printf("%s has repeated %d no. of times in %s\n",test_string,count,file_path);

    return count;
}

//read_file function reads the different text files before comparing the strings and after text files are segregated
int read_file(char *file_path)
{
    FILE *ptr_file;

    ptr_file =fopen(file_path,"r");

    if (!ptr_file){
        return -1;
    }

    char *A;
    A = &buf[0];

    do {

        *A = fgetc(ptr_file);
        if (feof(ptr_file)) {
            break ;
        }

        ++A;
    } while(1);

    fclose(ptr_file);
    return 0;
}


int main(int argc,char **argv){

    int m = 0;
    int total = 0;
    int i = 0;
    char str[25];
    int count = 0;

    printf("The Text files in the directory are.:\n");
    m = directory_files();  //return value is the number of text files on the current directory
    printf("Enter the string you want to search.\n");
    scanf("%s",str);   //string to be searched

    for(i = 0 ; i < m ; i++){
      read_file(dir_filenames[i]);
      count =  compare_word(str,dir_filenames[i],count);  //comparing the entered string with with texts on different files
      total = count  + total;				 // total number of strings repeated on different files
    }

     printf("%s has repeated %d no. of times in total.\n",str,total);

    return 0;
}
