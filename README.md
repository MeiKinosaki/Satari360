# Satari360

Emulador de Atari ST para Xbox 360.

**Versão:** 1.2b  
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
- Leitura inicial de imagens raw `.ST` (somente leitura; `.MSA` ainda não suportado)
- Camada de plataforma Xbox 360 e empacotamento `default.xex`

## Estrutura inicial
- `src/core/`: estado e núcleo da máquina
- `src/platform/xbox360/`: ponto de entrada da plataforma
- `tests/`: testes de fumaça no host
- `docs/ROADMAP.md`: etapas de desenvolvimento

## Situação da versão 1.2b
A CPU experimental inclui um conjunto muito limitado de instruções e a classe `Machine` combina CPU e barramento, aceita uma ROM fornecida pelo chamador e executa um orçamento limitado de instruções. Os módulos iniciais Shifter (`atari_video.*`) e PSG YM2149 (`ym2149.*`) implementam `BusDevice` e são registrados no `MemoryBus` da classe `Machine`. Também foram adicionados modelos de registradores para MFP 68901 (`mfp68901.*`) e ACIA (`acia.*`), ligados ao barramento e cobertos por verificações básicas em `machine_smoke.cpp`. Foi adicionado `DiskImage`, que aceita imagens ST raw de tamanho limitado, permite ler setores de 512 bytes e ejetar a imagem. O teste `disk_image_smoke.cpp` cobre carregamento, leitura, tamanho inválido e ejeção. Isso ainda não é uma controladora WD1772: não há suporte a `.MSA`, acesso pelo firmware, escrita, rotação, temporização ou integração com o barramento. MFP/ACIA continuam sendo latches de registradores; temporizadores, interrupções, protocolo serial, renderização de pixels e geração de áudio real não estão implementados. A compilação e os testes ainda precisam ser executados e confirmados; a toolchain Xbox 360 e `default.xex` seguem pendentes.

## Próximas etapas
1. Completar o mapa de memória Atari ST, incluindo regiões de I/O e registradores de periféricos.
2. Integrar um núcleo Motorola 68000 com licença compatível.
3. Implementar periféricos, vídeo e áudio.
4. Adicionar carregamento de mídia e controles.
5. Configurar e validar a compilação no ambiente Xbox 360.
