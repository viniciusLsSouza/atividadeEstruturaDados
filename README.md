
## Funcionalidades do Programa

O programa oferece as seguintes funcionalidades através de um menu interativo:

1. Exibição da playlist pela ordem de cadastro.
2. Exibição da playlist ordenada pelo nome das músicas.
3. Inserção de novas músicas.
4. Remoção de uma música.
5. Busca por uma música.
6. Avançar para a próxima música.
7. Retornar à música anterior.
8. Sair do programa.

### Exibição da Playlist

- **Ordem de Cadastro**: Exibe as músicas na ordem em que foram adicionadas à playlist.
- **Ordenada pelo Nome das Músicas**: Exibe as músicas em ordem alfabética.

### Inserção de Novas Músicas

Permite inserir novas músicas na playlist. As novas músicas também são salvas no arquivo `musicas.txt`.

### Remoção de uma Música

Permite remover uma música específica da playlist. A remoção é refletida no arquivo `musicas.txt`.

### Busca por uma Música

Permite buscar uma música específica na playlist. Exibe o artista e o nome da música, se encontrada.

### Navegação entre as Músicas

- **Avançar**: Avança para a próxima música na playlist.
- **Retornar**: Retorna à música anterior na playlist.

## Compilação e Execução

### Compilação

Para compilar o programa, utilize um compilador de C como `gcc`. Execute o seguinte comando no terminal:

```bash
gcc -o playlist playlist.c
