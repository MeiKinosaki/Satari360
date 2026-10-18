# Satari360

Emulador de Atari ST para Xbox 360.

**Versão:** 0.9b  
**Estado:** estrutura inicial de desenvolvimento; ainda não é um emulador funcional.

## Objetivo
Desenvolver uma aplicação para Xbox 360 capaz de emular a família Atari ST, com foco inicial em arquitetura modular, testes e compatibilidade com uma toolchain homebrew adequada.

## Componentes planejados
- CPU Motorola 68000
- RAM, ROM/TOS e mapa de endereços
- Vídeo Atari ST (shifter e modos gráficos)
- MFP 68901, ACIA/teclado e temporizadores
- Áudio YM2149
- Joystick, teclado e mouse
- Carregamento de imagens de disquete .ST/.MSA
- Camada de plataforma Xbox 360 e empacotamento `default.xex`

## Estrutura inicial
- `src/core/`: estado e núcleo da máquina
- `src/platform/xbox360/`: ponto de entrada da plataforma
- `tests/`: testes de fumaça no host
- `docs/ROADMAP.md`: etapas de desenvolvimento

## Situação da versão 0.9b
A CPU experimental inclui um conjunto muito limitado de instruções e a classe `Machine` combina CPU e barramento, aceita uma ROM fornecida pelo chamador e executa um orçamento limitado de instruções. Foram adicionados modelos iniciais de registradores para o Shifter (`atari_video.*`) e um latch de registradores do PSG YM2149 (`ym2149.*`), com teste de fumaça `video_psg_smoke.cpp` e integração ao CMake. Esses módulos não geram imagem nem som reais e ainda não estão ligados ao barramento da máquina. O mapa de memória Atari ST permanece incompleto; MFP/ACIA, WD1772, controles, toolchain Xbox 360 e `default.xex` seguem pendentes. A execução do workflow e dos testes ainda precisa ser confirmada.

## Próximas etapas
1. Completar o mapa de memória Atari ST, incluindo regiões de I/O e registradores de periféricos.
2. Integrar um núcleo Motorola 68000 com licença compatível.
3. Implementar periféricos, vídeo e áudio.
4. Adicionar carregamento de mídia e controles.
5. Configurar e validar a compilação no ambiente Xbox 360.
