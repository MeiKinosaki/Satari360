# Satari360

Emulador de Atari ST para Xbox 360.

**Versão:** 0.8b  
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

## Situação da versão 0.8b
A CPU experimental inclui NOP, MOVEQ, MOVE.L imediato para Dn, ADDQ.L/SUBQ.L em Dn, alguns desvios e BSR/RTS. Foi adicionada a classe `Machine`, que combina barramento e CPU, aceita uma imagem ROM fornecida pelo chamador, reinicia a CPU a partir dos vetores e executa um orçamento limitado de instruções. Um teste de fumaça cobre essa integração com uma ROM sintética. A camada continua sendo apenas um esqueleto: mapa de memória Atari ST incompleto, sem Shifter, YM2149, MFP/ACIA, controladora de disquete ou integração Xbox 360. O workflow de host está configurado, mas sua execução e resultado ainda precisam ser confirmados.

## Próximas etapas
1. Completar o mapa de memória Atari ST, incluindo regiões de I/O e registradores de periféricos.
2. Integrar um núcleo Motorola 68000 com licença compatível.
3. Implementar periféricos, vídeo e áudio.
4. Adicionar carregamento de mídia e controles.
5. Configurar e validar a compilação no ambiente Xbox 360.
