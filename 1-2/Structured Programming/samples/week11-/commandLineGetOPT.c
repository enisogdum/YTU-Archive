//https://www.gnu.org/software/libc/manual/html_node/Getopt.html#Getopt
//The getopt() is a builtin function that is used to parse command line arguments.
//int getopt(int argc, char *const argv[], const char *options) 
//At each call, it returns 
//		a single character representing the next option letter that it finds, 
//		or ' ? ' if it finds an invalid option.
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char *optarg;	// arguman alan bir opsiyon karakteri varsa ilgili argumaný tutar
extern int optopt;	//hatalý opsiyon karakterini tutar
int main (int argc, char **argv)
{
  int aflag = 0;	//a opsiyonu set edildiyse
  int bflag = 0;	//a opsiyonu set edildiyse
  char *cvalue = NULL; //opsiyon argumani
  int index;
  int c;

  while ((c = getopt (argc, argv, "abc:")) != -1)
  // If such an option is followed by a colon (:), the option requires an argument
    switch (c)
      {
      case 'a':
        aflag = 1;
        break;
      case 'b':
        bflag = 1;
        break;
      case 'c':
        cvalue = optarg; //optarg is set by getopt to point at the value of the option argument, for those options that accept arguments.
        break;
    // By default, getopt() prints an error message on standard error, places the erroneous option character in optopt, and returns '?' as the function result.
    // You can use optopt for providing your own diagnostic messages.
    /*
	  case '?': 
        if (optopt == 'c') 
          printf ("Option -%c requires an argument.\n", optopt);
        else if (isprint (optopt)) 
          printf ("Unknown option `-%c'.\n", optopt);
        return 1;
    */
      default:
        exit(0);
      }

  printf ("aflag = %d, bflag = %d, cvalue = %s\n", aflag, bflag, cvalue);
  //optind shows the index of next element to be processed in argv array.
  for (index = optind; index < argc; index++)
    printf ("Non-option argument %s\n", argv[index]);
  return 0;
}
/*
./commandLineGetOPT
./commandLineGetOPT -a -b
./commandLineGetOPT -b -a
./commandLineGetOPT -c
./commandLineGetOPT -c foo
./commandLineGetOPT -cfoo
./commandLineGetOPT 8
./commandLineGetOPT -a -b -c 8 -d -f
./commandLineGetOPT -c foo -a -b
./commandLineGetOPT -c foo -a -b 8
*/
