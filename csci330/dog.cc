/*
   Gerald Ellsworth
   z1885378
   CS 330-1
   Assignment 5
   Due Date: 2/12/2021
*/

#include <iostream>
#include "dog.h"

int main(int argc, char *argv[])
{
   char *buffer = new char [1];                                               // The buffer string that files are read/written into.
   int fd;                                                     // Variable for the file descriptor
   ssize_t nr;                                                 // Variable for the bytes read
//   ssize_t nw;                                                 // Variable for the bytes written
   ssize_t count = 500;                                              // Variable for the number of available bytes
   int i = 1;
   int k;
   char optstring[] = "c";
   int opt = 0;
   bool c = false;


   while((opt = getopt(argc, argv, optstring)) != -1)		// Parse through the arguments provided on the command line
      {
         switch(opt)
         {
//            case 's':
//		break;
  //          case 'n':
//		break;
         case 'c':
            c = true;
      		break;
  //          case 'r':
//		break;
  //          case 'x':
//		break;
  //          case 'b':
//		break;
            default:
		perror("no arguments provided.");

           }
	   }
      char *fn = argv[optind];

   if (argc > 1)                                            // Checks if there are more than 1 file to read.
   {
         if (strcmp(argv[i], "-") == 0)                        // If the argument in location i is a - then we go into our loop.
         {
            while (i < argc)                                   // Looping through the files on the command line.
            {
               fd = i;
               nr = read(fd, buffer, count);                   // Reads the file, in this case a standard input.
               if (nr == -1)
               {
                  perror ("- found");
                  return 3;
               }
               buffer[nr] = 0;
               write(1, buffer, nr);                      // We write back what was input.
            }
         }   
      
         else                                                  // Else if an actual file is input, we attempt to open it.
         {
            for (int i = 1; i < argc; i++)                     // We loop through all the files that are requested to be opened.
            {
               fd = open(argv[i], O_RDWR);                     
               if (fd == -1)                                   // If there is any error in the file, we output an error message.
               {
                  perror("Error opening file");               
                  return 2;
               }
               do
               {
                  nr = read(fd, buffer, count);                   
                  if (nr == -1)
                  {
                     perror ("Error reading file");
                     return 3;
                  }
                     buffer[nr] = 0;
                     write(1, buffer, nr);                // We attempt to write back anything that was read.
               }
               while (nr == count);
            }
            close(fd);                                         // We close any files that have been opened.
         }
   }
   else                                                        // If there are no arguments, we print an error message.
   {
      cerr << "You didn't tell me what to do!" << endl;
      return 1;
   }

   if (c == true)
      std::cout << "c found.";
}
