# APS1-Embarcados - Tocador de músicas 8-bit em SAM-E70
Atividade Pratica Supervisionada da materia Sistemas Emarcados ministrada no Quinto Semestre de Engenharia da Computação. O objetivo da mesma é familizar o estudante com o Kit de desenvolvimento - ATSAME70-XPLD. 
## Começando
Para conseguir tocar músicas em seu kit será necessário o uso e experiência com o software de desenvolvimento Atmel Studio e de GitHub.

## Pré-requisitos
* Atmel Studio  
* ATSAME70-XPLD
* Buzzer
* OLED XPLAINED PRO

## Instalando
Para realizar a instalação da infraestrutura necessária será necessário seguir os seguintes passos descritos neste link:  
https://insper.github.io/ComputacaoEmbarcada/Sobre-Ferramental/

## Como funciona  
O código está estrutuarado da seguinte maneira: Temos um array contendo as frequências de cada e um array contendo sua duração em ms para três músicas. Para emitirmos som no buzzer, ligamos a um sinal PWM com a frequência de cada nota. Para sincronizar cada nota com seu tempo certo, calculamos quanto tempo leva para cada ciclo do buzzer e ajustamos de acordo. Os três botões da placa OLED são para alternar entre as músicas e seus leds servem de identificador visual, além de piscarem de acordo com as notas da música. O botão SW3000 funciona como pause/play e o LED da placa acende quando a música está pausada.

## Configuração
  
### Buzzer
##### +VCC  
* SAME70-> PC13  
##### -VCC
* SAME70-> +VCC
  
  
### OLED XPLAINED PRO
* SAME70-> EXT1
  
## Funcionalidades
### OLED XPLAINED PRO
* Botão 1 -> Marcha Imperial - Star Wars 
* Botão 2 -> Underworld - Mario 
* Botão 3 -> Música tema Mario 

### SAME70
* Botão SW300 -> Pause/Play
  
  
## Assista ao Demo do projeto funcionando:
https://youtu.be/xAPuTY2uWjs
  
## Autores

* **Leonardo Mendes**  [git](https://github.com/zMendes)
* **Lucas Leal Vale**  [git](https://github.com/lucaslealvale)


