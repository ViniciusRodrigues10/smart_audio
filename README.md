# smart_audio
# Analisador de Espectro de Áudio com STM32
Este projeto implementa um analisador de espectro de áudio usando um microcontrolador STM32, micrfone e uma conexão USB para comunicação com um computador. O analisador de espectro captura os dados do microfone e os envia para o computador, onde um programa Python processa esses dados e plota o espectro de frequências em tempo real utilizando a Transformada Rápida de Fourier (FFT).

## Requisitos de Hardware
Microcontrolador STM32 (por exemplo, STM32F407Vetx)
Microfone
Cabo USB para conectar o microcontrolador ao computador

## Requisitos de Software
IDE de desenvolvimento STM32 (por exemplo, System Workbench)
Biblioteca USB (por exemplo, STM32 USB Library)
Python 3.x
Bibliotecas Python: tkinter, numpy, serial, matplotlib

## Configuração do Hardware
Conecte o microfone ao microcontrolador STM32 na porta PA0, seguindo as especificações do hardware utilizado.

## Configuração do Software
Clone este repositório para o seu computador:

bash
Copy code
git clone https://github.com/seu-usuario/nome-do-projeto.git
Copie o código em C e abra a sua IDE System Workbench ou STM32CubeIDE, cole o código e compile-o para o microcontrolador STM32. Certifique-se de configurar corretamente as bibliotecas USB e as configurações de comunicação.

Conecte o microcontrolador ao computador usando o cabo USB.

Instale as bibliotecas Python necessárias executando o seguinte comando:

## Execute o programa Python:
Abra o programa Python em sua IDE clique com o botão dereito do mouse clique em `run python` -> `run python file in terminal`.

No microcontrolador STM32, inicie a captura de áudio e envie os dados para o computador via USB.

O programa Python receberá os dados do microcontrolador e exibirá um gráfico do espectro de frequências calculado usando a FFT.

## Contribuição
Contribuições para a melhoria deste projeto são bem-vindas. Se você encontrar problemas ou tiver sugestões, por favor, abra uma issue neste repositório.

## Contato
Se você tiver alguma dúvida ou precisar entrar em contato, você pode me encontrar em vinicius.gonzaga@academico.ifpb.edu.br
