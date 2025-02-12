#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pwm.h"

#define PINO_SERVO 22        // GPIO 22 para o servomotor

// Definições LED RGB
#define PINO_LED_VERMELHO 13 // GPIO 13 para o LED RGB (vermelho)
#define PINO_LED_VERDE 11    // GPIO 11 para o LED RGB (verde)
#define PINO_LED_AZUL 12     // GPIO 12 para o LED RGB (azul)
// Definições com const int
const int FREQUENCIA_PWM = 50;    // Frequência de 50 Hz (período de 20 ms)
const int VALOR_WRAP = 20000;     // Valor de wrap para 20 ms (50 Hz)
const int TEMPO_ESPERA_MS = 5000; // Tempo de espera em cada posição (5 segundos)
const int ATRASO_SUAVE_MS = 10;   // Atraso para movimentação suave (10 ms)
const int INCREMENTO_US = 5;      // Incremento de ciclo ativo para movimentação suave (±5 µs)

// Função para configurar o PWM
void configurar_pwm(uint pino, uint frequencia, uint wrap)
{
    gpio_set_function(pino, GPIO_FUNC_PWM);       // Configura o pino para função PWM
    uint num_slice = pwm_gpio_to_slice_num(pino); // Obtém o slice do PWM
    pwm_set_wrap(num_slice, wrap);                // Define o valor de wrap
    pwm_set_clkdiv(num_slice, 125.0f);            // Configura o divisor de clock para 125 (125 MHz / 125 = 1 MHz)
    pwm_set_enabled(num_slice, true);             // Habilita o PWM
}

// Função para definir o ciclo ativo (duty cycle) em microssegundos
void definir_ciclo_ativo_us(uint pino, uint ciclo_us)
{
    uint num_slice = pwm_gpio_to_slice_num(pino); // Obtém o slice do PWM
    pwm_set_chan_level(num_slice, pwm_gpio_to_channel(pino), ciclo_us); // Define o nível do canal
}

