#define FRAMES 1
#define TIME 0.01

// Espacio de nombres global
volatile sig_atomic_c signal_received = 0;
const int DURACION = 200; // En centésimas de segundo

// Pines
const int pines_positivos[8] = {26, 19, 13, 6, 5, 11, 9, 10};
const int pines_negativos[8] = {21, 20, 16, 12, 7, 8, 25, 24};

// Arreglo que contendrá el frame actual
int frame_actual[2][8][8] = {{{0,0,0,0,0,0,0,0},
		              {0,0,1,1,1,1,0,0},
   		              {0,1,1,1,1,1,1,0},
		              {0,1,0,1,1,0,1,0},
		              {0,1,1,1,1,1,1,0},
		              {0,0,1,1,1,1,0,0},
		              {0,0,1,1,1,1,0,0},
	  	              {0,0,0,0,0,0,0,0}},
			     {{0,0,1,1,1,1,0,0},
		              {0,1,1,1,1,1,1,0},
		              {0,1,0,1,1,0,1,0},
		              {0,1,1,1,1,1,1,0},
		              {0,0,1,0,0,1,0,0},
		              {0,0,0,0,0,0,0,0},
		              {0,0,0,1,1,0,0,0},
	  	              {0,0,1,1,1,1,0,0}}};
int mostrando_frame; //usado como booleano para indicar cuando terminar de mostrar un frame

// Módulos
void todos_led_off(){ //-pv
	//aseguramos que al empezar todos los pines esten apagados | revisa 2 por 2, 1 postivio y 1 negativo
	for(int n = 0; n < 8; n++){//se pregunta por los 8 pines de ambos lados
		gpioSetMode(pines_positivos[n], PI_OUTPUT); //ponemos dichos pines en modo output
		gpioSetMode(pines_negativos[n], PI_OUTPUT);

		gpioWrite(pines_positivos[n], PI_LOW); //enviamos señales contrarias a los pines
		gpioWrite(pines_negativos[n], PI_HIGH);
		
		gpioSetMode(pines_positivos[n], PI_INPUT); //enviamos señales
		gpioSetMode(pines_negativos[n], PI_INPUT);

		if(gpioRead(pines_negativos[n]) == PI_LOW){ //preguntamos si los pines estan con señal correcta, si lo esta es que estan encendidos
			printf("Error apagando pin negativo: %d\n", (pines_negativos[n]));
		}
		
		if(gpioRead(pines_positivos[n]) == PI_HIGH){
			printf("Error apagando pin positivo: %d\n", (pines_positivos[n]));
		}
	}
}//-pv

void encender_y_apagar_led(int signal_plus, int signal_minus) {  //recive directamente los pines, llamar usando los arrays, ejecuta un encendido y apagado de leds
	//pato: hecho apartir del modelo while del profe

	// Activar  |  1=pi_high  0=pi_low
		gpioSetMode(signal_minus, PI_OUTPUT);   //encendemos output para señales mas-menos
		gpioSetMode(signal_plus, PI_OUTPUT);
	//Activar Señales	
		gpioWrite(signal_plus, PI_HIGH);  //levantamos señales
		gpioWrite(signal_minus, PI_LOW); 
	// Esperar
		 time_sleep(TIME);
	// Desactivar Señales
		gpioWrite(signal_plus, PI_LOW);
		gpioWrite(signal_minus, PI_HIGH);
	 	time_sleep(TIME);
		//(Flavio)Documento_de_Leds(frame_actual);
	// Desactivar
		gpioSetMode(signal_minus, PI_INPUT); //que ejecute la señales
		gpioSetMode(signal_plus, PI_INPUT);
}

const void mostrar_frame(const int frame[8][8], const int DURACION) {
	int mostrando_frame = 1;
	gpioSetTimerFuncEx(0, DURACION * 10, avanzar_frame, &mostrando_frame); //empieza el temporizador 0 (maximo 9 simultaneos), por 2000 milisegundos (200 cs * 10 = 2000 ms)
	
	while (mostrando_frame == 1) { // cambiando mostrando_frame a 0 se rompe el ciclo e incrementa frame en 1 (usando % para no sobrepasar)
		for (int row = 0; row < 8; row++) {          //del 0 al 7
			for (int col = 0; col < 8; col++) {         //del 0 al 7
				if (frame[row][col] == 1) {
					encender_y_apagar_led(pines_positivos[row], pines_negativos[col]);
				}
			}
		}
	}	
}

void apagar_display(){ 
	//modulo para asegurarse de apagar todos los led antes de ejecutar gpioTerminate
	for(int i = 0, i < 8; i++){
		if (gpioGetMode(pines_positivo[i]) == PI_HIGH){//preguntamos si estan activos -pv
			gpioWrite(pines_positivos[i], PI_LOW); //pines positivos a negativo
			gpioSetMode(pines_positivos[i], PI_INPUT);
		}
		if(gpioGetMode(pines_negativos[i])) == PI_LOW){//preguntamos si estan activos -pv
			gpioWrite(pines_negativos[i], PI_HIGH); //pines negativos a positivo
			gpioSetMode(pines_negativos[i], PI_INPUT);
		}
		
	}
	gpioTerminate();
}

void avanzar_frame(void *mostrando_frame) {
	*mostrando_frame = 0; //esto cortara el bucle dentro del frame actual
	gpioSetTimerFunc(0, 2000, NULL);
}

const void signal_handler(int signal) {
	signal_received = signal;
}

/*(FLAVIO)void Documento_de_Leds(int frame_actual[2][8][8]){
	FILE*ledsfile=fopen("Leds.txt","a");
 	if(ledsfile==NULL){
  		printf("No se puedo abrir el archivo");
    	}
    for(int frame=0;frame<2;frame++){
   		for(row=0;row<8;row++){
   			for(col=0;col<8;col++){
				fprintf(ledsfile,"%d,",frame_actual[frame][row][col]);
   			}
     		fprintf(ledsfile,"\n");
     		
       	}	
	}
     	
       fclose(ledsfile);
  } */

int main() {
	int frame;
	/*(FLAVIO)FILE*ledsfile;
 	ledsfile=fopen("Leds.txt","w");
  	fclose(ledsfile);*/

	// Inicio
	if(gpioInitialize() == PI_INIT_FAILED){ // Inicialización del GPIO
		printf("Error al inicializar el GPIO.\n");
		return 1;
	}
	todos_led_off(); // Limpieza de ledes

	signal(SIGINT, signal_handler);	// Manejo de señal
	printf("Presione Ctrl + C para terminar el programa.\n");
	
	while (!signal_received) {
		mostrar_frame(frame_actual[frame], DURACION);
		frame=(frame+1)%2;
	}

	// Fin
	apagar_display(); // Limpieza de ledes y finalización del GPIO
	
	return 1;
}
