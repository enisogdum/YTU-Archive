#include <stdio.h>
#include <stddef.h> 
#define EOF_FLAG 1;
#define ERR_FLAG 2;


FILE *open_file(char* file_name, char* mode){
  FILE *fp;
  fp = fopen(file_name, mode);
  if (fp == NULL)	//eg. you try to open a file for reading that does not exist
  {
    /* fprintf() takes an extra argument indicating which stream 
	the output should be sent to. The message is send to the standard I/O stream stderr.
	By default, this stream usually points to your terminal.
	*/
	fprintf( stderr, "Error opening file\n");
	//fprintf( stdout, "Error opening file\n");
    exit (0);
  }
  return fp;
}

// If neither flag is set, stat will equal zero.
// If error is set, but not eof, stat equals 1
// If eof is set, but not error, stat equals 2
// If both flags are set, stat equals 3
char check_file(FILE* fp)
{
  char stat=0;
  if (ferror(fp))	//if you try to read a file which is opened in writing mode
  	stat|=ERR_FLAG;	//stat=2  010
  if (feof(fp))		//end of file
  	stat|=EOF_FLAG;	//stat=3  011 if both ERR_FLAG EOF_FLAG is on
  clearerr(fp);
  return stat;
}

int main(){
  char file_name[100], mode[2], stat; 
  FILE *fp; 
  printf("enter name of the file to be opened\n"); 
  scanf("%s", file_name);
  printf("enter name of the access mode\n"); 
  scanf("%s", mode);
  fp=open_file(file_name, mode);
  /*
  .
  some reading and/or writing operations are performed
  .
  */
  stat=check_file(fp);
  if (stat==0)
  	printf("everything is fine\n"); 
  else
  	printf("%d",stat); 
  fclose(fp);
  return 0; 
}
