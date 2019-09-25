void mostrarMenuInicial() {

	printf("#######################################################################\n");
	printf("############################ MENU INICIAL #############################\n");
	printf("#######################################################################\n\n");
	printf("Por favor, seleccione una de las siguientes opciones:\n\n");
	printf("1) Edicion archivo Hosts.\n");
	printf("0) Salir\n\n");
	printf("Opcion seleccionada: ");

}

char solicitarRutaArchivo(char *rutaArchivo) {

	printf("\nPor favor, introduzca la ruta hacia el archivo:\n");
	printf("(Ej. ruta relativa \"..\\Carpeta\\archivo.txt\" )\n");
	printf("(Ej. ruta absoluta \"c:\\Carpeta\\archivo.txt\" )\n");
	printf("\nRuta: ");
	//Quizá aquí sería mejor usar fgets. Podriamos controlar la asignación de memoria y permitiria el uso de espacios en la dirección introducida.
	scanf("%s", rutaArchivo);

	return &rutaArchivo;
}

char solicitarRutaArchivoHostsSistema(char *rutaArchivo) {

	int rutaPorDefecto;
	
	printf("\nDesea utilizar la ruta por defecto para acceder al archivo Hosts del sistema?\n");
	printf("1) Utilizar ruta por defecto.\n");
	printf("2) Indicar ruta manualmente.\n");
	printf("Opcion seleccionada: ");
	//Quizá aquí sería mejor usar fgets. Podriamos controlar la asignación de memoria y permitiria el uso de espacios en la dirección introducida.
	scanf("%d", &rutaPorDefecto);

	while (rutaPorDefecto != 1 || rutaPorDefecto != 2) {

		printf("\nOPCION NO VALIDA.\n\n");
		printf("\nDesea utilizar la ruta por defecto para acceder al archivo Hosts del sistema?\n");
		printf("1) Utilizar ruta por defecto.\n");
		printf("2) Indicar ruta manualmente.\n");
		printf("Opcion seleccionada: ");
		scanf("%d", &rutaPorDefecto);

	}

	if (rutaPorDefecto == "S") {

		printf("\nIF RUTA POR DEFECTO\n");

	}
	else {

		printf("\nIF RUTA MANUAL\n");
	}


	return &rutaArchivo;
}

FILE *inicializarPunteroArchivo(char *rutaArchivo, char *modo)
{
	FILE *archivoProcesado;
	archivoProcesado = fopen(rutaArchivo, modo);

	if (archivoProcesado == NULL) {

		//Si ha fallado la apertura del archivo mostramos los detalles por pantalla.
		printf("\nERROR DETECTADO ABRIENDO: \"%s\"\nDETALLES: %s\n", rutaArchivo, strerror(errno));
		//Solicitamos de nuevo que introduzca una dirección hasta el archivo
		solicitarRutaArchivo(rutaArchivo);
		//Recursivamente lanzamos de nuevo la función hasta que el usuario introduzca una dirección válida.
		inicializarPunteroArchivo(rutaArchivo, modo);
	} 
	else {

		//Hemos tenido éxito. Devolvemos el puntero FILE con los detalles del stream incializado.
		return archivoProcesado;
	}
}

