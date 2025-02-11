# Controle de Servomotor com PWM e LED RGB

## Descrição
Este projeto utiliza o microcontrolador Raspberry Pi Pico para controlar um servomotor por meio de PWM (Pulse Width Modulation). Além disso, um LED RGB é utilizado para fornecer feedback visual, mudando de cor conforme o ângulo do servomotor. O código foi desenvolvido em C utilizando o Pico SDK e é compatível com a ferramenta de simulação Wokwi.

## Funcionalidades
- Controle de um servomotor com PWM, ajustando o ângulo entre 0° e 180°.
- Movimentação suave do servomotor com incrementos de ±5 µs.
- Controle de um LED RGB que muda de cor conforme o ângulo do servomotor:
  - Vermelho: 180 graus.
  - Verde: 90 graus.
  - Azul: 0 graus.
- Movimentação periódica do servomotor entre 0° e 180° com feedback visual no LED RGB.

## Hardware e Conexões

### Componentes Utilizados
- Raspberry Pi Pico (Microcontrolador RP2040).
- Servomotor (Motor micro servo padrão).
- LED RGB (Comum ou da BitDogLab).
- Jumpers e protoboard (para conexões).

### Conexões
| Componente          | GPIO do Raspberry Pi Pico |
|---------------------|---------------------------|
| Servomotor (Sinal)  | GPIO 22                   |
| LED RGB (Vermelho)  | GPIO 13                   |
| LED RGB (Verde)     | GPIO 11                   |
| LED RGB (Azul)      | GPIO 12                   |

## Compilação e Execução

### Pré-requisitos
- Pico SDK: Configurado no ambiente de desenvolvimento.
- GCC Arm Toolchain: Para compilar o código.
- CMake: Para gerenciar o processo de build.

### Passos para Compilar e Executar
1. Clone o repositório:
   ```sh
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DO_REPOSITORIO>

   Claro! Vou ajustar o seu README.md para que ele fique mais claro e organizado, seguindo os requisitos do projeto.

```markdown
# Controle de Servomotor com PWM e LED RGB

## Descrição
Este projeto utiliza o microcontrolador Raspberry Pi Pico para controlar um servomotor por meio de PWM (Pulse Width Modulation). Além disso, um LED RGB é utilizado para fornecer feedback visual, mudando de cor conforme o ângulo do servomotor. O código foi desenvolvido em C utilizando o Pico SDK e é compatível com a ferramenta de simulação Wokwi.

## Funcionalidades
- Controle de um servomotor com PWM, ajustando o ângulo entre 0° e 180°.
- Movimentação suave do servomotor com incrementos de ±5 µs.
- Controle de um LED RGB que muda de cor conforme o ângulo do servomotor:
  - Vermelho: 180 graus.
  - Verde: 90 graus.
  - Azul: 0 graus.
- Movimentação periódica do servomotor entre 0° e 180° com feedback visual no LED RGB.

## Hardware e Conexões

### Componentes Utilizados
- Raspberry Pi Pico (Microcontrolador RP2040).
- Servomotor (Motor micro servo padrão).
- LED RGB (Comum ou da BitDogLab).
- Jumpers e protoboard (para conexões).

### Conexões
| Componente          | GPIO do Raspberry Pi Pico |
|---------------------|---------------------------|
| Servomotor (Sinal)  | GPIO 22                   |
| LED RGB (Vermelho)  | GPIO 13                   |
| LED RGB (Verde)     | GPIO 11                   |
| LED RGB (Azul)      | GPIO 12                   |

## Compilação e Execução

### Pré-requisitos
- Pico SDK: Configurado no ambiente de desenvolvimento.
- GCC Arm Toolchain: Para compilar o código.
- CMake: Para gerenciar o processo de build.

### Passos para Compilar e Executar
1. Clone o repositório:
   ```sh
   git clone <URL_DO_REPOSITORIO>
   cd <NOME_DO_REPOSITORIO>
   ```

2. Configure o ambiente de build:
   ```sh
   mkdir build
   cd build
   cmake ..
   ```

3. Compile o código:
   ```sh
   make
   ```

4. Carregue o binário gerado no Raspberry Pi Pico.

## Código Principal (Servo_Control_PWM.c)
O código principal está organizado da seguinte forma:
- **Configuração do PWM:** Define a frequência e o ciclo ativo para controlar o servomotor e o LED RGB.
- **Movimentação do Servomotor:** Ajusta o ângulo do servomotor em três posições principais (0°, 90°, 180°) e realiza uma movimentação suave entre elas.
- **Controle do LED RGB:** Altera a cor do LED RGB conforme o ângulo do servomotor.

### Experimento com a Ferramenta Educacional BitDogLab
Utilizando a ferramenta BitDogLab, observe o comportamento da iluminação do LED RGB conforme o ângulo do servomotor. O LED deve mudar de cor de acordo com a posição do servomotor, proporcionando um feedback visual claro.

```