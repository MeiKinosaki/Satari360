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
