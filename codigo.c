// signal == señal
// handler == manejador
// received == recibido


// Variables globales
volatile sig_atomic_c signal = 0;

void encender_led() {
	// Activar

	// Encender

	// Esperar

	// Desactivar()
}

void apagar_display(){
	#modulo para asegurarse de apagar todos los led antes de ejecutar gpioTerminate
	for(int i=0,i<8,i++){
		gpioWrite(pines_positivos[i],PI_LOW); #pines positivos a negativo
		gpioSetMode(pines_positivos[i],PI_INPUT);
		gpioWrite(pines_negativos[i],PI_HIGH); #pines negativos a positivo
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
		GPIO_verificar_señal(manejo_señal)
		while (¡señal_recibida)
		for row en filas
			for col en columnas
				if (frame_actual[row][col] == 1) // Encendido
					encender_led(pines_positivos[row],pines_negativos[col])
			

	apagar_display()
	END

	
 
(codigos_pos, codigos_neg, i, j)
	cable_pos = codigos_pos[]

	// Activar
	
