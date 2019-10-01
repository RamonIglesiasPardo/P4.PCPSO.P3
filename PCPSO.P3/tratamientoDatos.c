char solicitarRutaArchivo(char *rutaArchivo) {

	infoUsrSolicitarRutaManual();
	//Quizá aquí sería mejor usar fgets. Podriamos controlar la asignación de memoria y filtrar mejor la entrada del usuario.
	scanf(" %s", rutaArchivo);

	return rutaArchivo;

}
//Mediante un menu da la posibilidad de utilizar una ruta por defecto para alcanzar el archvio Hosts del SO.
char solicitarRutaArchivoHostsSistema(char *rutaArchivo) {

	int opcionSeleccionada;	
	infoUsrUsarRutaDefault();

	//Quizá aquí sería mejor usar fgets. Podriamos controlar la asignación de memoria y permitiria el uso de espacios en la dirección introducida.
	scanf(" %d", &opcionSeleccionada);

	while (opcionSeleccionada != 1 && opcionSeleccionada != 2) {

		printf("\nOPCION NO VALIDA.\n\n");
		infoUsrUsarRutaDefault();
		scanf(" %d", &opcionSeleccionada);

	}

	if (opcionSeleccionada == 1) {

		strcpy(rutaArchivo, RUTA_POR_DEFECTO_HOST_SISTEMA);

	} 
	else {

		solicitarRutaArchivo(rutaArchivo);
	}
	
	return rutaArchivo;
}

/*Al pasarle una ruta hacia el archivo y el modo de apertura devolvera un puntero tipo FILE
para manipular el stream de datos. Si se da algún error de con la ruta proporcionada para 
la apertura del archivo devuelve el fallo por pantalla y solicita una nueva ruta
*/
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
		printf("\nEXITO ABRIENDO: \"%s\"\n", rutaArchivo);
		return archivoProcesado;
	}
}

/*Devueleve true si el primer caracter de la línea pasada es igual a uno de los simbolos utilizados para 
comentar lineas */
bool esLineaComentario(char *linea) {
	
	return linea[0] == '#' || linea[0] == '/' || linea[0] == '@' || linea[0] == ' ' || linea[0] == '\n';
}

//Devuelve true si ha podido obtener los dos primeros strings de la línea procesada. 
bool obtenerStringsIpUrl(char *stringIP, char *stringURL, char *contenidoLinea) {

	//Utilizaremos strtok() para separar el string recogiendo los elementos que estan delimitados por espacios.
	char *contenidoDelimitadoPorEspacios = strtok(contenidoLinea, " ");
	char *stringsObtenidos[2] = {NULL};
	int posicionString = 0;
	
	//Procesaremos los strings si este no es nulo y ademas nos limitaremos a las dos primeras cadenas.
	while (contenidoDelimitadoPorEspacios != NULL && posicionString < 2) {

		stringsObtenidos[posicionString] = contenidoDelimitadoPorEspacios;
		contenidoDelimitadoPorEspacios = strtok(NULL, " ");
		posicionString++;
	}

	//Si no se ha podido obtener una cadena devolvemos false y finalizamos la aplicación.
	if (stringsObtenidos[0] == NULL || stringsObtenidos[1] == NULL) {

		return false;

	}

	//Si el segundo string (con la URL) tiene saltos de línea los retiramos del string.
	if (strstr(stringsObtenidos[1], "\n")) {

		stringsObtenidos[1] = strtok(stringsObtenidos[1], "\n");

	}

	//El proceso ha sido correcto, copiamos los strings obtenidos en los respectivos punteros.
	strcpy(stringIP, stringsObtenidos[0]);
	strcpy(stringURL, stringsObtenidos[1]);
		
	return true;

}

//Al pasarle un puntero tipo FILE devolvera su contenido por pantalla.
void mostrarContenidoArchivo(FILE *archivoA) {
	
	//Declaramos la variable para albergar el resultado de cada lectura del flujo. 
	char caracter;

	infoUsrInicioMostrarContenidos();

	//Hasta que no alcanzemos el EOF del archivo imprimiremos por pantalla todo caracter que encontremos.
	while (!feof(archivoA)) {
			
		//Lectura caracter a caracter del flujo apuntado por "archivoA"
		caracter = fgetc(archivoA);
		//Imprimimos por pantalla cada caracter.
		printf("%c", caracter);
	}

	infoUsrFinMostrarContenidos();

	//Devolvemos el apuntador al principio del archivo.
	rewind(archivoA);
	
}

//Al pasarle un archivo tipo FILE obtendrá los pares IP-URL y los almacenada en la structura que se le proporcione.
void obtenerParesIpUrl(FILE *archivoHostsProporcionado, struct parIpUrl *punteroParesIpURL) {
	
	int  numLinea = 1, numParesObtenidos = 0;
//Hasta que no alcanzemos el EOF del archivo de origen iremos tratando línea a línea.
	while (!feof(archivoHostsProporcionado)) {

		//El contenedor de la línea tratada y máximo de caracteres que permitiremos
		char bufferLinea[MAX_CHAR_CADENA] = {' '};

		//Obtenemos el contenido de la línea
		fgets(bufferLinea, 150, archivoHostsProporcionado);
		/*Facilitamos la salida para usuario mostrando qué está haciendo la aplicación. (también evitamos que si el primer caracter es un
		salto de línea lo imprima por pantal[descuadrando la salida...])*/ 
		printf("\nLINEA NUM %02d. CARACTER DETECTADO POSICION 1: %c.", numLinea, bufferLinea[0] == '\n'? ' ': bufferLinea[0]);

		//Solo trataremos la línea si esta no es un comentario.
		if (!esLineaComentario(bufferLinea)) {

			//Contenedores para los pares IP y URL			
			char stringIP[TAM_IP], stringURL[TAM_URL];
					
			/*Devuelve true si ha podido obtener los dos primeros strings de la línea. Ademas los asigna a los punteros correspondientes*/
			if (!obtenerStringsIpUrl(stringIP, stringURL, bufferLinea)) {

				infoUsrErrorObtenerStrings(numLinea);
				break;

			}
			
			//Todo ha ido bien obteniendo los strings. Los vamos introduciendo en la estructura.
			strcpy(punteroParesIpURL->ip, stringIP);
			strcpy(punteroParesIpURL->url, stringURL);

			//
			punteroParesIpURL->numParesEncontrados = numParesObtenidos;
			//Saltamos a la siguiente dirección en memoria del puntero para dirigirlo al siguiente grupo de la estructura.
			punteroParesIpURL++;

			printf("\n\nIP DETECTADA == %s\n", stringIP);
			printf("URL DETECTADA == %s\n", stringURL);
			numParesObtenidos++;
		}
		else {
			printf("ESTA LINEA ES UN COMENTARIO: NO SE PROCESA");
		}
		numLinea++;
	}
}

