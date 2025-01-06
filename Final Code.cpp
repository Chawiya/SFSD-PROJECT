
/*
 * File Management System Implementation
 * This program implements a file management system with block allocation and record management
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Constants
#define MAX_FILE_NAME 50
#define Fact_Blockage 10
#define MAX_BLOCKS 100

// Structure definitions
typedef struct {
    int id;
    char data[100];
    int activ;     // Active status (1=active, 0=deleted)
} Record;

// Memory block structure - represents a block in secondary memory
typedef struct MemoryBlock {
    int id;
    int is_occupied;
    char file_name[MAX_FILE_NAME];
    int record_count;
    Record r[Fact_Blockage];
    int next;
} MemoryBlock;

typedef struct {
    char *file_name;
    int adresse_premier;
    int record_count;
    int bloc_count;
    int mode;
    int etat;
} meta;

// Global variables
meta liste_metadonnes[100];
int index_metadonnes = 0;
MemoryBlock *memory;
int total_blocks;
int block_size;

// Validation functions
int validate_filename(const char *filename) {
    if (!filename) {
        printf("Nom de fichier invalide!\n");
        return 0;
    }
    if (strlen(filename) >= MAX_FILE_NAME) {
        printf("Nom de fichier trop long (max %d caractères)\n", MAX_FILE_NAME);
        return 0;
    }
    return 1;
}

int validate_record_count(int count) {
    if (count <= 0) {
        printf("Le nombre d'enregistrements doit être positif\n");
        return 0;
    }
    if (count > MAX_BLOCKS * Fact_Blockage) {
        printf("Nombre d'enregistrements trop grand pour la mémoire disponible\n");
        return 0;
    }
    return 1;
}

int validate_mode(int mode) {
    if (mode != 0 && mode != 1) {
        printf("Mode invalide! Utilisez 0 pour chaîné ou 1 pour contigu\n");
        return 0;
    }
    return 1;
}
// fonction pour afficher la liste des mÃ©tadonnÃ©es
void afficher_metadonnes() {
	int i;
    printf("liste des mÃ©tadonnÃ©es : \n");
    for ( i = 0; i < index_metadonnes; i++) {
        if (liste_metadonnes[i].etat == 1) {
            printf("fichier : %s \n", liste_metadonnes[i].file_name);
            printf("adress premier bloc : %d\n", liste_metadonnes[i].adresse_premier);
            printf("record count : %d\n", liste_metadonnes[i].record_count);
            printf("bloc count : %d\n", liste_metadonnes[i].bloc_count);
            if (liste_metadonnes[i].mode == 0) {
                printf("mode : chainÃ© \n");
            }else {
                printf("mode : contigue \n");
            }
        }
    }
}



// Memory initialization
void initialize_memory() {
	int i ;
    printf("Entrez le nombre total de blocs : ");
    scanf("%d", &total_blocks);
    
    if (total_blocks <= 0 || total_blocks > MAX_BLOCKS) {
        printf("Nombre de blocs invalide. Utilisation de la valeur par défaut: %d\n", MAX_BLOCKS);
        total_blocks = MAX_BLOCKS;
    }

    printf("Entrez la taille d'un bloc (en octets) : ");
    scanf("%d", &block_size);
    
    if (block_size <= 0) {
        printf("Taille de bloc invalide. Utilisation de la valeur par défaut: 1024\n");
        block_size = 1024;
    }

    memory = (MemoryBlock *)malloc(total_blocks * sizeof(MemoryBlock));
    if (!memory) {
        printf("Erreur d'allocation mémoire!\n");
        exit(1);
    }

    for ( i = 0; i < total_blocks; i++) {
        memory[i].id = i;
        memory[i].is_occupied = 0;
        strcpy(memory[i].file_name, "");
        memory[i].record_count = 0;
        memory[i].next = -1;
    }

    printf("\nMémoire initialisée avec %d blocs de taille %d octets.\n", total_blocks, block_size);
}

// Metadata management functions
int fichier_existe(const char *file_name) {
	int i;
    for ( i = 0; i < index_metadonnes; i++) {
        if (liste_metadonnes[i].etat == 1 && 
            strcmp(liste_metadonnes[i].file_name, file_name) == 0) {
            return i;
        }
    }
    return -1;
}

void ajouter_metadonne(const char *file_name, int adr_pr, int record_count, int mode) {
    liste_metadonnes[index_metadonnes].file_name = strdup(file_name);
    liste_metadonnes[index_metadonnes].adresse_premier = adr_pr;
    liste_metadonnes[index_metadonnes].record_count = record_count;
    liste_metadonnes[index_metadonnes].bloc_count = (record_count + Fact_Blockage - 1) / Fact_Blockage;
    liste_metadonnes[index_metadonnes].mode = mode;
    liste_metadonnes[index_metadonnes].etat = 1;
    index_metadonnes++;
}

int read_metadonne(const char *file_name, int type) {
    int idx = fichier_existe(file_name);
    if (idx == -1) return -1;
    
    switch(type) {
        case 1: return liste_metadonnes[idx].adresse_premier;
        case 2: return liste_metadonnes[idx].record_count;
        case 3: return liste_metadonnes[idx].bloc_count;
        case 4: return liste_metadonnes[idx].mode;
        default: return -1;
    }
}

void modifier_metadonne(const char *file_name, int type, int value) {
    int idx = fichier_existe(file_name);
    if (idx == -1) return;
    
    switch(type) {
        case 1: liste_metadonnes[idx].adresse_premier = value; break;
        case 2: liste_metadonnes[idx].record_count = value; break;
        case 3: liste_metadonnes[idx].bloc_count = value; break;
        case 4: liste_metadonnes[idx].mode = value; break;
    }
}

void supp_metadonnes(const char *file_name) {
    int idx = fichier_existe(file_name);
    if (idx != -1) {
        free(liste_metadonnes[idx].file_name);
        liste_metadonnes[idx].etat = 0;
    }
}

// Block allocation functions
int Contigue(MemoryBlock *memory, int fileSize) {
    int Cmp = 0;
    int j = -1;
    int i;

    for ( i = 0; i < total_blocks; i++) {
        if (memory[i].is_occupied == 0) {
            if (j == -1) {
                j = i;
                memory[i].is_occupied = 1;
            }
            Cmp++;
            if (Cmp == fileSize) break;
        } else {
            j = -1;
            Cmp = 0;
        }
    }

    if (Cmp < fileSize) {
        printf("Espace contigu insuffisant\n");
        return -1;
    }

    for (i = j; i < j + fileSize - 1; i++) {
        memory[i].is_occupied = 1;
    }
    printf("Allocation contiguë réussie, début au bloc %d.\n", j);
    return j;
}

int Chained(MemoryBlock *memory, int fileSize) {
    int Cmp = 0;
    int j = -1;
    int k = -1;
    int i;

    for ( i = 0; i < total_blocks; i++) {
        if (memory[i].is_occupied == 0) {
            if (j == -1) {
                j = i;
                memory[i].is_occupied = 1;
            }

            if (k != -1) {
                memory[k].next = i;
            }
            k = i;
            Cmp++;

            if (Cmp == fileSize) {
                memory[i].next = -1;
                break;
            }
        }
    }

    if (Cmp < fileSize) {
        printf("Blocs insuffisants pour allocation chaînée\n");
        return -1;
    }

    printf("Allocation chaînée réussie, début au bloc %d.\n", j);
    return j;
}

void display_memory_state() {
	int i;
    printf("\nÉtat actuel de la mémoire secondaire :\n");
    for ( i = 0; i < total_blocks; i++) {
        if (memory[i].is_occupied) {
            printf("\033[1;31m");
            printf("Bloc %d : Occupé | Fichier : %s | Enregistrements : %d\n",
                   memory[i].id, memory[i].file_name, memory[i].record_count);
            printf("\033[0m");
        } else {
            printf("\033[1;32m");
            printf("Bloc %d : Libre\n", memory[i].id);
            printf("\033[0m");
        }
    }
}

// Record management functions
void crier_fichier(char *file_name, int record_count, int mode) {
	int i;
	int j;
    if (!validate_filename(file_name) || !validate_record_count(record_count) || !validate_mode(mode)) {
        return;
    }

    if (fichier_existe(file_name) >= 0) {
        printf("Erreur : Un fichier avec ce nom existe déjà.\n");
        return;
    }

    int bloc_count = (record_count + Fact_Blockage - 1) / Fact_Blockage;
    int adr_pr = (mode == 1) ? Contigue(memory, bloc_count) : Chained(memory, bloc_count);

    if (adr_pr == -1) {
        printf("Erreur d'allocation des blocs.\n");
        return;
    }

    ajouter_metadonne(file_name, adr_pr, record_count, mode);

    if (mode == 1) {
        for ( i = adr_pr; i < adr_pr + bloc_count; i++) {
            strcpy(memory[i].file_name, file_name);
            for ( j = 0; j < Fact_Blockage && record_count > 0; j++) {
                memory[i].r[j].id = (i - adr_pr) * Fact_Blockage + j + 1;
                memory[i].r[j].activ = 1;
                printf("Entrez les données de l'enregistrement %d du bloc %d : ", 
                       memory[i].r[j].id, i);
                scanf(" %s", memory[i].r[j].data);
                memory[i].record_count++;
                record_count--;
            }
        }
    } else {
        for ( i = adr_pr; i != -1; i = memory[i].next) {
            strcpy(memory[i].file_name, file_name);
            for ( j = 0; j < Fact_Blockage && record_count > 0; j++) {
                memory[i].r[j].id = memory[i].record_count + 1;
                memory[i].r[j].activ = 1;
                printf("Entrez les données de l'enregistrement %d du bloc %d : ", 
                       memory[i].r[j].id, i);
                scanf(" %s", memory[i].r[j].data);
                memory[i].record_count++;
                record_count--;
            }
        }
    }

    printf("Fichier '%s' créé avec succès.\n", file_name);
}

// Record operations and search functions
Record* searchRecord(const char *file, int id) {
	int i;
	int j;
    int adr_pr = read_metadonne(file, 1);
    int bloc_count = read_metadonne(file, 3);
    int mode = read_metadonne(file, 4);

    if (adr_pr == -1 || bloc_count <= 0) {
        printf("Erreur : Métadonnées introuvables ou fichier vide.\n");
        return NULL;
    }

    printf("Recherche dans le fichier '%s', ID = %d, Mode = %d\n", file, id, mode);

    if (mode == 1) {
        for ( i = adr_pr; i < adr_pr + bloc_count; i++) {
            for ( j = 0; j < memory[i].record_count; j++) {
                Record *r = &memory[i].r[j];
                if (r->id == id && r->activ == 1) {
                    return r;
                }
            }
        }
    } else {
        for (i = adr_pr; i != -1; i = memory[i].next) {
            for ( j = 0; j < memory[i].record_count; j++) {
                Record *r = &memory[i].r[j];
                if (r->id == id && r->activ == 1) {
                    return r;
                }
            }
        }
    }
    return NULL;
}

void insertRecord(const char *file_name, int id, const char *data) {
    int adr_pr = read_metadonne(file_name, 1);
    int mode = read_metadonne(file_name, 4);
    
    if (adr_pr == -1) {
        printf("Fichier non trouvé\n");
        return;
    }
    
    if (mode == 1) {
        int block = adr_pr + (id - 1) / Fact_Blockage;
        int pos = (id - 1) % Fact_Blockage;
        memory[block].r[pos].id = id;
        strcpy(memory[block].r[pos].data, data);
        memory[block].r[pos].activ = 1;
    } else {
        int current = adr_pr;
        while (current != -1) {
            if (memory[current].record_count < Fact_Blockage) {
                int pos = memory[current].record_count;
                memory[current].r[pos].id = id;
                strcpy(memory[current].r[pos].data, data);
                memory[current].r[pos].activ = 1;
                memory[current].record_count++;
                break;
            }
            current = memory[current].next;
        }
    }
}

// Record deletion functions
void deleteRecordLogical(const char *file, int id) {
    Record *record = searchRecord(file, id);
    if (record != NULL) {
        record->activ = 0;
        printf("Enregistrement supprimé logiquement (ID: %d).\n", id);
    } else {
        printf("Erreur : Enregistrement non trouvé.\n");
    }
}

// Physically delete a record by ID
void deleteRecordPhysical(const char *file, int id) {
	int i, j, k;
    int bloc = read_metadonne(file, 3);
    for ( i = 0; i < bloc; i++) {
        MemoryBlock *block = &memory[i];
        for ( j = 0; j < block->record_count; j++) {
            if (block->r[j].id == id) {
                // Shift records to remove the deleted one
                for ( k = j; k < block->record_count - 1; k++) {
                    block->r[k] = block->r[k + 1];
                }
                block->record_count--;
                printf("Record physically deleted (ID: %d).\n", id);
                return;
            }
        }
    }
    printf("Error: Record not found.\n");
}

// Memory optimization functions
void compactMemory(MemoryBlock *memory) {
    int writeIndex = 0;
    int readIndex;
    int i;
    for (readIndex = 0; readIndex < total_blocks; readIndex++) {
        if (memory[readIndex].is_occupied) {
            if (writeIndex != readIndex) {
                memory[writeIndex] = memory[readIndex];
                memory[readIndex].is_occupied = 0;
                memory[readIndex].next = -1;
            }
            writeIndex++;
        }
    }

    for ( i = writeIndex; i < total_blocks; i++) {
        memory[i].is_occupied = 0;
        memory[i].next = -1;
    }
    
    printf("Compactage de la mémoire terminé.\n");
}

// Memory defragmentation and file management
void defragmentMemory() {
    int writeIndex = 0;
    int readIndex;
    for ( readIndex = 0; readIndex < total_blocks; readIndex++) {
        int adr_pr = read_metadonne(memory[readIndex].file_name, 1);
        if (memory[readIndex].is_occupied) {
            if (writeIndex != readIndex) {
                memory[writeIndex].is_occupied = 1;
                memory[writeIndex] = memory[readIndex];
                memory[readIndex].is_occupied = 0;
                if (writeIndex < adr_pr) {
                    modifier_metadonne(memory[writeIndex].file_name, 2, writeIndex);
                }
            }
            writeIndex++;
        }
    }
    
    printf("\nDéfragmentation de la mémoire terminée.\n");
    display_memory_state();
}

void supprimer_fichier(const char *file_name) {
	int i;
    int adr_pr = read_metadonne(file_name, 1);
    int bloc_count = read_metadonne(file_name, 3);
    int mode = read_metadonne(file_name, 4);

    if (adr_pr == -1 || bloc_count <= 0) {
        printf("Erreur : fichier '%s' introuvable ou déjà supprimé.\n", file_name);
        return;
    }

    if (mode == 1) {
        for ( i = adr_pr; i < adr_pr + bloc_count; i++) {
            memory[i].is_occupied = 0;
            strcpy(memory[i].file_name, "");
            memory[i].record_count = 0;
        }
    } else {
        int current = adr_pr;
        while (current != -1) {
            int next = memory[current].next;
            memory[current].is_occupied = 0;
            strcpy(memory[current].file_name, "");
            memory[current].record_count = 0;
            memory[current].next = -1;
            current = next;
        }
    }

    supp_metadonnes(file_name);
    printf("Fichier '%s' supprimé avec succès.\n", file_name);
}

void clear_memory() {
	int i;
	int j;
    for ( i = 0; i < total_blocks; i++) {
        memory[i].is_occupied = 0;
        strcpy(memory[i].file_name, "");
        memory[i].record_count = 0;
        memory[i].next = -1;
        for ( j = 0; j < Fact_Blockage; j++) {
            memory[i].r[j].activ = 0;
            strcpy(memory[i].r[j].data, "");
        }
    }
    printf("\nMémoire vidée avec succès.\n");
}

// Menu functions
void afficher_menu() {
    printf("\n=================== MENU ===================\n");
    printf("1. Initialiser la mémoire\n");
    printf("2. Afficher l'état de la mémoire\n");
    printf("3. Vider la mémoire\n");
    printf("4. Créer un fichier\n");
    printf("5. Insérer un enregistrement\n");
    printf("6. Chercher un enregistrement\n");
    printf("7. Supprimer un enregistrement (logique)\n");
    printf("8. Supprimer un enregistrement (physique)\n");
    printf("9. Compactage de la mémoire\n");
    printf("10. Défragmentation de la mémoire\n");
    printf("11. Afficher les métadonnées\n");
    printf("12. Supprimer un fichier\n");
    printf("0. Quitter\n");
    printf("===========================================\n");
    printf("Choisissez une option : ");
}

void menu() {
    int choix, id, record_count, mode;
    char file_name[MAX_FILE_NAME];
    char data[100];
    Record *record;

    do {
        afficher_menu();
        scanf("%d", &choix);
        
        switch (choix) {
            case 1:
                initialize_memory();
                break;
            case 2:
                display_memory_state();
                break;
            case 3:
                clear_memory();
                break;
            case 4:
                printf("Nom du fichier : ");
                scanf("%s", file_name);
                printf("Nombre d'enregistrements : ");
                scanf("%d", &record_count);
                printf("Mode (1 = contigu, 0 = chaîné) : ");
                scanf("%d", &mode);
                crier_fichier(file_name, record_count, mode);
                break;
            case 5:
                printf("Nom du fichier : ");
                scanf("%s", file_name);
                printf("ID de l'enregistrement : ");
                scanf("%d", &id);
                printf("Données : ");
                scanf("%s", data);
                insertRecord(file_name, id, data);
                break;
            case 6:
                printf("Nom du fichier : ");
                scanf("%s", file_name);
                printf("ID de l'enregistrement : ");
                scanf("%d", &id);
                record = searchRecord(file_name, id);
                if (record) {
                    printf("Enregistrement trouvé : ID = %d, Data = %s\n", 
                           record->id, record->data);
                }
                break;
            case 7:
                printf("Nom du fichier : ");
                scanf("%s", file_name);
                printf("ID de l'enregistrement : ");
                scanf("%d", &id);
                deleteRecordLogical(file_name, id);
                break;
            case 8:
                printf("Nom du fichier : ");
                scanf("%s", file_name);
                printf("ID de l'enregistrement : ");
                scanf("%d", &id);
                deleteRecordPhysical(file_name, id);
                break;
            case 9:
                compactMemory(memory);
                break;
            case 10:
                defragmentMemory();
                break;
            case 11:
                afficher_metadonnes();
                break;
            case 12:
                printf("Nom du fichier à supprimer : ");
                scanf("%s", file_name);
                supprimer_fichier(file_name);
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Option invalide!\n");
        }
    } while (choix != 0);
}

int main() {
    menu();
    return 0;
}
