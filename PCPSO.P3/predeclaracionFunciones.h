#define MAX_CHAR_RUTA_ARCHIVO 50
#define MAX_CHAR_CADENA 50
#define RUTA_POR_DEFECTO_HOST_SISTEMA "..\/PCPSO.P3/hosts" //"%windir%/\system32/\drivers/\etc/\hosts"    C:\\Windows\\System32\\drivers\\etc\\hosts      %windir%\system32\drivers\etc\hosts    ../PCPSO.P3/hostsProporcionado.txt
#define RUTA_POR_DEFECTO_HOST_TEMPORAL "..\/PCPSO.P3\/hosts_tmp"

//Funciones principales del programa
void editarArchivoHosts();

//Funciones dedicadas al tratamiento de datos.
char solicitarRutaArchivo(char *rutaArchivo);
char solicitarRutaArchivoHostsSistema(char *rutaArchivo);
FILE *inicializarPunteroArchivo(char *rutaArchivo, char *modo);
void mostrarContenidoArchivo(FILE *archivoA);
void guardarComoArchivo();
void buscarCadenaCaracteres();

//Funciones dedicadas a la presentación de información al usuario
void infoUsrMenuInicial();
void infoUsrFinalPrograma();
void infoUsrSolicitarRutaManual();
void infoUsrUsarRutaDefault();
void infoUsrInicioMostrarContenidos();
void infoUsrFinMostrarContenidos();