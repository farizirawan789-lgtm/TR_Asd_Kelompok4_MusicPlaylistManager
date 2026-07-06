#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lagu {
    char judul[100];
    char penyanyi[100];
    int durasi;
    struct Lagu *next;
};

typedef struct Lagu Lagu;

Lagu *head = NULL;

// Tambah Lagu
void tambahLagu() {
    Lagu *baru = (Lagu*)malloc(sizeof(Lagu));

    printf("\n=== Tambah Lagu ===\n");
    printf("Judul Lagu    : ");
    getchar();
    fgets(baru->judul, sizeof(baru->judul), stdin);
    baru->judul[strcspn(baru->judul, "\n")] = 0;

    printf("Nama Penyanyi : ");
    fgets(baru->penyanyi, sizeof(baru->penyanyi), stdin);
    baru->penyanyi[strcspn(baru->penyanyi, "\n")] = 0;

    printf("Durasi (menit): ");
    scanf("%d", &baru->durasi);

    baru->next = NULL;

    if(head == NULL){
        head = baru;
    } else {
        Lagu *temp = head;
        while(temp->next != NULL){
            temp = temp->next;
        }
        temp->next = baru;
    }

    printf("\nLagu berhasil ditambahkan!\n");
}

// Tampilkan Playlist
void tampilPlaylist() {
    Lagu *temp = head;

    if(head == NULL){
        printf("\nPlaylist masih kosong!\n");
        return;
    }

    printf("\n===== PLAYLIST =====\n");

    int no = 1;
    while(temp != NULL){
        printf("%d. %s\n", no++, temp->judul);
        printf("   Penyanyi : %s\n", temp->penyanyi);
        printf("   Durasi   : %d menit\n\n", temp->durasi);
        temp = temp->next;
    }
}

// Cari Lagu
void cariLagu() {
    char cari[100];

    printf("\nMasukkan Judul Lagu: ");
    getchar();
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    Lagu *temp = head;

    while(temp != NULL){
        if(strcmp(temp->judul, cari) == 0){
            printf("\nLagu ditemukan!\n");
            printf("Judul    : %s\n", temp->judul);
            printf("Penyanyi : %s\n", temp->penyanyi);
            printf("Durasi   : %d menit\n", temp->durasi);
            return;
        }
        temp = temp->next;
    }

    printf("\nLagu tidak ditemukan.\n");
}

// Hapus Lagu
void hapusLagu() {
    char hapus[100];

    printf("\nMasukkan Judul Lagu yang ingin dihapus: ");
    getchar();
    fgets(hapus, sizeof(hapus), stdin);
    hapus[strcspn(hapus, "\n")] = 0;

    Lagu *temp = head;
    Lagu *prev = NULL;

    while(temp != NULL && strcmp(temp->judul, hapus) != 0){
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        printf("\nLagu tidak ditemukan.\n");
        return;
    }

    if(prev == NULL){
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);

    printf("\nLagu berhasil dihapus.\n");
}

int main() {

    int pilih;

    do{
        printf("\n=============================\n");
        printf("     MUSIC PLAYLIST MANAGER\n");
        printf("=============================\n");
        printf("1. Tambah Lagu\n");
        printf("2. Tampilkan Playlist\n");
        printf("3. Cari Lagu\n");
        printf("4. Hapus Lagu\n");
        printf("5. Keluar\n");
        printf("=============================\n");
        printf("Pilih Menu : ");
        scanf("%d",&pilih);

        switch(pilih){

        case 1:
            tambahLagu();
            break;

        case 2:
            tampilPlaylist();
            break;

        case 3:
            cariLagu();
            break;

        case 4:
            hapusLagu();
            break;

        case 5:
            printf("\nTerima kasih telah menggunakan Music Playlist Manager.\n");
            break;

        default:
            printf("\nMenu tidak tersedia!\n");
        }

    }while(pilih != 5);

    return 0;
}