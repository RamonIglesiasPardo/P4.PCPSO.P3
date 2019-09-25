#define MAX_CHAR_RUTA_ARCHIVO 50
#define MAX_CHAR_CADENA 50

void mostrarMenuInicial();
char solicitarRutaArchivo(char *rutaArchivo);
FILE *inicializarPunteroArchivo(char *rutaArchivo, char *modo);
void mostrarContenidoArchivo();
void guardarComoArchivo();
void buscarCadenaCaracteres();