void editarArchivoHosts() {
	//Declaramos las variables que albergarán la dirección de los archivos a procesar.
	char rutaArchivoHostsSistema[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoHostsProporcionado[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoTemp[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los puntero tipo FILE para los archivos que procesaremos.
	FILE *archivoHostsSistema, *archivoHostsProporcionado, *archivoTemp;
	
	
	//Solicitamos al usuario que introduzca la ruta del archivo Hosts del Sistema.
	solicitarRutaArchivoHostsSistema(rutaArchivoHostsSistema);
	
	
	//Inicializamos y validamos el puntero FILE. 
	archivoHostsSistema = inicializarPunteroArchivo(&rutaArchivoHostsSistema, "rt");


	//Hemos llegado al EOF. Cerramos el archivo para liberar recursos
	fclose(archivoHostsSistema);

}

void mostrarContenidoArchivo(FILE *archivoA) {
	
	//Declaramos la variable para albergar el resultado de cada lectura del flujo. 
	char caracter;

	printf("\n#######################################################################\n");
	printf("######################### MOSTRANDO CONTENIDOS ########################\n");
	printf("#######################################################################\n\n");

	//Hasta que no alcanzemos el EOF del archivo imprimiremos por pantalla todo caracter que encontremos.
	while (!feof(archivoA)) {
			
		//Lectura caracter a caracter del flujo apuntado por "archivoA"
		caracter = fgetc(archivoA);
		//Imprimimos por pantalla cada caracter.
		printf("%c", caracter);
	}

	//Devolvemos el apuntador al principio del archivo.
	rewind(archivoA);
	
}

void guardarComoArchivo() {
	
	//Declaramos el contenedor para albergar el dirección de los archivo a procesar.
	char rutaArchivoOrigen[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoDestino[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los punteros de tipo FILE para los archivos que procesaremos.
	FILE *archivoOrigen, *archivoDestino;

	printf("\n#######################################################################\n");
	printf("####################### DETALLES ARCHIVO ORIGEN #######################\n");
	printf("#######################################################################\n");
	//Solicitamos al usuario que introduzca la ruta del archivo de origen.
	solicitarRutaArchivo(rutaArchivoOrigen);
	//Inicializamos y validamos el puntero FILE. 
	archivoOrigen = inicializarPunteroArchivo(&rutaArchivoOrigen, "rt");

	printf("\n#######################################################################\n");
	printf("####################### DETALLES ARCHIVO DESTINO ######################\n");
	printf("#######################################################################\n");
	//Solicitamos al usuario que introduzca la ruta del archivo de destino.
	solicitarRutaArchivo(rutaArchivoDestino);
	//Inicializamos y validamos el puntero FILE. 
	archivoDestino = inicializarPunteroArchivo(&rutaArchivoDestino, "wt");
		
	//Declaramos el contenedor para albergar el resultado de cada lectura. 
	char caracter;
	
	//Obtenemos ya el primer caracter para evitar problemas a la hora de copiar el último en el archivo de destino.
	caracter = fgetc(archivoOrigen);

	//Hasta que no alcanzemos el EOF del archivo de origen iremos copiando todo caracter que encontremos en el archivo de destino.
	while (!feof(archivoOrigen)) {
		
		//Escritura caracter a caracter en el flujo apuntado por "archivoDestino"
		fputc(caracter, archivoDestino);
		//Lectura caracter a caracter del flujo apuntado por "archivoOrigen"
		caracter = fgetc(archivoOrigen);
			
	}
	
	//Hemos llegado al EOF. Cerramos los archivos para liberar recursos.
	fclose(archivoOrigen);
	fclose(archivoDestino);

}

void buscarCadenaCaracteres() {
	//Declaramos el contenedor para albergar el dirección de los archivo a procesar.
	char rutaArchivo[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los punteros de tipo FILE para el archivo que procesaremos.
	FILE *archivoARevisar;
	//Declaramos las dos cadenas de caracteres que necesitaremos para la busqueda.
	char stringBuscado[MAX_CHAR_CADENA];
	char stringLeido[MAX_CHAR_CADENA];

	printf("\n#######################################################################\n");
	printf("####################### DETALLES ARCHIVO ORIGEN #######################\n");
	printf("#######################################################################\n");
	//Solicitamos al usuario que introduzca la ruta del archivo de origen.
	solicitarRutaArchivo(rutaArchivo);
	//Inicializamos y validamos el puntero FILE. 
	archivoARevisar = inicializarPunteroArchivo(&rutaArchivo, "rt");

	//Declaramos e inicializamos las dos variables que nos permitirán llevar la cuenta de cantidad de strings coincidentes y iteración. 
	int n=1, m=0;

	do {

		printf("\n#######################################################################\n");
		printf("################## CADENA DE CARACTERES A BUSCAR ######################\n");
		printf("#######################################################################\n");
		printf("\n(Introduzca \"SALIR\" para volver al menu princial)\nBuscar en archivo: ");
		scanf("%s", stringBuscado);
		//Forzamos salir de la función buscar cadena en archivo y volver al menu principal si el usuario introduce "SALIR"
		if (!strcmp(stringBuscado, "SALIR")) {
			break;
		}
		
		//Hasta que no alcanzemos el EOF del archivo de origen iremos obteniendo toda cadena que tenga.
		while (!feof(archivoARevisar)) {
			
			//Con fscanf() recorremos el flujo del archivoARevisar extrayendo toda cadena delimitada por espacios asignando secuencialmente esas cadenas a stringLeido.
			fscanf(archivoARevisar, "%s.", stringLeido);
			//Facilitamos una salida por pantalla más informativa. 
			printf("\nCADENA NUM %d. STRING LEIDO ---> %s", n, stringLeido);
			n++;
			//Vamos comparando los ene strings obtenidos del archivo analizado con el string buscado por el usuario.
			if (!strcmp(stringBuscado, stringLeido)) {

				printf(" <-------- COINCIDE!!!");
				//Aumentamos el contador de coincidencias dadas.
				m++;
			}

		}
		//Informamos por pantalla en función de las coincidencias encontradas.
		if (m == 0) {

			printf("\n\nLa cadena \"%s\" NO esta presente en el fichero\n", stringBuscado);

		}
		else {

			printf("\n\nLa cadena \"%s\" SI esta presente en %d ocasion/es\n", stringBuscado, m);

		}
		//Reiniciamos los contadores por si hay que buscar más cadenas en el mismo archivo. 
		n = 0;
		m = 0;
		//Volvemos al punto inicial del archivo por si hay que buscar más cadenas en el mismo archivo. 
		rewind(archivoARevisar);

	} while (strcmp(stringBuscado, "SALIR"));
	
	//Hemos llegado al EOF. Cerramos los archivos para liberar recursos.
	fclose(archivoARevisar);

}