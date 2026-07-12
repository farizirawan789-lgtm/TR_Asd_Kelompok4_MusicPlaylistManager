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

#define NAMA_FILE "playlist.txt"

//Menyimpan Palylist ke File
void simpanfile() {
    FILE *fp = fopen(NAMA_FILE, "w");

    if(fp == NULL){
        printf("\nGagal menyimpan ke file!\n");
        return;
    }

    Lagu *temp = head;

    while(temp != NULL){
        fprintf(fp, "%s\n", temp->judul);
        fprintf(fp, "%s\n", temp->penyanyi);
        fprintf(fp, "%d\n", temp->durasi);
        temp = temp->next;
    }

    fclose(fp);
}

// Muat Playlist dari File
void muatdarifile() {
    FILE *fp = fopen(NAMA_FILE, "r");

    if(fp == NULL){
        return;
    }

    char baris[100];

    while(fgets(baris, sizeof(baris), fp) != NULL){
        Lagu *baru = (Lagu*)malloc(sizeof(Lagu));

        baris[strcspn(baris, "\n")] = 0;
        strcpy(baru->judul, baris);

        fgets(baris, sizeof(baris), fp);
        baris[strcspn(baris, "\n")] = 0;
        strcpy(baru->penyanyi, baris);

        fgets(baris, sizeof(baris), fp);
        baru->durasi = atoi(baris);

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
    }

    fclose(fp);
}

// Tambah Lagu
void tambahlagu() {
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

    simpanfile();
    printf("\nLagu berhasil ditambahkan!\n");
}

// Tampilkan Playlist
void tampilplaylist() {
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
void carilagu() {
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

// Update Lagu
void updatelagu() {
    char cari[100];

    if(head == NULL){
        printf("\nPlaylist masih kosong!\n");
        return;
    }

    printf("\nMasukkan Judul Lagu yang ingin diupdate: ");
    getchar();
    fgets(cari, sizeof(cari), stdin);
    cari[strcspn(cari, "\n")] = 0;

    Lagu *temp = head;

    while(temp != NULL && strcmp(temp->judul, cari) != 0){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("\nLagu tidak ditemukan.\n");
        return;
    }

    printf("\nData lama:\n");
    printf("Judul    : %s\n", temp->judul);
    printf("Penyanyi : %s\n", temp->penyanyi);
    printf("Durasi   : %d menit\n", temp->durasi);

    printf("\nMasukkan data baru\n");

    printf("Judul Lagu    : ");
    fgets(temp->judul, sizeof(temp->judul), stdin);
    temp->judul[strcspn(temp->judul, "\n")] = 0;

    printf("Nama Penyanyi : ");
    fgets(temp->penyanyi, sizeof(temp->penyanyi), stdin);
    temp->penyanyi[strcspn(temp->penyanyi, "\n")] = 0;

    printf("Durasi (menit): ");
    scanf("%d", &temp->durasi);

    simpanfile();
    printf("\nLagu berhasil diupdate!\n");
}

// Hapus Lagu
void hapuslagu() {
    char hapus[100];
    char yakin;

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

    printf("\nData Lagu\n");
    printf("judul    : %s\n", temp->judul);
    printf("Penyanyi : %s\n", temp->penyanyi);
    printf("Durasi   : %d menit\n", temp->durasi);

    printf("Yakin ingin menghapus lagu ini? (y/t): ");
    scanf(" %c",&yakin);

    if(yakin == 'y' || yakin == 'Y'){
    }else{
        printf("Penghapusan dibatalkan.\n");
        return;
    }


    if(prev == NULL){
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    free(temp);

    simpanfile();
    printf("\nLagu berhasil dihapus.\n");
}

// Sorting berdasarkan Judul (A-Z)
void sortingjudul() {
    if(head == NULL || head->next == NULL){
        printf("\nData tidak cukup untuk disorting!\n");
        return;
    }

    Lagu *i, *j;

    for(i = head; i->next != NULL; i = i->next){
        for(j = head; j->next != NULL; j = j->next){
            if(strcmp(j->judul, j->next->judul) > 0){
                char tempJudul[100], tempPenyanyi[100];
                int tempDurasi;

                strcpy(tempJudul, j->judul);
                strcpy(tempPenyanyi, j->penyanyi);
                tempDurasi = j->durasi;

                strcpy(j->judul, j->next->judul);
                strcpy(j->penyanyi, j->next->penyanyi);
                j->durasi = j->next->durasi;

                strcpy(j->next->judul, tempJudul);
                strcpy(j->next->penyanyi, tempPenyanyi);
                j->next->durasi = tempDurasi;
            }
        }
    }

    simpanfile();
    printf("\nPlaylist berhasil diurutkan berdasarkan judul!\n");
}

// Sorting berdasarkan Durasi (terkecil ke terbesar)
void sortingdurasi() {
    if(head == NULL || head->next == NULL){
        printf("\nData tidak cukup untuk disorting!\n");
        return;
    }

    Lagu *i, *j;

    for(i = head; i->next != NULL; i = i->next){
        for(j = head; j->next != NULL; j = j->next){
            if(j->durasi > j->next->durasi){
                char tempJudul[100], tempPenyanyi[100];
                int tempDurasi;

                strcpy(tempJudul, j->judul);
                strcpy(tempPenyanyi, j->penyanyi);
                tempDurasi = j->durasi;

                strcpy(j->judul, j->next->judul);
                strcpy(j->penyanyi, j->next->penyanyi);
                j->durasi = j->next->durasi;

                strcpy(j->next->judul, tempJudul);
                strcpy(j->next->penyanyi, tempPenyanyi);
                j->next->durasi = tempDurasi;
            }
        }
    }

    simpanfile();
    printf("\nPlaylist berhasil diurutkan berdasarkan durasi!\n");
}

int main() {

    int pilih;

    muatdarifile();

    do{
        printf("\n==============================\n");
        printf("||  MUSIC PLAYLIST MANAGER  ||\n");
        printf("==============================\n");
        printf("1. Tambah Lagu\n");
        printf("2. Tampilkan Playlist\n");
        printf("3. Cari Lagu\n");
        printf("4. Update Lagu\n");
        printf("5. Hapus Lagu\n");
        printf("6. Sorting Judul\n");
        printf("7. Sorting Durasi\n");
        printf("8. Keluar\n");
        printf("=============================\n");
        printf("Pilih Menu : ");
        scanf("%d",&pilih);

        switch(pilih){

        case 1:
            tambahlagu();
            break;

        case 2:
            tampilplaylist();
            break;

        case 3:
            carilagu();
            break;

        case 4:
            updatelagu();
            break;

        case 5:
            hapuslagu();
            break;

        case 6:
            sortingjudul();
            break;

        case 7:
            sortingdurasi();
            break;

        case 8:
            printf("\nTerima kasih telah menggunakan Music Playlist Manager.\n");
            break;

        default:
            printf("\nMenu tidak tersedia!\n");
        }

    }while(pilih != 8);

    return 0;
}
