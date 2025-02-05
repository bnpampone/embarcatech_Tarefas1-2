#include "pico/stdlib.h"
#include "pico/time.h"

#define LED_BLUE 11
#define LED_RED 12
#define LED_GREEN 13
#define BUTTON_A 5

bool led_active = false; // Para saber o estado do Leds LIGADO/DESLIGADO
int led_state = 0; // Gerencia quantos Leds estão LIGADOS/DESLIGADOS

int64_t led_state_callback(alarm_id_t id, void *user_data){
  if(led_state == 1){
    gpio_put(LED_BLUE, false);
    gpio_put(LED_RED, true);
    gpio_put(LED_GREEN, true);
    led_state = 2;
   add_alarm_in_ms(3000, led_state_callback, NULL, false);
  } else if(led_state == 2){
    gpio_put(LED_BLUE, false);
    gpio_put(LED_RED, false);
    gpio_put(LED_GREEN, true);
    led_state = 3;
   add_alarm_in_ms(3000, led_state_callback, NULL, false);
  } else if(led_state == 3){
    gpio_put(LED_BLUE, false);
    gpio_put(LED_RED, false);
    gpio_put(LED_GREEN, false);
    led_state = 0; // Retorna ao estado inicial do led 0 (TODOS LIGADOS)
    led_active = false;
  }
  return 0;
}

int main(){

  gpio_init(LED_BLUE);
  gpio_init(LED_RED);
  gpio_init(LED_GREEN);
  gpio_init(BUTTON_A);
  gpio_set_dir(LED_BLUE, GPIO_OUT);
  gpio_set_dir(LED_RED, GPIO_OUT);
  gpio_set_dir(LED_GREEN, GPIO_OUT);
  gpio_set_dir(BUTTON_A, GPIO_IN);

  gpio_pull_up(BUTTON_A);

  while(true){
    if(gpio_get(BUTTON_A) == 0 && !led_active){
      sleep_ms(50); // Debounce no botão para não ler mais de uma vez
      if(gpio_get(BUTTON_A) == 0){ // Estado Inicial do Led pós pressionar botão
          gpio_put(LED_BLUE, true);
          gpio_put(LED_RED, true);
          gpio_put(LED_GREEN, true);
          
          led_active = true; // Define o estado do LED como LIGADO
          led_state = 1;
          add_alarm_in_ms(3000, led_state_callback, NULL, false);
      }
    }
    sleep_ms(10); // Para melhorar a eficiência da CPU
  }


}