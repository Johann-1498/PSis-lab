#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
   pid_t pid1, pid2, pid3;


   // Crear el primer hijo
   pid1 = fork();
   if (pid1 < 0) {
       std::cerr << "Error al crear el primer hijo" << std::endl;
       return 1;
   }
   if (pid1 == 0) {
       // Código del primer hijo
       std::cout << "Soy el primer hijo, mi PID es " << getpid() << std::endl;
       return 0; // Termina el primer hijo
   } else {
       // Crear el segundo hijo
       pid2 = fork();
       if (pid2 < 0) {
           std::cerr << "Error al crear el segundo hijo" << std::endl;
           return 1;
       }
       if (pid2 == 0) {
           // Código del segundo hijo
           std::cout << "Soy el segundo hijo, mi PID es " << getpid() << std::endl;
           return 0; // Termina el segundo hijo
       } else {
           // Crear el tercer hijo
           pid3 = fork();
           if (pid3 < 0) {
               std::cerr << "Error al crear el tercer hijo" << std::endl;
               return 1;
           }
           if (pid3 == 0) {
               // Código del tercer hijo
               std::cout << "Soy el tercer hijo, mi PID es " << getpid() << std::endl;
               return 0; // Termina el tercer hijo
           } else {
               // Código del padre
               std::cout << "Soy el padre, mi PID es " << getpid() << std::endl;


               // Esperar a que todos los hijos terminen
               wait(NULL); // Esperar al primer hijo
               wait(NULL); // Esperar al segundo hijo
               wait(NULL); // Esperar al tercer hijo
           }
       }
   }


   return 0;
}
