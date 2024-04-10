#define FRAMES 1
#define TIME 0.01

// Variables globales
volatile sig_atomic_c signal = 0;

// Pines
int pines_positivos[8]={26,19,13,6,5,11,9,10};
int pines_negativos[8]={21,20,16,12,7,8,25,24};

// Arreglo que contendrá el frame actual
int frame_actual[8][8]={{0,0,0,0,0,0,0,0},
		        {0,0,0,0,0,0,0,0},
		        {0,0,0,0,0,0,0,0},
		        {0,0,0,1,1,0,0,0},
		        {0,0,0,1,1,0,0,0},
		        {0,0,0,0,0,0,0,0},
		        {0,0,0,0,0,0,0,0},
	  	        {0,0,0,0,0,0,0,0}};

// Módulos
void encender_y_apagar_led(int signal_plus, int signal_minus) {  //recive directamente los pines, llamar usando los arrays, ejecuta un encendido y apagado de leds
	//pato: hecho apartir del modelo while del profe

	// Activar  |  1=pi_high  0=pi_low
		gpioSetMode(signal_minus,1);   //encendemos input para señales mas-menos
		gpioSetMode(signal_plus,1);
	//Activar Señales	
		gpioWrite(signal_plus, 1);  //levantamos señales
		gpioWrite(signal_minus,0); 
	// Esperar
		 time_sleep(TIME);
	// Desactivar Señales
		gpioWrite(signal_plus,0);
		gpioWrite(signal_minus,1);
	// Desactivar
		gpioSetMode(signal_minus,0); //que ejecute la señales
		gpioSetMode(signal_plus,0);
}

void apagar_display(){ 
	//modulo para asegurarse de apagar todos los led antes de ejecutar gpioTerminate
	for(int i=0,i<8,i++){
		gpioWrite(pines_positivos[i],PI_LOW); //pines positivos a negativo
		gpioSetMode(pines_positivos[i],PI_INPUT);
		gpioWrite(pines_negativos[i],PI_HIGH); //pines negativos a positivo
		gpioSetMode(pines_negativos[i],PI_INPUT);
	}
	gpioTerminate();
}

void signal_handler(signal) { // FINALIZADA //
	signal_received = signal;
}

main() { // MAIN DE PRUEBA: MANEJA UN SOLO FRAME (frame_actual) --- BORRAR POSTERIORMENTE
	int row, col;
	if(gpioInitialize() == PI_INIT_FAILED){
		printf("Error al inicializar el gpio\n");
		return 1;
	}

	printf("presione Ctrl+c para terminar el programa");
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			if (frame_actual[row][col] == 1) {
				encender_y_apagar_led(pines_positivos[row], pines_negativos[col]);
			}
		}
	}

	// Fin
	apagar_display()
	return 1;

}
/*
main() { // MAIN PRINCIPAL
	int row,col;
	if(gpioInitialize()==PI_INIT_FAILED){
		printf("Error al inicializar el gpio\n");
		return(1);
	}

	// Manejo señal
	printf("presione Ctrl+c para terminar el programa");
	for (int=0;i<FRAMES;i++){
		signal(SIGINT, signal_handler);	
		// conseguir_frame_actual(FILE, frame_actual); // PSEUDO
		while (!signal_received) {
			for (int row=0; row<8;row++){
				for (int col=0; col<8; col++;){
					if (frame_actual[row][col] == 1) { // Encendido
						encender_y_apagar_led(pines_positivos[row],pines_negativos[col]);
      					}
	   			}
       			}
		}

	apagar_display()
	return 1;
}
*/
