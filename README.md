# Satari360

Emulador de Atari ST para Xbox 360.

**Versão:** 0.4b  
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

## Situação da versão 0.4b
A CPU experimental agora reconhece NOP, MOVEQ, RTS, BRA/Bcc com deslocamento curto ou extensão de 16 bits e BSR, com avaliação inicial de condições usando as flags N/Z/V/C. O teste de fumaça cobre alguns desses caminhos. O conjunto de instruções continua muito incompleto; exceções e temporização reais ainda não estão implementadas. Os testes foram escritos, mas não executados neste ambiente. Periféricos, vídeo, áudio, integração Xbox 360 e `default.xex` continuam pendentes.

## Próximas etapas
1. Completar o mapa de memória Atari ST, incluindo regiões de I/O e registradores de periféricos.
2. Integrar um núcleo Motorola 68000 com licença compatível.
3. Implementar periféricos, vídeo e áudio.
4. Adicionar carregamento de mídia e controles.
5. Configurar e validar a compilação no ambiente Xbox 360.