int main()
{
    stdio_init_all(); // Inicializa a comunicação serial (para debug)

    // Configura o PWM no pino 22 para o servomotor
    configurar_pwm(PINO_SERVO, FREQUENCIA_PWM, VALOR_WRAP);
    printf("PWM configurado no GPIO %d para o servomotor.\n", PINO_SERVO); // Mensagem de configuração

    // Configura o PWM nos pinos 11, 12 e 13 para o LED RGB
    configurar_pwm(PINO_LED_VERMELHO, FREQUENCIA_PWM, VALOR_WRAP); // Configura o PWM no pino 13 (vermelho)
    configurar_pwm(PINO_LED_VERDE, FREQUENCIA_PWM, VALOR_WRAP);   // Configura o PWM no pino 11 (verde)
    configurar_pwm(PINO_LED_AZUL, FREQUENCIA_PWM, VALOR_WRAP);   // Configura o PWM no pino 12 (azul)
    printf("PWM configurado nos GPIOs %d (vermelho), %d (verde) e %d (azul) para o LED RGB.\n",
           PINO_LED_VERMELHO, PINO_LED_VERDE, PINO_LED_AZUL); // Mensagem de configuração

    // 1. Vai direto para 180 graus (2400 µs) no início
    definir_ciclo_ativo_us(PINO_SERVO, 2400);
    printf("Servomotor: Ciclo ativo definido para 2400 µs (180 graus). Aguardando 5 segundos...\n");

    // Controla o LED RGB (cor correspondente ao ângulo)
    definir_ciclo_ativo_us(PINO_LED_VERMELHO, 2400); // Vermelho máximo
    definir_ciclo_ativo_us(PINO_LED_VERDE, 0);       // Verde mínimo
    definir_ciclo_ativo_us(PINO_LED_AZUL, 0);        // Azul mínimo
    printf("LED RGB: Cor vermelha (180 graus).\n");
    sleep_ms(TEMPO_ESPERA_MS); // Aguarda 5 segundos

    // 2. Define o ciclo ativo para 1.470 µs (90 graus)
    definir_ciclo_ativo_us(PINO_SERVO, 1470);
    printf("Servomotor: Ciclo ativo definido para 1470 µs (90 graus). Aguardando 5 segundos...\n");

    // Controla o LED RGB (cor correspondente ao ângulo)
    definir_ciclo_ativo_us(PINO_LED_VERMELHO, 0); // Vermelho mínimo
    definir_ciclo_ativo_us(PINO_LED_VERDE, 1470); // Verde médio
    definir_ciclo_ativo_us(PINO_LED_AZUL, 0);     // Azul mínimo
    printf("LED RGB: Cor verde (90 graus).\n");
    sleep_ms(TEMPO_ESPERA_MS); // Aguarda 5 segundos

    // 3. Define o ciclo ativo para 500 µs (0 graus)
    definir_ciclo_ativo_us(PINO_SERVO, 500);
    printf("Servomotor: Ciclo ativo definido para 500 µs (0 graus). Aguardando 5 segundos...\n");

    // Controla o LED RGB (cor correspondente ao ângulo)
    definir_ciclo_ativo_us(PINO_LED_VERMELHO, 0); // Vermelho mínimo
    definir_ciclo_ativo_us(PINO_LED_VERDE, 0);    // Verde mínimo
    definir_ciclo_ativo_us(PINO_LED_AZUL, 500);   // Azul máximo
    printf("LED RGB: Cor azul (0 graus).\n");
    sleep_ms(TEMPO_ESPERA_MS); // Aguarda 5 segundos

    // 4. Movimentação periódica suave entre 0 e 180 graus
    printf("Iniciando movimentação periódica suave entre 0 e 180 graus...\n");
    while (true)
    {
        // Movimentação de 0 a 180 graus (500 µs a 2400 µs)
        for (uint ciclo_us = 500; ciclo_us <= 2400; ciclo_us += INCREMENTO_US)
        {
            definir_ciclo_ativo_us(PINO_SERVO, ciclo_us); // Define o ciclo ativo

            // Atualiza o LED RGB conforme o ângulo
            definir_ciclo_ativo_us(PINO_LED_VERMELHO, ciclo_us);               // Intensidade vermelha aumenta
            definir_ciclo_ativo_us(PINO_LED_VERDE, 2400 - ciclo_us);           // Intensidade verde diminui
            definir_ciclo_ativo_us(PINO_LED_AZUL, 500 + (ciclo_us - 500) / 2); // Intensidade azul varia

            // Exibe informações de ângulo e cor do LED RGB
            printf("Servomotor: Movendo para %d µs (ângulo aproximado: %.1f graus)\n", ciclo_us, (ciclo_us - 500) / 10.56);
            printf("LED RGB: Vermelho=%d, Verde=%d, Azul=%d\n", ciclo_us, 2400 - ciclo_us, 500 + (ciclo_us - 500) / 2);
            sleep_ms(ATRASO_SUAVE_MS); // Atraso para movimentação suave
        }

        // Movimentação de 180 a 0 grgitaus (2400 µs a 500 µs)
        for (uint ciclo_us = 2400; ciclo_us >= 500; ciclo_us -= INCREMENTO_US)
        {
            definir_ciclo_ativo_us(PINO_SERVO, ciclo_us); // Define o ciclo ativo

            // Atualiza o LED RGB conforme o ângulo
            definir_ciclo_ativo_us(PINO_LED_VERMELHO, ciclo_us);               // Intensidade vermelha diminui
            definir_ciclo_ativo_us(PINO_LED_VERDE, 2400 - ciclo_us);           // Intensidade verde aumenta
            definir_ciclo_ativo_us(PINO_LED_AZUL, 500 + (ciclo_us - 500) / 2); // Intensidade azul varia

            // Exibe informações de ângulo e cor do LED RGB
            printf("Servomotor: Movendo para %d µs (ângulo aproximado: %.1f graus)\n", ciclo_us, (ciclo_us - 500) / 10.56);
            printf("LED RGB: Vermelho=%d, Verde=%d, Azul=%d\n", ciclo_us, 2400 - ciclo_us, 500 + (ciclo_us - 500) / 2);
            sleep_ms(ATRASO_SUAVE_MS); // Atraso para movimentação suave
        }
    }

    return 0; // Retorna 0 (sem erros)
}