#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int ac, char **av, char **ep)
{
	int tmp = dup(1);//hago copia del fd de stdout
	int fd = open("outfile", O_WRONLY);
	int pp1[2];//FDs del primer pipe
	int	pid;
	//char *op[2] = {"ls", NULL};

	dup2(fd, 1);//copia del fichero abierto al fd de stdout
	close(fd);//cerrar fd antiguo del fichero

	if (pipe(pp) == -1)//creemos un pipe!
	{
		printf("Error al abrir los pipes\n");
		exit(-1);
	}

	pid = fork();//creemos un proceso
	if (pid == 0)
	{
		close(pp[0]);//para que queremos leer? cerremos lectura!
		write(pp[1], "Soy el hijo\n", 12);//vamos a escribir en el pipe
		close(pp[1]);//ya hemos escrito, cerremos el fd de escritura de este pp
		execve("/bin/ls", &av[1], ep);//ejecutamos un comando
		printf("Error: execve failed\n");//si llega aqui es error
		exit(-1);
	} else
	{
		pid = fork();//creemos segundo proceso
		if (pid == 0)
		{
			

		}
	}
	dup2(tmp, 1);//no queremos que imprima en pantalla, duplicamos 'tmp' para que
				 //su fd ahora sea 1, la salida estandar. La salida se escribira
				 //en 'tmp'
	printf("final\n");
	char buf[90];
	close(pp[1]);//no vamos a escribir, cerramos fd
	read(pp[0], buf, 80);//leer pipe y meterlo en el buf
	close(pp[0]);//cerrar lectura
	printf("%s", buf);//imprimir buf
}
// 1. 	Crear dos procesos child(c) que vayan a ejecutar ambos comandos
// 2. 	Crear pipe que comunice c1 y c2, cerrando respectivos fd del pipe que no
//		necesiten los child y otro pipe que comunique c2 y padre
// 3. 	Parser para obtener el PATH del comando
// 4. 	Crear otro proceso para obtener la ruta del comando?
