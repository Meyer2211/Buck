#include <PWM.h> //Liberia correspondiente a la señal PWM

int32_t frequency = 150000; //Frecuencia asiganada al Pin
const float Vout = 12.0; //Voltaje deseado en la salida 
const int pwmPin = 9; // Pin asignado para la señal PWM
const int VinPin1 = A4; //Pin de Lectura del Divisor de tension 1 (Salida)
const int VinPin2 = A3; //Pin de Lectura del Divisor de tension 2 (Entrada)

int PWM = 0; //Valor incial de PWM correspondiente a la fuente de 20V
int maxPWM = 254; // Valor máximo de PWM (100% ciclo de trabajo)
int minPWM = 1; // Valor minimos de PWM (0% ciclo de trabajo)

float voltaje_Out = 0; //Variable donde almacenaremos el valor censado (Salida)
float voltaje_Int = 0; //Variable donde almacenaremos el valor censado (Entrada)

void setup() {
  InitTimersSafe(); // Inicializa los temporizadores del Arduino 
  bool success = SetPinFrequencySafe(pwmPin, frequency); //Establece la frecuencia del pin pwmPin a 150 kHz.
  // Si se activa enciende el led #13 para indicar que fue correcto el funcionamiento
  if (success) {
    pinMode(13, OUTPUT);
    digitalWrite(13, HIGH);    
  }
}
void loop() {
  int Valor_Sensado_Out = analogRead(VinPin1); //Analiza la señal recibida por el divisor de tension (Salida)
  int Valor_Sensado_Int = analogRead(VinPin2); //Analiza la señal recibida por el divisor de tension (Entrada)

  // Convertir el valor analógico (0-1023) a voltaje real (suponiendo referencia de 5V)
  voltaje_Out = (Valor_Sensado_Out*(5.0 /1023.0))*3.0; //Valor sensado y Ajustado (Salida)
  voltaje_Int = (Valor_Sensado_Int*(5.0 /1023.0))*5.0; //Valor sensado y Ajustado (Entrada)

//Valores fijos de PWM basados en el analisis realizado
if (abs(voltaje_Int - 13) < 0.1) {
    PWM = 230; // Si voltaje_Int es muy cercano a 13, el PWM será igual a 230
  } else if (abs(voltaje_Int - 20) < 0.1) {
    PWM = 155; // Si voltaje_Int es muy cercano a 20, el PWM será igual a 155
  } else if (voltaje_Int != 13) {
    PWM = (Vout / voltaje_Int) * 254.0; //Valor inicial del PWM

    if (voltaje_Out < 12) {
      // Si el voltaje es menor que 12V (12V en la salida), aumentar el ciclo de trabajo
      PWM = constrain(PWM + 1, minPWM, maxPWM);
    } else if (voltaje_Out >= 12) {
      // Si el voltaje es mayor que 12V, disminuir el ciclo de trabajo
      PWM = constrain(PWM - 1, minPWM, maxPWM);
    }
  }
  pwmWrite(pwmPin, PWM); //Manda la señal PWM determinada por el pin seleccionado
}