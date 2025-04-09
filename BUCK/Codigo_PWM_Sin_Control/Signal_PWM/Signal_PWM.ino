#include <PWM.h> // Se incluye la librería PWM.h, la cual permite controlar el ancho de pulso de una señal PWM y cambiar la frecuencia de los pines PWM. Esta librería ofrece funciones avanzadas para el control de PWM.
int32_t frequency = 150000; // Se define la frecuencia de la señal PWM en 150 kHz. Esto significa que la señal generada en el pin tendrá esa frecuencia.
const int pwmPin = 9; // Se define el pin del Arduino que se utilizará para generar la señal PWM
//El “Void Setup” es una función que se ejecuta una sola vez al inicio para configurar el entorno.
void setup() {
  InitTimersSafe(); // Inicializa los temporizadores del Arduino de manera segura, asegurándose de que no entren en conflicto con otras funciones de hardware.
  bool success = SetPinFrequencySafe(pwmPin, frequency); //Establece la frecuencia del pin pwmPin a 150 kHz. Esta función devuelve true si la configuración es exitosa. En caso de éxito, se ejecutan las instrucciones dentro del bloque if.
  if (success) {
    pinMode(13, OUTPUT); //Esto sirve como una indicación de que la configuración de PWM ha sido exitosa. (enciende el LED conectado al pin 13, que es el LED integrado en muchas placas Arduino)
    digitalWrite(13, HIGH);    
  }
}
//El “Void loop” es una función que se ejecuta continuamente una vez por ciclo de programa.
void loop() { 
  pwmWrite(pwmPin,187); //Esta función genera una señal PWM en el pin 9 con un valor de 153 sobre un rango de 0 a 255. El valor de 153 corresponde a un ciclo de trabajo del 60% (aproximadamente), lo que significa que el pin estará en alto el 60% del tiempo y en bajo el 40% del tiempo en cada ciclo de la señal PWM.
}
