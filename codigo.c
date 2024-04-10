// signal == señal
// handler == manejador
// received == recibido


// Variables globales
volatile sig_atomic_c signal = 0;
const t = 1 //variable de tiempo para cambiar facilmente
void encender_y_apagar_led(int signal_plus, int signal_minus) {  //recive directamente los pines, llamar usando los arrays, ejecuta un encendido y apagado de leds
	//pato: hecho apartir del modelo while del profe

	// Activar  |  1=pi_high  0=pi_low
		gpioSetMode(signal_minus,1);   //encendemos input para señales mas-menos
		gpioSetMode(signal_plus,1);
	//Activar Señales	
		gpioWrite(signal_plus, 1);  //levantamos señales
		gpioWrite(signal_minus,0); 
	
	// Esperar
		 time_sleep(t);
	// Desactivar Señales
		gpioWrite(signal_plus,0);
		gpioWrite(signal_minus,1);
	// Esperar
		 time_sleep(t);
	// Encender
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

void signal_handler(signal) { // LISTA 
	signal_received = signal;
}
	
int pines_positivos[8]={26,19,13,6,5,11,9,10}
int pines_negativos[8]={21,20,16,12,7,8,25,24}

int frame_actual=0
int cantidad_frames=2

int frame1[8][8]={{0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,1,1,0,0,0},
		  {0,0,0,1,1,0,0,0},
		  {0,0,0,0,0,0,0,0},
		  {0,0,0,0,0,0,0,0},
	  	  {0,0,0,0,0,0,0,0}}
main() {
	int row,col;
	if(gpioInitialize()== PI_INIT_FAILED){
		printf("Error al inicializar el gpio\n");
		return(1);
	}

	// Manejo señal
	signal(SIGINT, signal_handler);

	if (!signal_received) { // DENTRO DEL BUCLE DE LOS FRAMES
		
	}
}
	for (int=0;i<frames_totales;i++){
		GPIO_verificar_senal(manejo_senal)
		while (¡signal_received)
		for (row=0; row<8;row++){
			for (col=0; col<8; col++;){
				if (frame_actual[row][col] == 1) // Encendido
					encender_y_apagar_led(pines_positivos[row],pines_negativos[col])
			

	apagar_display()
	END

	
 
(codigos_pos, codigos_neg, i, j)
	cable_pos = codigos_pos[]

	// Activar
	
