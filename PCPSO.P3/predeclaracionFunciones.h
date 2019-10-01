#define MAX_CHAR_RUTA_ARCHIVO 50
#define MAX_CHAR_CADENA 150
#define TAM_IP 16
#define TAM_URL 50
#define RUTA_POR_DEFECTO_HOST_SISTEMA "C:/Windows/system32/drivers/etc/hosts"  
#define RUTA_POR_DEFECTO_HOST_TEMPORAL "hosts_tmp"

//Funciones principales del programa
void editarArchivoHosts();

//Funciones dedicadas al tratamiento de datos.
char solicitarRutaArchivo(char *rutaArchivo);
char solicitarRutaArchivoHostsSistema(char *rutaArchivo);
FILE *inicializarPunteroArchivo(char *rutaArchivo, char *modo);
bool esLineaComentario(char *linea);
bool obtenerStringsIpUrl(char *stringIP, char *stringURL, char *contenidoLinea);
void obtenerParesIpUrl(FILE *archivoHostsProporcionado, struct parIpUrl *);
void mostrarContenidoArchivo(FILE *archivoA);
void parNuevoCopiarEnArchivoTmp(struct parIpUrl *paresIpUrlHostsPropuesto, struct parIpUrl *paresIpUrlHostsSistema);
void anadirDatosHostsSO(FILE *archivoHostsSistema);

//Funciones dedicadas a la presentación de información al usuario
void infoUsrMenuInicial();
void infoUsrFinalPrograma();
void infoUsrSolicitarRutaManual();
void infoUsrUsarRutaDefault();
void infoUsrInicioMostrarContenidos();
void infoUsrFinMostrarContenidos();
void infoUsrErrorObtenerStrings(int numLinea);

//Predeclaración de la estructura para contener los pares IP URL con sus respectivos máximos de caracteres aceptados.
struct parIpUrl {
	char ip[TAM_IP];
	char url[TAM_URL];
	int numParesEncontrados;
};
