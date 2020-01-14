


#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define limite 1000









int main(){
	

	double cadena[limite];
	double *longitud;
	FILE* documento;
	int i=0;
	documento=fopen("ArchivoA.tex", "rt");
	fscanf(documento, "%lf", longitud);

	while(&longitud!= EOF && i < limite){
		cadena[i] = &&longitud;
		printf("%f", cadena[i]);
		i++;
		fscanf(documento, "%lf", longitud);


	}

	fclose(documento);

	for(int i=0; i<&longitud;i++)
	{
		printf("%f\n",cadena[i]);
	}

	return 0;
}