void editarArchivoHosts() {
	//Declaramos las variables que albergarán la dirección de los archivos a procesar.
	char rutaArchivoHostsSistema[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoHostsProporcionado[MAX_CHAR_RUTA_ARCHIVO], rutaArchivoTemp[MAX_CHAR_RUTA_ARCHIVO];
	//Declaramos los puntero tipo FILE para los archivos que procesaremos.
	FILE *archivoHostsSistema, *archivoHostsProporcionado, *archivoTemp;
		
	//Solicitamos al usuario que introduzca la ruta del archivo Hosts del Sistema.
	solicitarRutaArchivoHostsSistema(rutaArchivoHostsSistema);
	//Abrimos el acceso al archivo Hosts del SO y mostramos su contenido.
	archivoHostsSistema = inicializarPunteroArchivo(rutaArchivoHostsSistema, "r+");
	mostrarContenidoArchivo(archivoHostsSistema);

	//Solicitamos al usuario que introduzca la ruta del archivo Hosts del Sistema.
	//solicitarRutaArchivo(rutaArchivoHostsProporcionado);
	strcpy(rutaArchivoHostsProporcionado, "../PCPSO.P3/hostsProporcionado.txt");
	//Abrimos el acceso al archivo Host proporcionado.
	archivoHostsProporcionado = inicializarPunteroArchivo(rutaArchivoHostsProporcionado, "rt");

	//Checkear si los pares proporcionados estan presentes en el hosts del SO. Si no lo estan escribirlos en un archivo temporal. 
	printf("\nCREANDO ARCHIVO TEMPORAL\n");
	strcpy(rutaArchivoTemp, RUTA_POR_DEFECTO_HOST_TEMPORAL);
	archivoTemp = inicializarPunteroArchivo(rutaArchivoTemp, "w");

	char bufferLinea[150];
	char a1[100], a2[100], a3[100], a4[100];
	char parBuscado[100] = "nodebeSalir";
	int  n=1, ip[4]={0}, a,b,c,d;
	
	
	//Hasta que no alcanzemos el EOF del archivo de origen iremos obteniendo cada línea.
	while (!feof(archivoHostsProporcionado)) {
		
		fgets(bufferLinea, 150, archivoHostsProporcionado);
		
		
		printf("\nLINEA NUM %d", n);
		printf("\nCHAR EN POSICION 1: %c", bufferLinea[0]);
		
		//strstr(bufferMaxLongitudLinea, "#") == NULL;
	
		//strstr(bufferLinea[0], "#") == NULL

		if (bufferLinea[0] != '#')  {


			printf("\n CONTENIDO TOTAL LINEA ----> %s\n", bufferLinea); //printing each token







			char *contenidoDelimitadoPorPuntos = strtok(bufferLinea, ".");
			int m = 1;
			while (contenidoDelimitadoPorPuntos != NULL) {
			
				printf("-------------------> ELEMENTO %d == %s\n", m, contenidoDelimitadoPorPuntos); //printing each token
				contenidoDelimitadoPorPuntos = strtok(NULL, ".");
				m++;
			}



				


			//char* loquesale, *delim = "%s.%s.%s.%s";
			//loquesale = strtok(bufferMaxLongitudLinea, delim);
			////fscanf(archivoHostsProporcionado, "%s %s", a1, a2);
			//printf("\nCADENA NUM %d. STRING LEIDO ---> %s", n, loquesale);
			////fgets(bufferMaxLongitudLinea, 150, archivoHostsProporcionado);
		}
		n++;

		//fscanf(archivoHostsProporcionado, "%d %d %d %d", &ip[0], &ip[1], &ip[2], &ip[3]);
		//printf("\nCADENA NUM %d. STRING LEIDO ---> %d %d %d %d", n, ip[0], ip[1], ip[2], ip[3]);
		

		//fscanf(archivoHostsProporcionado, "%s %s %s %s", a1, a2, a3, a4);
		//printf("\nCADENA NUM %d. STRING LEIDO ---> %s %s %s %s", n, a1, a2, a3, a4);
		



	



		//fscanf(archivoHostsProporcionado, "%d.%d.%d.%d", &a, &b, &c, &d);
		//Facilitamos una salida por pantalla más informativa. 
		//printf("\nIP %d.%d.%d.%d --->", a, b, c, d);

		
		//Vamos comparando los ene strings obtenidos del archivo analizado con el string buscado por el usuario.
		//if (!strcmp(parBuscado, a1)) {

			//printf(" <-------- COINCIDE!!!");
			
			
		//}

	}


	getch();

	//Inicializamos y validamos el puntero FILE. 
	


	//Hemos llegado al EOF. Cerramos el archivo para liberar recursos
	fclose(archivoHostsSistema);

}