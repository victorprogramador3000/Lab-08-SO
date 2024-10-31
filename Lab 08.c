#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_PAGINA 256
#define NUM_FRAMES 64
#define NUM_PAGINAS 128

// Estrutura para um Frame na Memória Física
typedef struct {
    int ocupado;
    int id_pagina;
} Frame;

// Estrutura para uma Página na Memória Virtual
typedef struct {
    int id_frame;
} Pagina;

// Estrutura para a Tabela de Páginas
typedef struct {
    Pagina paginas[NUM_PAGINAS];
} TabelaPaginas;

// Estrutura para um Processo
typedef struct {
    int id_processo;
    int enderecos_virtuais[10]; // Exemplo de endereços virtuais para acesso
} Processo;

Frame memoria_fisica[NUM_FRAMES];
TabelaPaginas tabela_paginas;

void inicializarMemoriaFisica() {
    for (int i = 0; i < NUM_FRAMES; i++) {
        memoria_fisica[i].ocupado = 0;
        memoria_fisica[i].id_pagina = -1;
    }
}

void inicializarTabelaPaginas() {
    for (int i = 0; i < NUM_PAGINAS; i++) {
        tabela_paginas.paginas[i].id_frame = -1;
    }
}

int alocarPagina(int id_pagina) {
    for (int i = 0; i < NUM_FRAMES; i++) {
        if (!memoria_fisica[i].ocupado) {
            memoria_fisica[i].ocupado = 1;
            memoria_fisica[i].id_pagina = id_pagina;
            tabela_paginas.paginas[id_pagina].id_frame = i;
            return i;
        }
    }
    printf("Erro: Não há frames livres.\n");
    return -1;  // Nenhum frame livre
}

int traduzirEndereco(int endereco_virtual) {
    int num_pagina = endereco_virtual / TAMANHO_PAGINA;
    int offset = endereco_virtual % TAMANHO_PAGINA;

    if (tabela_paginas.paginas[num_pagina].id_frame == -1) {
        printf("Page fault: Página %d não está na memória.\n", num_pagina);
        return -1;
    }

    int id_frame = tabela_paginas.paginas[num_pagina].id_frame;
    int endereco_fisico = id_frame * TAMANHO_PAGINA + offset;
    return endereco_fisico;
}

int main() {
    inicializarMemoriaFisica();
    inicializarTabelaPaginas();

    // Exemplo de alocação e tradução
    alocarPagina(1);
    alocarPagina(2);

    int endereco_virtual = 300;
    int endereco_fisico = traduzirEndereco(endereco_virtual);

    if (endereco_fisico != -1) {
        printf("Endereço físico correspondente: %d\n", endereco_fisico);
    }

    return 0;
}
