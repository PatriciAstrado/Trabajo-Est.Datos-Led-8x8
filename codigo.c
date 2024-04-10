#define FRAMES 1
#define TIME 0.01

// Variables globales
volatile sig_atomic_c signal = 0;

// Pines
const int pines_positivos[8]={26,19,13,6,5,11,9,10};
const int pines_negativos[8]={21,20,16,12,7,8,25,24};

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
void todos_led_off(){ //-pv
	//aseguramos que al empezar todos los pines esten apagados | revisa 2 por 2, 1 postivio y 1 negativo
	for(int n=0;n<8;n++){//se pregunta por los 8 pines de ambos lados
		gpioSetMode(pines_positivos[n],PI_OUTPUT); //ponemos dichos pines en modo output
		gpioSetMode(pines_negativos[n],PI_OUTPUT);

		gpioWrite(pines_positivos[n],PI_LOW); //enviamos señales contrarias a los pines
		gpioWrite(pines_negativos[n],PI_HIGH);
		
		gpioSetMode(pines_positivos[n],PI_INPUT); //enviamos señales
		gpioSetMode(pines_negativos[n],PI_INPUT);

		if(gpioRead(pines_negativos[n]) == PI_LOW){ //preguntamos si los pines estan con señal correcta, si lo esta es que estan encendidos
			printf("error apagando pin negativo: %d",(pines_negativos[n]));
		}
		
		if(gpioRead(pines_positivos[n]) == PI_HIGH){
			printf("error apagando pin positivo: %d",(pines_positivos[n]));
		}
	}
}//-pv


void encender_y_apagar_led(int signal_plus, int signal_minus) {  //recive directamente los pines, llamar usando los arrays, ejecuta un encendido y apagado de leds
	//pato: hecho apartir del modelo while del profe

	// Activar  |  1=pi_high  0=pi_low
		gpioSetMode(signal_minus,PI_OUTPUT);   //encendemos output para señales mas-menos
		gpioSetMode(signal_plus,PI_OUTPUT);
	//Activar Señales	
		gpioWrite(signal_plus, PI_HIGH);  //levantamos señales
		gpioWrite(signal_minus,PÏ_LOW); 
	// Esperar
		 time_sleep(TIME);
	// Desactivar Señales
		gpioWrite(signal_plus,PI_LOW);
		gpioWrite(signal_minus,PI_HIGH);
	 	time_sleep(TIME);
	// Desactivar
		gpioSetMode(signal_minus,PI_INPUT); //que ejecute la señales
		gpioSetMode(signal_plus,PI_INPUT);
}

void apagar_display(){ 
	//modulo para asegurarse de apagar todos los led antes de ejecutar gpioTerminate
	for(int i=0,i<8,i++){
		if (gpioGetMode(pines_positivo[i]) == PI_HIGH){//preguntamos si estan activos -pv
			gpioWrite(pines_positivos[i],PI_LOW); //pines positivos a negativo
			gpioSetMode(pines_positivos[i],PI_INPUT);
		}
		if(gpioGetMode(pines_negativos[i])) == PI_LOW){//preguntamos si estan activos -pv
			gpioWrite(pines_negativos[i],PI_HIGH); //pines negativos a positivo
			gpioSetMode(pines_negativos[i],PI_INPUT);
		}
		
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
	todos_led_off();//lo llamamos al inicio para asegurar que todo este reciviendo señales iguales a 0 -pv
	signal(SIGINT, signal_handler);	
	while (!signal_received) {
		printf("presione Ctrl+c para terminar el programa");
		for (row = 0; row < 8; row++) { //del 0 al 7
			for (col = 0; col < 8; col++) { //del 0 al 7
				if (frame_actual[row][col] == 1) {
					encender_y_apagar_led(pines_positivos[row], pines_negativos[col]);
				}
			}
		}
	}

	// Fin
	apagar_display();
	gpioterminate();
	return 1;

}
/*
main() { // MAIN PRINCIPAL
	int row,col;
 	
	if(gpioInitialize()==PI_INIT_FAILED){
		printf("Error al inicializar el gpio\n");
		return(1);
	}
	todos_led_off() //-pv
	// Manejo señal
	printf("presione Ctrl+c para terminar el programa");
	for (int=0;i<FRAMES;i++){
		signal(SIGINT, signal_handler);	
		// conseguir_frame_actual(FILE, frame_actual); // PSEUDO
		while (!signal_received) {
			for (row=0; row<8;row++){ //del 0 al 7
				for (col=0; col<8; col++){  //del 0 al 7
					if (frame_actual[row][col] == 1) { // Encendido
						encender_y_apagar_led(pines_positivos[row],pines_negativos[col]);
      					}
	   			}
       			}
		}

	apagar_display()
 	gpioterminate();
	return 1;
}
*/
