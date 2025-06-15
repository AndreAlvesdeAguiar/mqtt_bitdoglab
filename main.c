#include <string.h>
#include "pico/stdlib.h"
#include "pico/cyw43_arch.h"
#include "include/wifi_conn.h"
#include "include/mqtt_comm.h"

#define BOTAO_GPIO 5

int main() {
    stdio_init_all();

    // Inicializa o GPIO como entrada com pull-up
    gpio_init(BOTAO_GPIO);
    gpio_set_dir(BOTAO_GPIO, GPIO_IN);
    gpio_pull_up(BOTAO_GPIO);

    connect_to_wifi("Login", "Senha");

    mqtt_setup("bitdog1", "192.168.15.13", "", "");

    while (true) {
        int estado = gpio_get(BOTAO_GPIO);  // 1 = solto, 0 = pressionado

        // Cria mensagem com o estado do botão (como string "0" ou "1")
        char mensagem[2];
        snprintf(mensagem, sizeof(mensagem), "%d", estado);

        // Publica a mensagem no tópico definido
        mqtt_comm_publish("bitdoglab/entrada/botao1", (uint8_t *)mensagem, strlen(mensagem));

        sleep_ms(1000);  // 1 segundo
    }

    return 0;
}
