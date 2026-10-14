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

## v0.3b — CPU Motorola 68000
- [ ] Selecionar/integrar um núcleo com licença compatível.
- [ ] Estado de registradores, reset e ciclo de execução.
- [ ] Exceções, interrupções e acesso ao barramento.

## v0.4b — periféricos básicos
- [ ] Shifter e modos gráficos.
- [ ] YM2149, MFP 68901 e ACIA.
- [ ] Temporização e interrupções.

## v0.5b — mídia e entrada
- [ ] Imagens .ST/.MSA.
- [ ] Teclado, joystick e mouse.

## v0.6b em diante — integração Xbox 360
- [ ] Camada de vídeo/áudio/input da plataforma.
- [ ] Toolchain homebrew e geração de default.xex.
- [ ] Testes de compatibilidade, desempenho e estabilidade.

> Os itens marcados como concluídos referem-se aos arquivos e testes implementados neste repositório. O teste precisa ser compilado e executado para ser considerado validado; a integração Xbox 360 não está concluída.
