# aed_t2

# Objetivos

Usar grafos para mapear a cidade do porto e respetiva rede STCP.

Dados dois locais, indicar o “melhor” percurso para ir de um local para o outro, usando para isso a
rede dos STCP.

Para obter pontuação máxima, o seu programa deverá ser capaz de implementar diferentes versões do que
significa um “local”, do que significa “melhor” percurso, e de como pode uma pessoa mudar de linha:

- “Local” - tanto pode ser indicada diretamente uma paragem, como um localização (i.e., as coordenadas),
onde pode ver as paragens que estejam perto dessa posição.
- “Melhor” percurso - um utilizador pode querer o percurso que: passa por menos paragens; percorre menor
distância; implica menos mudanças de autocarro (de linha); fica mais barato (passa por menos zonas), etc.
- “Mudar” de autocarro – para além de mudar de autocarro numa paragem, deve também ser possível
caminhar um pouco para uma outra paragem “vizinha” (que esteja a menos do que uma certa distância)
