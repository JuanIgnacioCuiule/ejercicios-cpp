#include <stdio.h>

char buffer[33];
char *reservadas[4] = {"inicio", "fin", "escribir", "leer"};
int i = 0;

void limpiarBuffer() {
	for (int j = 0; j < 33; ++j) {
		buffer[j] = '\0';
	}
	i = 0;
}

int largo(char palabra[]) {
	int largoDePalabra = 0;
	while (palabra[largoDePalabra] != '\0') {
		largoDePalabra++;
	}
	return largoDePalabra;
}

int strcmp(const char* s1, const char* s2) {
    while(*s1 && (*s1==*s2))
        s1++,s2++;
    return *(const unsigned char*)s1-*(const unsigned char*)s2;
}

int esPalabraReservada() {
	return strcmp(buffer, "inicio") == 0  // inicio
			|| strcmp(buffer, "fin") == 0  // fin
			|| strcmp(buffer, "escribir") == 0  // escribir
			|| strcmp(buffer, "leer") == 0; // leer
}

int esEspacio(char caracter) {
	return caracter == ' '
			|| caracter == '\n'
			|| caracter == '\t';
}

int esCaracterDePuntuacion(char caracter) {
	return caracter == ','
			|| caracter == ';'
			|| caracter == '('
			|| caracter == ')';
}

int main () {
	FILE *fp;
	fp = fopen("archivo.micro","r");

	while(!feof(fp)) {
		char letra = getc(fp);
		if (letra == '+' || letra == '-') {
			printf("Operador aditivo: %c\n", letra);
		}
		else if (letra == ':') {
			char prox = getc(fp);
			if (prox == '=' && !feof(fp)) {
				printf("Asignación: :=\n");
			} else if (feof(fp)) {
				printf("Ni idea: %c\n", letra);
				break;
			} else {
				ungetc(letra, fp);
				ungetc(prox, fp);
			}
		}
		else if(esCaracterDePuntuacion(letra)) {
			printf("Caracter de puntuación: %c\n", letra);
		}
		else {
			while(!feof(fp) && !esEspacio(letra)) {
				buffer[i] = letra;
				i++;
				letra = getc(fp);
			}
			if (esPalabraReservada()) {
				printf("Palabra reservada: %s\n", buffer);
			} else if (!feof(fp)){
				printf("Ni idea: %s\n", buffer);
			}
			limpiarBuffer();
		}
	}

	fclose(fp);
	return 0;	
}
