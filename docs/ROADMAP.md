# Satari360 — roteiro de desenvolvimento

## v0.1b — estrutura e documentação
- [x] Identidade do projeto e escopo inicial.
- [x] Documentação do objetivo e dos subsistemas.
- [ ] Build de destino Xbox 360 validado.

## v0.2b — barramento de memória inicial
- [x] RAM configurável no host.
- [x] Acessos de 8, 16 e 32 bits em big-endian.
- [x] Região inicial de ROM TOS a partir de 0xE00000, somente leitura.
- [x] Teste de fumaça para RAM, endianness e ROM.
- [ ] Integrar regiões de I/O e registradores de vídeo.
- [ ] Validar o comportamento com uma ROM TOS legalmente obtida.
- [ ] Executar o teste no ambiente de build-alvo.

## v0.3b — CPU Motorola 68000 (esqueleto inicial)
- [x] Estado inicial dos registradores D0-D7/A0-A7 e SR.
- [x] Vetores de reset lidos pelo barramento.
- [x] Instruções NOP, MOVEQ, BRA de deslocamento curto e RTS (implementação limitada).
- [x] Parada explícita ao encontrar opcode ainda não suportado.
- [x] Teste de fumaça integrado ao CMake.
- [ ] Validar compilação e executar testes no host.
- [ ] Integrar um núcleo 68000 completo, com licença compatível.
- [ ] Implementar exceções, interrupções e conjunto de instruções completo.

## v0.4b — expansão experimental da CPU 68000
- [x] BRA/Bcc com deslocamento curto e extensão de 16 bits.
- [x] BSR com salvamento do PC de retorno na pilha.
- [x] Avaliação inicial das condições de branch por flags N/Z/V/C.
- [x] Testes de fumaça para alguns fluxos de execução.
- [ ] Executar os testes e corrigir eventuais falhas.
- [ ] Completar instruções, exceções e precisão de temporização.
- [ ] Iniciar shifter, modos gráficos, YM2149, MFP 68901 e ACIA.

## v0.5b — validação automatizada inicial
- [x] Workflow GitHub Actions para configurar, compilar e executar testes no host.
- [x] Testes de fumaça expandidos para branches e chamadas/retornos.
- [ ] Confirmar resultado do workflow após sua execução no GitHub.
- [ ] Corrigir qualquer falha de compilação ou teste antes de avançar.

## v0.6b — expansão experimental da CPU
- [x] Adicionar decodificação inicial de MOVE.L com operando imediato para registrador Dn.
- [x] Ampliar o teste de fumaça para verificar a leitura do imediato de 32 bits.
- [x] Manter testes de desvios curtos/estendidos, BSR e RTS.
- [ ] Executar o workflow e validar os testes no host.
- [ ] Corrigir semântica de instruções e flags com testes de referência.
- [ ] Continuar expansão gradual do conjunto de instruções 68000.

## v0.7b — operações rápidas de registrador
- [x] Implementar ADDQ.L imediato para Dn.
- [x] Implementar SUBQ.L imediato para Dn.
- [x] Atualizar flags N/Z/V/C de forma inicial para essas operações.
- [x] Ampliar testes para verificar resultados e fluxo de execução.
- [x] Corrigir expectativa de PC no teste de BPL não tomado.
- [ ] Executar compilação e CTest no host e revisar os resultados.
- [ ] Adicionar testes de limites, overflow, carry e zero antes de considerar a semântica validada.

## v0.5b — mídia e entrada
- [ ] Imagens .ST/.MSA.
- [ ] Teclado, joystick e mouse.

## v0.6b em diante — integração Xbox 360
- [ ] Camada de vídeo/áudio/input da plataforma.
- [ ] Toolchain homebrew e geração de default.xex.
- [ ] Testes de compatibilidade, desempenho e estabilidade.

> Os itens marcados como concluídos referem-se aos arquivos e testes implementados neste repositório. O teste precisa ser compilado e executado para ser considerado validado; a integração Xbox 360 não está concluída.


## v0.8b — integração inicial da máquina
- [x] Criar classe `Machine` que possui barramento e CPU.
- [x] Adicionar interface para carregar uma ROM fornecida pelo chamador.
- [x] Reiniciar a CPU a partir dos vetores lidos no barramento.
- [x] Adicionar execução limitada por orçamento de instruções.
- [x] Adicionar teste de fumaça com ROM sintética.
- [x] Documentar arquitetura e limitações em `docs/ARCHITECTURE.md`.
- [ ] Compilar e executar os testes no host e corrigir falhas.
- [ ] Modelar o mapa de memória real do Atari ST e I/O mapeado.
- [ ] Implementar periféricos e vídeo/áudio antes de alegar compatibilidade com jogos.
- [ ] Validar separadamente a toolchain e o executável Xbox 360.

