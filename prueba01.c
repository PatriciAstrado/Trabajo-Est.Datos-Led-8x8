//https://www.woolseyworkshop.com/2018/06/20/blink-making-an-led-blink-on-a-raspberry-pi/
#include <signal.h>
#include <stdio.h>
#include <pigpio.h>

const int RedLED = 21;
volatile sig_atomic_t signal_received = 0;

void sigint_handler(int signal) {
   signal_received = signal;
}

int main() {
   if (gpioInitialise() == PI_INIT_FAILED) {
      printf("ERROR: Failed to initialize the GPIO interface.\n");
      return 1;
   }
   gpioSetMode(RedLED, PI_OUTPUT);
   signal(SIGINT, sigint_handler);
   printf("Press CTRL-C to exit.\n");
   while (!signal_received) {
      gpioWrite(RedLED, PI_HIGH);
      time_sleep(1);
      gpioWrite(RedLED, PI_LOW);
      time_sleep(1);
   }
   gpioSetMode(RedLED, PI_INPUT);
   gpioTerminate();
   printf("\n");
   return 0;
}
