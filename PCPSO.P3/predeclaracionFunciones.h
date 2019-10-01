#define MAX_CHAR_RUTA_ARCHIVO 50
#define MAX_CHAR_CADENA 150
#define TAM_IP 16
#define TAM_URL 50
#define RUTA_POR_DEFECTO_HOST_SISTEMA "../PCPSO.P3/hosts" //"%windir%/\system32/\drivers/\etc/\hosts"    C:\\Windows\\System32\\drivers\\etc\\hosts      %windir%\system32\drivers\etc\hosts    ../PCPSO.P3/hostsProporcionado.txt
#define RUTA_POR_DEFECTO_HOST_TEMPORAL "../PCPSO.P3/hosts_tmp"

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
void parNuevoCopiarEnArchivoTmp(struct parIpUrl *paresIpUrlHostsPropuesto, struct parIpUrl *paresIpUrlHostsSistema, FILE *archivoTemp);
void guardarComoArchivo();
void buscarCadenaCaracteres();

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
