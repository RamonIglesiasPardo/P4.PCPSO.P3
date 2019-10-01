void editarArchivoHosts() {
	//Declaramos las variables que albergarán la dirección de los archivos a procesar.
	char rutaArchivoHostsSistema[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoHostsProporcionado[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoTemp[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los puntero tipo FILE para los archivos que procesaremos.
	FILE *archivoHostsSistema, *archivoHostsProporcionado, *archivoTemp;
		
	//Solicitamos al usuario que introduzca la ruta del archivo Hosts del Sistema, inicializamos el puntero tipo FILE y mostramos contenidos..
	strcpy(rutaArchivoHostsSistema, RUTA_POR_DEFECTO_HOST_SISTEMA);
	//solicitarRutaArchivoHostsSistema(rutaArchivoHostsSistema);
	archivoHostsSistema = inicializarPunteroArchivo(rutaArchivoHostsSistema, "r+");
	mostrarContenidoArchivo(archivoHostsSistema);

	//Solicitamos al usuario que introduzca la ruta del archivo Hosts e inicializamos el puntero FILE.
	strcpy(rutaArchivoHostsProporcionado, "../PCPSO.P3/hostsProporcionado.txt");
	//solicitarRutaArchivo(rutaArchivoHostsProporcionado);
	archivoHostsProporcionado = inicializarPunteroArchivo(rutaArchivoHostsProporcionado, "rt");

	//Creamos el archivo temporal e incializamos el puntero FILE.
	printf("\nCREANDO ARCHIVO TEMPORAL\n");
	strcpy(rutaArchivoTemp, RUTA_POR_DEFECTO_HOST_TEMPORAL);
	archivoTemp = inicializarPunteroArchivo(rutaArchivoTemp, "w");

	//Declaración de las estructuras que contendran los pares IP-URL. Permitirimos hasta 50 pares por struct.
	struct parIpUrl paresIpUrlHostsPropuesto[50] = { NULL };
	struct parIpUrl paresIpUrlHostsSistema[50] = { NULL };
	
	//Empezamos a procesar los pares del Hosts propuesto y despues del Hosts del SO
	printf("\n\nANALIZANDO PARES IP-URL PROPUESTOS EN EL ARCHIVO HOST INTRODUCIDO: \"%s\"\n", rutaArchivoHostsProporcionado);
	obtenerParesIpUrl(archivoHostsProporcionado, paresIpUrlHostsPropuesto);
	printf("\n\nANALIZANDO PARES IP-URL EXISTENTES EN EL ARCHIVO HOST DEL SO: \"%s\"\n", rutaArchivoHostsSistema);
	obtenerParesIpUrl(archivoHostsSistema, paresIpUrlHostsSistema);

	parNuevoCopiarEnArchivoTmp(paresIpUrlHostsPropuesto, paresIpUrlHostsSistema, archivoTemp);

	fclose(archivoTemp);



	/*int i=0;
	while (i <= paresIpUrlHostsPropuesto[i].numParesEncontrados) {

		printf("\n\nIP: %s\n", paresIpUrlHostsPropuesto[i].ip);
		printf("URL: %s\n", paresIpUrlHostsPropuesto[i].url);

		i++;

	}*/



	getch();


	


	//Hemos llegado al EOF. Cerramos el archivo para liberar recursos

	fclose(archivoHostsSistema);


}