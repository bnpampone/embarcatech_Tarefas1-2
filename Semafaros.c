#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/timer.h"

#define LED_RED 11 // atributo = 0
#define LED_YELLOW 12 // atributo = 1
#define LED_GREEN 13 // atributo = 2 e retorna a 0

static volatile uint attribute = 0; //Inicia a contagem 

// Função CallBack

bool repeating_timer_callback(struct repeating_timer *t) {

    switch (attribute) {
        case 0: // Sinal Vermelho
            gpio_put(LED_RED, 1);
            gpio_put(LED_GREEN, 0);
            printf("\nSinal Vermelho! \n\n");
            attribute = 1;
            break;

        case 1: // Sinal Amarelo
            gpio_put(LED_RED, 0);
            gpio_put(LED_YELLOW, 1);
            printf("\nSinal Amarelo! \n\n");
            attribute = 2;
            break;

        case 2: // Sinal Verde
            gpio_put(LED_YELLOW, 0);
            gpio_put(LED_GREEN, 1);
            printf("\nSinal Verde! \n\n");
            attribute = 0;
            break;
    }

    return true; // Para não parar o looping
}



int main(){
  stdio_init_all(); // Serial

gpio_init(LED_RED);
gpio_set_dir(LED_RED, GPIO_OUT);
gpio_put(LED_RED, 1); // Led começa ligado no looping do semafaro

gpio_init(LED_YELLOW);
gpio_set_dir(LED_YELLOW, GPIO_OUT);
gpio_put(LED_YELLOW, 0); // Led começa desligado

gpio_init(LED_GREEN);
gpio_set_dir(LED_GREEN, GPIO_OUT);
gpio_put(LED_GREEN, 0); // Led começa desligado


struct repeating_timer timer;
add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer); //Loop do temporizador com parametros de 3s e callback

while(true){
  printf("ATENÇÃO AO SEMÁFARO!!"); // Cada 1s mensagem é enviada e em 3s é enviado o estado do semafaro
  sleep_ms(1000);
}
}