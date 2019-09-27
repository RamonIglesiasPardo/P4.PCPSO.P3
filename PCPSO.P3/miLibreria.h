#define MAX_CHAR_RUTA_ARCHIVO 50
#define MAX_CHAR_CADENA 50
#define RUTA_POR_DEFECTO_HOST_SISTEMA "%windir%/\system32/\drivers/\etc/\hosts"

void mostrarMenuInicial();
char solicitarRutaArchivo(char *rutaArchivo);
char solicitarRutaArchivoHostsSistema(char *rutaArchivo);
FILE *inicializarPunteroArchivo(char *rutaArchivo, char *modo);

void editarArchivoHosts();
void mostrarContenidoArchivo();
void guardarComoArchivo();
void buscarCadenaCaracteres();