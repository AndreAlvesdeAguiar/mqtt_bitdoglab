# 🛰️ Instalação e Uso do Broker Mosquitto no Windows

Este guia explica como instalar e rodar o **broker MQTT Mosquitto** em uma máquina com Windows, permitindo o envio e recebimento de mensagens MQTT com dispositivos IoT, como a **BitDog Lab**.

---

## 📥 1. Baixar o Mosquitto

1. Acesse o site oficial: [https://mosquitto.org/download](https://mosquitto.org/download)
2. Baixe o instalador para Windows (formato `.exe`)
3. Durante a instalação:
   - Marque a opção para instalar o **serviço**
   - Finalize a instalação normalmente

---

## 🔥 2. Permitir o Mosquitto no Firewall

Para que dispositivos externos (como sua BitDog Lab) possam se conectar, é necessário liberar a porta `1883`.

Abra o terminal como **Administrador** e execute:

```bash
netsh advfirewall firewall add rule name="Mosquitto MQTT" dir=in action=allow protocol=TCP localport=1883
```

---

## 🗂️ 3. Criar o arquivo de configuração para conexões externas

Por padrão, o Mosquitto roda em **modo local** e rejeita conexões externas. Para mudar isso:

### 📁 Etapas:

1. Crie a pasta:

```
C:\mosquitto_config
```

2. Crie um novo arquivo chamado `mosquitto.conf` dentro dessa pasta.

> 💡 **Atenção**: garanta que o nome do arquivo seja `mosquitto.conf` (sem `.txt` escondido no final). Ative a opção "Extensões de nome de arquivo" no Windows Explorer para ter certeza.

### ✍️ Conteúdo do arquivo `mosquitto.conf`:

```conf
listener 1883
allow_anonymous true
```

---

## 🧪 4. Rodar o Mosquitto manualmente

Abra o terminal e execute os comandos abaixo para rodar o broker com o novo arquivo de configuração:

```bash
cd "C:\Program Files\mosquitto"
mosquitto.exe -c "C:\mosquitto_config\mosquitto.conf" -v
```

Você verá algo assim:

```
mosquitto version 2.0.21 starting
Using config file: C:\mosquitto_config\mosquitto.conf
Opening ipv4 listen socket on port 1883.
mosquitto version 2.0.21 running
```

> O parâmetro `-v` ativa o modo **verbose**, mostrando conexões e mensagens publicadas.

---

## 📡 5. Testar com BitDog Lab ou outro cliente MQTT

Se o Mosquitto estiver rodando corretamente, a **BitDog Lab** (ou qualquer outro microcontrolador com Wi-Fi) poderá se conectar usando o **IP local da sua máquina Windows** (por exemplo, `192.168.15.13`).

### 🧪 Teste com ferramentas nativas:

#### Assinar um tópico (ouvir mensagens):

```bash
mosquitto_sub -h localhost -t "bitdoglab/entrada/botao1"
```

#### Publicar uma mensagem:

```bash
mosquitto_pub -h localhost -t "bitdoglab/entrada/botao1" -m "1"
```

---

## 🚀 6. Dica: Rodar Mosquitto como serviço (background)

Se quiser que o Mosquitto rode automaticamente como serviço em segundo plano:

```bash
net start mosquitto
```

Para parar:

```bash
net stop mosquitto
```

> ⚠️ O modo serviço usa o arquivo de configuração padrão, que **não aceita conexões externas**. Para permitir, substitua o `mosquitto.conf` no diretório de instalação ou continue rodando manualmente com `-c`.

---

## 📌 Informações úteis

- **Porta padrão MQTT:** `1883`
- **Broker local (Mosquitto):** Ideal para testes em rede privada
- **Broker online (HiveMQ):** [https://www.hivemq.com/demos/websocket-client/](https://www.hivemq.com/demos/websocket-client/) – útil para acessar MQTT pela internet
- **Protocolo utilizado:** MQTT 3.1.1
- **Exemplo de tópico:** `bitdoglab/entrada/botao1`

---

## 🤖 Projeto com BitDog Lab

### Exemplo de conexão no código C (RP2040 com Wi-Fi):

```c
mqtt_setup("bitdog1", "192.168.15.13", "", "");
mqtt_comm_publish("bitdoglab/entrada/botao1", (uint8_t *)"1", 1);
```

---

## 🛠️ Ferramentas recomendadas

- [MQTT Explorer](https://mqtt-explorer.com/) — para visualizar mensagens de forma gráfica
- [MQTT.fx](https://mqttfx.jensd.de/) — ferramenta leve de desktop
- `mosquitto_pub`, `mosquitto_sub` — linha de comando para testes locais

---

## ✅ Pronto! Agora seu notebook está funcionando como broker MQTT 🎉

Sua BitDog Lab já pode enviar dados diretamente para seu notebook via Wi-Fi, usando o protocolo MQTT, com total controle local para testes, simulações e integração com dashboards!
