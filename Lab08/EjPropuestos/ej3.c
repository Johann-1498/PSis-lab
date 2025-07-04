//codigo10.c
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>


using namespace std;


int main() {
   int i;
   int fd1, fd2;
   const char string1[10] = "*********";
   const char string2[10] = "---------";
   pid_t rf;


   fd1 = creat("ficheroA", 0666);
   fd2 = creat("ficheroB", 0666);
   rf = fork();


   switch (rf) {
   case -1:
       printf("\nNo he podido crear el proceso hijo");
       break;
   case 0:
       // Proceso hijo
       for (i = 0; i < 10; i++) {
           write(fd1, string2, sizeof(string2));
           write(fd2, string2, sizeof(string2));
           sleep(1); // Esperar 1 segundo
       }
       break;
   default:
       // Proceso padre
       for (i = 0; i < 10; i++) {
           write(fd1, string1, sizeof(string1));
           write(fd2, string1, sizeof(string1));
           usleep(500000); // Esperar 0.5 segundos (500000 microsegundos)
       }
   }


   printf("\nFinal de ejecucion de %d \n", getpid());
   exit(0);
}
