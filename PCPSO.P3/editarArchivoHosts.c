void editarArchivoHosts() {
	//Declaramos las variables que albergarán la dirección de los archivos a procesar.
	char rutaArchivoHostsSistema[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoHostsProporcionado[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los puntero tipo FILE para los archivos que procesaremos.
	FILE *archivoHostsSistema, *archivoHostsProporcionado;
		
	//Solicitamos al usuario que introduzca la ruta del archivo Hosts del Sistema, inicializamos el puntero tipo FILE y mostramos contenidos..
	solicitarRutaArchivoHostsSistema(rutaArchivoHostsSistema);
	archivoHostsSistema = inicializarPunteroArchivo(rutaArchivoHostsSistema, "r+");
	mostrarContenidoArchivo(archivoHostsSistema);

	//Solicitamos al usuario que introduzca la ruta del archivo Hosts e inicializamos el puntero FILE.
	solicitarRutaArchivo(rutaArchivoHostsProporcionado);
	archivoHostsProporcionado = inicializarPunteroArchivo(rutaArchivoHostsProporcionado, "rt");

	//Declaración e inicializamos las estructuras que contendran los pares IP-URL. Permitirimos hasta 50 pares por struct.
	struct parIpUrl paresIpUrlHostsPropuesto[50] = { NULL};
	struct parIpUrl paresIpUrlHostsSistema[50] = { NULL };
	
	//Empezamos a procesar los pares del Hosts propuesto y despues del Hosts del SO
	printf("\n\nANALIZANDO PARES IP-URL PROPUESTOS EN EL ARCHIVO HOST INTRODUCIDO: \"%s\"\n", rutaArchivoHostsProporcionado);
	obtenerParesIpUrl(archivoHostsProporcionado, paresIpUrlHostsPropuesto);
	printf("\n\nANALIZANDO PARES IP-URL EXISTENTES EN EL ARCHIVO HOST DEL SO: \"%s\"\n", rutaArchivoHostsSistema);
	obtenerParesIpUrl(archivoHostsSistema, paresIpUrlHostsSistema);

	//Con esta función chequeamos si los pares propuestos ya existen en el Hosts del SO. Si son nuevos los escribimos en el archivo temporal.
	parNuevoCopiarEnArchivoTmp(paresIpUrlHostsPropuesto, paresIpUrlHostsSistema);
	
	//Copiamos los datos del archivo temporal al Hosts del SO y eliminamo archivo.
	anadirDatosHostsSO(archivoHostsSistema);

	//Mostramos contenidos del archivo Hosts resultante del SO.
	mostrarContenidoArchivo(archivoHostsSistema);

	//Cerramos los archivos para liberar recursos.
	fclose(archivoHostsSistema);
	fclose(archivoHostsProporcionado);

	printf("Fin del programa...");

}