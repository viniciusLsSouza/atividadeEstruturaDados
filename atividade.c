#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char artist[100];
    char song[100];
    struct Node* prev;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    Node* tail;
    Node* current;
} CircularDoublyLinkedList;

CircularDoublyLinkedList* createList() {
    CircularDoublyLinkedList* list = (CircularDoublyLinkedList*)malloc(sizeof(CircularDoublyLinkedList));
    list->head = NULL;
    list->tail = NULL;
    list->current = NULL;
    return list;
}

void append(CircularDoublyLinkedList* list, const char* artist, const char* song) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->artist, artist);
    strcpy(newNode->song, song);
    if (!list->head) {
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
        newNode->prev = newNode;
    } else {
        newNode->prev = list->tail;
        newNode->next = list->head;
        list->tail->next = newNode;
        list->head->prev = newNode;
        list->tail = newNode;
    }
}

void printList(CircularDoublyLinkedList* list) {
    if (!list->head) {
        printf("Playlist vazia.\n");
        return;
    }
    Node* temp = list->head;
    do {
        printf("Artista: %s, Música: %s\n", temp->artist, temp->song);
        temp = temp->next;
    } while (temp != list->head);
}

int compareSongs(const void* a, const void* b) {
    Node* nodeA = *(Node**)a;
    Node* nodeB = *(Node**)b;
    return strcmp(nodeA->song, nodeB->song);
}

void printListSorted(CircularDoublyLinkedList* list) {
    if (!list->head) {
        printf("Playlist vazia.\n");
        return;
    }
    int count = 0;
    Node* temp = list->head;
    do {
        count++;
        temp = temp->next;
    } while (temp != list->head);

    Node** nodes = (Node**)malloc(count * sizeof(Node*));
    temp = list->head;
    for (int i = 0; i < count; i++) {
        nodes[i] = temp;
        temp = temp->next;
    }

    qsort(nodes, count, sizeof(Node*), compareSongs);

    for (int i = 0; i < count; i++) {
        printf("Artista: %s, Música: %s\n", nodes[i]->artist, nodes[i]->song);
    }

    free(nodes);
}

void insertSong(CircularDoublyLinkedList* list, const char* artist, const char* song) {
    append(list, artist, song);
}

void removeSong(CircularDoublyLinkedList* list, const char* song) {
    if (!list->head) return;
    Node* temp = list->head;
    do {
        if (strcmp(temp->song, song) == 0) {
            if (temp->next == temp) {
                free(temp);
                list->head = NULL;
                list->tail = NULL;
                list->current = NULL;
            } else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                if (temp == list->head) list->head = temp->next;
                if (temp == list->tail) list->tail = temp->prev;
                if (temp == list->current) list->current = temp->next;
                free(temp);
            }
            return;
        }
        temp = temp->next;
    } while (temp != list->head);
}

Node* searchSong(CircularDoublyLinkedList* list, const char* song) {
    if (!list->head) return NULL;
    Node* temp = list->head;
    do {
        if (strcmp(temp->song, song) == 0) return temp;
        temp = temp->next;
    } while (temp != list->head);
    return NULL;
}

void nextSong(CircularDoublyLinkedList* list) {
    if (list->current) {
        list->current = list->current->next;
    }
}

void prevSong(CircularDoublyLinkedList* list) {
    if (list->current) {
        list->current = list->current->prev;
    }
}

void displayCurrentSong(CircularDoublyLinkedList* list) {
    if (list->current) {
        printf("Tocando agora: Artista: %s, Música: %s\n", list->current->artist, list->current->song);
    } else {
        printf("Nenhuma música está tocando no momento.\n");
    }
}

void loadFromFile(CircularDoublyLinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    char line[200];
    while (fgets(line, sizeof(line), file)) {
        char* token = strtok(line, ";");
        char artist[100], song[100];
        strcpy(artist, token);
        token = strtok(NULL, "\n");
        strcpy(song, token);
        append(list, artist, song);
    }
    fclose(file);
}

void updateFile(CircularDoublyLinkedList* list, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    if (!list->head) {
        fclose(file);
        return;
    }
    Node* temp = list->head;
    do {
        fprintf(file, "%s;%s\n", temp->artist, temp->song);
        temp = temp->next;
    } while (temp != list->head);
    fclose(file);
}

void menu(CircularDoublyLinkedList* list, const char* filename) {
    int choice;
    char artist[100], song[100];
    do {
        printf("\nMenu:\n");
        printf("1. Exibição da playlist pela ordem de cadastro\n");
        printf("2. Exibição da playlist ordenada pelo nome das músicas\n");
        printf("3. Inserção de novas músicas\n");
        printf("4. Remoção de uma música\n");
        printf("5. Busca por uma música\n");
        printf("6. Avançar para próxima música\n");
        printf("7. Retornar a música anterior\n");
        printf("8. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &choice);
        getchar();  

        switch (choice) {
            case 1:
                printList(list);
                break;
            case 2:
                printListSorted(list);
                break;
            case 3:
                printf("Digite o nome do artista: ");
                fgets(artist, sizeof(artist), stdin);
                artist[strcspn(artist, "\n")] = 0;  
                printf("Digite o nome da música: ");
                fgets(song, sizeof(song), stdin);
                song[strcspn(song, "\n")] = 0;  
                insertSong(list, artist, song);
                updateFile(list, filename);
                break;
            case 4:
                printf("Digite o nome da música a ser removida: ");
                fgets(song, sizeof(song), stdin);
                song[strcspn(song, "\n")] = 0;  
                removeSong(list, song);
                updateFile(list, filename);
                break;
            case 5:
                printf("Digite o nome da música a ser buscada: ");
                fgets(song, sizeof(song), stdin);
                song[strcspn(song, "\n")] = 0;  
                Node* found = searchSong(list, song);
                if (found) {
                    printf("Música encontrada: Artista: %s, Música: %s\n", found->artist, found->song);
                } else {
                    printf("Música não encontrada.\n");
                }
                break;
            case 6:
                nextSong(list);
                displayCurrentSong(list);
                break;
            case 7:
                prevSong(list);
                displayCurrentSong(list);
                break;
            case 8:
                printf("Saindo...\n");
                break;
            default:
                printf("Opção inválida!\n");
                break;
        }
    } while (choice != 8);
}

int main() {
    const char* filename = "musicas.txt";
    CircularDoublyLinkedList* playlist = createList();
    loadFromFile(playlist, filename);
    playlist->current = playlist->head;  // Iniciar a playlist com a primeira música
    menu(playlist, filename);
    return 0;
}