//Con esta función chequeamos si los pares propuestos ya existen en el Hosts del SO. Si son nuevos los escribimos en el archivo temporal
void parNuevoCopiarEnArchivoTmp(struct parIpUrl *paresIpUrlHostsPropuesto, struct parIpUrl *paresIpUrlHostsSistema) {
	
	printf("\n\nINICIANDO COPIA DE PARES NUEVOS HACIA ARCHIVO TEMPORAL\n");

	//Declaramos la variable que albergará la dirección del archivo temporal.
	char rutaArchivoTemp[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos el puntero tipo FILE para el archivo que procesaremos.
	FILE *archivoTemp;

	//Creamos el archivo temporal e incializamos su puntero FILE.
	printf("\nCREANDO ARCHIVO TEMPORAL\n");
	strcpy(rutaArchivoTemp, RUTA_POR_DEFECTO_HOST_TEMPORAL);
	archivoTemp = inicializarPunteroArchivo(rutaArchivoTemp, "w");
	
	struct parIpUrl *hostsSistemaBuffer;
	memcpy(&hostsSistemaBuffer, &paresIpUrlHostsSistema, sizeof paresIpUrlHostsSistema);

	for (int i = 0; i <= paresIpUrlHostsPropuesto->numParesEncontrados; i++) {
		
		bool hayCoincidencia = false;
		
		for (int j = 0; j <= paresIpUrlHostsSistema->numParesEncontrados; j++) {
			
			if (!strcmp(paresIpUrlHostsPropuesto->ip, paresIpUrlHostsSistema->ip) && !strcmp(paresIpUrlHostsPropuesto->url, paresIpUrlHostsSistema->url)) {
				
				hayCoincidencia = true;
				break;
				
			}
			paresIpUrlHostsSistema++;
		}

		if (!hayCoincidencia) {

			fputs("\n", archivoTemp);
			fputs(paresIpUrlHostsPropuesto->ip, archivoTemp);
			fputs(" ", archivoTemp);
			fputs(paresIpUrlHostsPropuesto->url, archivoTemp);


			bool hayCoincidencia = false;

		}

		paresIpUrlHostsPropuesto++;
		memcpy(&paresIpUrlHostsSistema, &hostsSistemaBuffer, sizeof hostsSistemaBuffer);
	}
	int estado = fclose(archivoTemp);

	if (estado == 0)
		printf("\nEXITO CERRANDO \"%s\"\n", rutaArchivoTemp);
	else
	{
		printf("FALLO CERRANDO ARCHIVO TEMPORAL\n");
		perror("ERROR: ");
	}
	

}

//Copiamos los datos del archivo temporal al Hosts del SO y eliminamo archivo.
void anadirDatosHostsSO(FILE *archivoHostsSistema) {

	printf("\nINICIANDO VOLCADO DEL ARCHIVO TEMPORAL AL HOSTS DEL SO\n");

	//Declaramos la variable que albergará la dirección del archivo temporal.
	char rutaArchivoTemp[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos el puntero tipo FILE para el archivo que procesaremos.
	FILE *archivoTemp;

	//Creamos el archivo temporal e incializamos su puntero FILE.
	printf("\nCREANDO ARCHIVO TEMPORAL\n");
	strcpy(rutaArchivoTemp, RUTA_POR_DEFECTO_HOST_TEMPORAL);
	archivoTemp = inicializarPunteroArchivo(rutaArchivoTemp, "r+");

	//Declaramos el contenedor para albergar el resultado de cada lectura. 
	char caracter;
	rewind(archivoTemp);

	//Obtenemos ya el primer caracter para evitar problemas a la hora de copiar el último en el archivo de destino.
	caracter = fgetc(archivoTemp);

	//Hasta que no alcanzemos el EOF del archivo de origen iremos copiando todo caracter que encontremos en el archivo de destino.
	while (!feof(archivoTemp)) {

		//Escritura caracter a caracter en el flujo apuntado por "archivoDestino"
		fputc(caracter, archivoHostsSistema);
		//Lectura caracter a caracter del flujo apuntado por "archivoOrigen"
		caracter = fgetc(archivoTemp);

	}
	fclose(archivoTemp);

	int estado = remove(rutaArchivoTemp);

	if (estado == 0)
		printf("\nEXITO ELIMINANDO \"%s\"\n", rutaArchivoTemp);
	else
	{
		printf("FALLO ELIMINANDO ARCHIVO TEMPORAL\n");
		perror("ERROR: ");
	}
	rewind(archivoHostsSistema);
}
