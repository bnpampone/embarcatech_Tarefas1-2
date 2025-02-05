# Sistema de Temporização e Clock com  Raspberry Pi Pico W

Atividade 1.
um semáforo com três LEDs (vermelho, amarelo e verde) alterna automaticamente a cada 3 segundos, utilizando um temporizador periódico (add_repeating_timer_ms()). O código inicializa os LEDs e exibe mensagens na serial enquanto a função de callback gerencia as trocas de estado.

Atividade 2.
um temporizador de disparo único (one-shot) é utilizado para controlar três LEDs (azul, vermelho e verde). Ao pressionar um botão, todos os LEDs acendem e desligam progressivamente a cada 3 segundos, utilizando add_alarm_in_ms(). O botão só pode ser acionado novamente após o ciclo completo, evitando leituras consecutivas.
