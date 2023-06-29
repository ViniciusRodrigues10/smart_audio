<h1 align="center">Analisador de Espectro de Áudio</h1>

Este projeto implementa um analisador de espectro de áudio usando um microcontrolador STM32, micrfone e uma conexão USB para comunicação com um computador. O analisador de espectro captura os dados do microfone e os envia para o computador, onde um programa Python processa esses dados e plota o espectro de frequências em tempo real utilizando a Transformada Rápida de Fourier (FFT).

## Requisitos de Hardware
Microcontrolador STM32 (por exemplo, STM32F407Vetx)

Microfone

Conversor serial para conectar o microcontrolador ao computador

## Requisitos de Software
IDE de desenvolvimento STM32 (por exemplo, System Workbench)

Python 3.x

Bibliotecas Python: tkinter, numpy, serial, matplotlib

## Configuração do Hardware
Conecte o microfone ao microcontrolador STM32 na porta PA0, seguindo as especificações do hardware utilizado.

## Configuração do Software
Clone este repositório para o seu computador:

```
git clone https://github.com/seu-usuario/nome-do-projeto.git
```
Copie o código em C e abra a sua IDE System Workbench ou STM32CubeIDE, cole o código e compile-o para o microcontrolador STM32. Certifique-se de configurar corretamente as bibliotecas USB e as configurações de comunicação.

Conecte o microcontrolador ao computador usando o conversor USB.

## Execute o programa Python:
Antes de rodar seu programa Python é essencial que você informe a porta USB que foi conectado o seu conversor serial. Para isso no código em Python no módulom `main` subtitua a variável `USB_PORT= 'COM7'` por `USB_PORT= 'SUA_PORTA_USB_UTILIZADA'`.

Abra o programa Python e rode-o caso esteja uitilizando o VSCODE clique com o botão dereito do mouse, vá em `run python` -> `run python file in terminal`.

No microcontrolador STM32, inicie a captura de áudio e envie os dados para o computador via USB.

O programa Python receberá os dados do microcontrolador e exibirá um gráfico do espectro de frequências calculadas usando a FFT.

## Contribuição

<table>
  <tr>
    <td align="center"><a href=""><img style="border-radius: 50%;" src="https://github.com/ViniciusRodrigues10/smart_audio/assets/76957963/93a3c388-4a48-42c6-a05a-af6f69f42221" width="100px;" alt=""/><br /><sub><b>Victor Gangorra</b></sub></a><br /><a href="" title=""></a></td>
    <td align="center"><br /><sub><b>Fagner de Araújo</b></sub></a><br /><a></a></td>
  </tr>
</table>

Contribuições para a melhoria deste projeto são bem-vindas. Se você encontrar problemas ou tiver sugestões, por favor, abra uma issue neste repositório.

## Autor

<img style="border-radius: 50%;" src="https://github.com/ViniciusRodrigues10/smart_audio/assets/76957963/fc14df0f-91d9-4dc7-96c9-ccac07e8a963" width="100px;" alt=""/>
<br />

<sub><b>Vinícius Rodrigues</b></sub></a> <a href="https://github.com/ViniciusRodrigues10" title="smart_audio"></a>
<br />

Entre em contato!

[![Linkedin Badge](https://img.shields.io/badge/-Vinicius_Rodrigues-blue?style=flat-square&logo=Linkedin&logoColor=white&link=https://www.linkedin.com/in/tgmarinho/)](https://www.linkedin.com/in/viniciusgonzagacavalcante/) 
[![Gmail Badge](https://img.shields.io/badge/-vinicius.gonzaga@academico.ifpb.edu.br-c14438?style=flat-square&logo=Gmail&logoColor=white&link=mailto:vinicius.gonzaga@academico.ifpb.edu.br
)](mailto:vinicius.gonzaga@academico.ifpb.edu.br)
