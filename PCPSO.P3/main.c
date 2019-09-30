#include <stdio.h>//Necesaria para varias funciones que utilizaremos como scanf, fscanf, printf... y definiciones de tipo como FILE...
#include <errno.h>//Necesaria para contar con la definici�n de "errno" (tambi�n se puede utilizar stdlib.h)
#include <string.h>//Necesaria para contar con la funci�n strcmp()
#include <stdbool.h>//Necesaria para contar con booleanos.
#include "predeclaracionFunciones.h"//Predeclaraci�n de las funciones y acciones creadas para el programa 
#include "editarArchivoHosts.c"//Funcionalidad principal del programa
#include "infoMostradaUsuario.c"//Mensajes mostrados al usuario
#include "tratamientoDatos.c"//Propiamente las funciones creadas para manipular los datos de la aplicaci�n

int main()
{
	int opcionSeleccionada;
	const int VALOR_SALIDA = 0;

	//Con este bucle "do while" volveremos al menu inicial hasta que no sea introducido el caracter de fuga. 
	do {
		//Mostramos las opciones del programa y solicitamos introduzca una opci�n al usuario.
		infoUsrMenuInicial();
		opcionSeleccionada = 1;
		//scanf("%d", &opcionSeleccionada);

		switch (opcionSeleccionada)
		{
		case 0:
			//Introducido caracter de fuga. Se cierra la aplicaci�n.
			break;
		case 1:
			printf("\nEjecutando opcion \"Edicion archivo Hosts.\"\n");
			editarArchivoHosts();
			break;
		default:
			printf("\nOPCION NO VALIDA.\nSELECCIONE UNA OPCION DENTRO DEL RANGO OFRECIDO.");
			break;
		}

		infoUsrFinalPrograma();

		getch(); // PAUSA
		system("cls"); //Limpiamos la pantalla (aunque para mejorar la portabilidad ser�a deseable no usarlo)

	} while (opcionSeleccionada != VALOR_SALIDA);

	return 0;
}