## v0.9b — primeiros módulos de vídeo e som
- [x] Criar modelo de registradores do Shifter em `atari_video.*`.
- [x] Criar latch de registradores YM2149 em `ym2149.*`.
- [x] Adicionar teste de fumaça para registradores de vídeo/PSG.
- [x] Integrar os módulos ao CMake.
- [ ] Confirmar compilação e execução dos testes no host.
- [ ] Ligar registradores de hardware ao barramento de memória da máquina.
- [ ] Implementar fetch de pixels/timing de vídeo e síntese de áudio real.
- [ ] Continuar com MFP/ACIA, teclado/joystick e controladora WD1772.


## v1.0b — barramento de dispositivos
- [x] Criar interface comum `BusDevice` para dispositivos de I/O mapeado.
- [x] Encaminhar leituras e escritas de 8 bits para dispositivos registrados.
- [x] Integrar Shifter e PSG ao barramento da máquina.
- [x] Corrigir o tipo do endereço-base do Shifter para 32 bits.

## v1.1b — registradores iniciais MFP/ACIA
- [x] Criar latch de registradores do MFP 68901.
- [x] Criar latches ACIA para portas de teclado e MIDI.
- [x] Registrar MFP/ACIA no barramento e incluí-los no CMake.
- [x] Ampliar teste de máquina para acessos mapeados de vídeo, PSG, MFP e ACIA.
- [ ] Executar compilação e todos os testes em CI; corrigir eventuais falhas.
- [ ] Implementar semântica real de timers, interrupções, status e dados de ACIA.
- [ ] Integrar controladora de disquetes WD1772 e mídia `.ST`/`.MSA`.
- [ ] Implementar renderização Shifter e síntese YM2149.
- [ ] Preparar e validar toolchain e entrada para Xbox 360.


## v1.2b — leitor inicial de imagem de disquete ST
- [x] Criar `DiskImage` para carregar imagem ST raw fornecida em memória.
- [x] Limitar o tamanho e exigir que a imagem seja múltipla de 512 bytes.
- [x] Implementar leitura de setores de 512 bytes, somente leitura.
- [x] Implementar ejeção e preservação da imagem atual quando uma nova imagem inválida é recusada.
- [x] Adicionar `disk_image_smoke.cpp` e integrar fonte/teste ao CMake.
- [ ] Executar compilação e todos os testes CTest em CI e registrar o resultado.
- [ ] Implementar parser `.MSA` e validar imagens reais de forma segura.
- [ ] Integrar leitura de setores com uma controladora WD1772 realista.
- [ ] Ligar CPU, mapa de memória e periféricos ao ciclo de execução da máquina.
- [ ] Continuar com temporização do MFP/ACIA, vídeo Shifter e áudio YM2149.
- [ ] Construir e validar o alvo Xbox 360 com toolchain adequada; gerar `default.xex` apenas após build real.


## v1.3b — decodificação MSA inicial
- [x] Adicionar interface `load_msa` e carregamento por vetor de bytes.
- [x] Validar magic, geometria, limites de trilha e tamanho máximo da imagem.
- [x] Decodificar trilhas MSA sem compressão e trilhas com marcador RLE `E5 E5`.
- [x] Rejeitar imagens truncadas/malformadas sem substituir a mídia já carregada.
- [x] Adicionar casos de teste para MSA simples, RLE e cabeçalho inválido.
- [ ] Executar CMake/CTest e validar os casos em CI.
- [ ] Adicionar testes de fuzz e limites de entrada para o parser.
- [ ] Ligar `DiskImage` a uma controladora WD1772; o parser sozinho não executa jogos.
- [ ] Continuar implementação precisa de CPU, mapa de memória, temporização e periféricos.
- [ ] Construir e validar separadamente o alvo Xbox 360 e o `default.xex`.


## Lote paralelo — controlador de disquete experimental
- [x] Criar `FloppyController` como dispositivo mapeado no barramento.
- [x] Adicionar montagem/ejeção para imagens ST e MSA já decodificadas.
- [x] Implementar comando experimental de leitura de setor em buffer de 512 bytes.
- [x] Adicionar teste de fumaça para montagem, leitura e erro de setor inválido.
- [x] Integrar fonte e teste ao CMake.
- [ ] Confirmar build e execução de todos os testes no CI.
- [ ] Substituir registradores simplificados pelo protocolo real WD1772/Glue logic Atari ST.
- [ ] Corrigir geometria para faces, setores por trilha e formatos variados.
- [ ] Integrar a controladora ao ciclo da máquina e ao firmware TOS.
