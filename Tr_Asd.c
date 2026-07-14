#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <windows.h>

struct Lagu {
    char judul[100];
    char penyanyi[100];
    char album[100];
    float durasi;
    struct Lagu *next;
};

typedef struct Lagu Lagu;
Lagu *head = NULL;

#define NAMA_FILE "playlist.txt"

/* Fungsi untuk menahan layar dan menunggu input enter dari pengguna */
void tunggu_enter() {
    getchar();
}

/* Fungsi untuk memvalidasi dan mengamankan input berupa angka dalam rentang tertentu */
int inputangka (char pesan[], int min, int max){
    char input[100];
    int angka;
    int i;

    while(1){
        printf("%s", pesan);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if(strlen(input) == 0){
            printf("Input tidak boleh kosong!\n");
            continue;
        }

        for(i = 0; input[i] != '\0'; i++){
            if(!isdigit(input[i])){
                printf("Input harus berupa angka!\n");
                break;
            }
        }

        if(input[i] != '\0'){
            continue;
        }

        angka = atoi(input);

        if(angka < min || angka > max){
            printf("Input harus antara %d sampai %d!\n", min, max);
            continue;
        }

        return angka;
    }
}

/* Fungsi untuk memvalidasi dan mengamankan input berupa angka desimal (float) */
float inputfloat(char pesan[], float min, float max) {
    char input[100];
    float angka;

    while(1) {
        printf("%s", pesan);
        fgets(input, sizeof(input), stdin);
        input[strcspn(input, "\n")] = 0;

        if(strlen(input) == 0) {
            printf("Input tidak boleh kosong!\n");
            continue;
        }

        char sampah;
        if(sscanf(input, "%f%c", &angka, &sampah) != 1) {
            printf("Input harus berupa angka (gunakan titik untuk koma, misal: 3.5)!\n");
            continue;
        }

        if(angka < min || angka > max) {
            printf("Input harus antara %.1f sampai %.1f!\n", min, max);
            continue;
        }

        return angka;
    }
}

/* Fungsi untuk memvalidasi input teks agar tidak boleh kosong */
void inputteks(char pesan[], char target[], int ukuran) {
    while(1) {
        printf("%s", pesan);
        fgets(target, ukuran, stdin);
        target[strcspn(target, "\n")] = 0;

        if(strlen(target) == 0) {
            printf("Input tidak boleh kosong!\n");
            continue;
        }
        break;
    }
}

/* Fungsi untuk menyimpan seluruh data linked list lagu ke dalam file teks */
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
        fprintf(fp, "%s\n", temp->album);
        fprintf(fp, "%.2f\n", temp->durasi);
        temp = temp->next;
    }
    fclose(fp);
}

/* Fungsi untuk memuat data lagu dari file teks ke dalam struktur linked list saat program dimulai */
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
        baris[strcspn(baris, "\n")] = 0;
        strcpy(baru->album, baris);

        fgets(baris, sizeof(baris), fp);
        baru->durasi = atof(baris);

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

/* Fungsi untuk menambahkan data lagu baru ke urutan terakhir linked list */
void tambahlagu() {
    system("cls");
    Lagu *baru = (Lagu*)malloc(sizeof(Lagu));

    printf("\n=== Tambah Lagu ===\n");
    inputteks("Judul Lagu    : ", baru->judul, sizeof(baru->judul));
    inputteks("Nama Penyanyi : ", baru->penyanyi, sizeof(baru->penyanyi));
    inputteks("Nama Album    : ", baru->album, sizeof(baru->album));
    baru->durasi = inputfloat("Durasi (menit): ", 0.1, 100.0);

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
    tunggu_enter();
}

/* Fungsi untuk menampilkan seluruh daftar lagu yang tersimpan beserta total durasi playlist */
void tampilplaylist() {
    system("cls");
    Lagu *temp = head;

    if(head == NULL){
        printf("\n============================================\n");
        printf("          PLAYLIST MASIH KOSONG\n");
        printf("============================================\n");
        tunggu_enter();
        return;
    }

    printf("\n===============================================================\n");
    printf("                          DAFTAR PLAYLIST\n");
    printf("===============================================================\n");

    int no = 1;
    float total_durasi = 0.0;

    while(temp != NULL){
        printf("  # Lagu ke-%d\n", no++);
        printf("|| Judul     : %s\n", temp->judul);
        printf("|| Penyanyi  : %s\n", temp->penyanyi);
        printf("|| Album     : %s\n", temp->album);
        printf("|| Durasi    : %.1f menit\n", temp->durasi);
        printf("\n");

        total_durasi += temp->durasi;
        temp = temp->next;
    }
    printf("===============================================================\n");
    printf("Total Lagu   : %d\n", no - 1);
    printf("Total Durasi : %.1f menit\n", total_durasi);
    tunggu_enter();
}

/* Fungsi untuk mencari lagu berdasarkan judul atau penyanyi secara case-insensitive */
void carilagu() {
    system("cls");
    char cari[100];

    inputteks("\nMasukkan Judul Lagu: ", cari, sizeof(cari));

    Lagu *temp = head;
    while(temp != NULL){
        if(strcasecmp(temp->judul, cari) == 0 || strcasecmp(temp->penyanyi, cari) == 0){
            printf("\nLagu ditemukan!\n");
            printf("Judul    : %s\n", temp->judul);
            printf("Penyanyi : %s\n", temp->penyanyi);
            printf("Album    : %s\n", temp->album);
            printf("Durasi   : %.1f menit\n", temp->durasi);

            tunggu_enter();
            return;
        }
        temp = temp->next;
    }
    printf("\nLagu dengan Judul atau Penyanyi tersebut tidak ditemukan\n");
    tunggu_enter();
}

/* Fungsi untuk mengubah atau memperbarui informasi data lagu lama berdasarkan judul */
void updatelagu() {
    system("cls");
    char cari[100];

    if(head == NULL){
        printf("\nPlaylist masih kosong!\n");
        tunggu_enter();
        return;
    }

    inputteks("\nMasukkan Judul Lagu yang ingin diupdate: ", cari, sizeof(cari));

    Lagu *temp = head;
    while(temp != NULL && strcmp(temp->judul, cari) != 0){
        temp = temp->next;
    }

    if(temp == NULL){
        printf("\nLagu tidak ditemukan.\n");
        tunggu_enter();
        return;
    }

    printf("\nData lama:\n");
    printf("Judul    : %s\n", temp->judul);
    printf("Penyanyi : %s\n", temp->penyanyi);
    printf("Album    : %s\n", temp->album);
    printf("Durasi   : %.1f menit\n", temp->durasi);

    printf("\nMasukkan data baru\n");
    inputteks("Judul Lagu    : ", temp->judul, sizeof(temp->judul));
    inputteks("Nama Penyanyi : ", temp->penyanyi, sizeof(temp->penyanyi));
    inputteks("Nama Album    : ", temp->album, sizeof(temp->album));
    temp->durasi = inputfloat("Durasi (menit): ", 0.1, 100.0);

    simpanfile();
    printf("\nLagu berhasil diupdate!\n");
    tunggu_enter();
}

/* Fungsi untuk menghapus data lagu tertentu dari linked list berdasarkan judul setelah konfirmasi konfirmasi */
void hapuslagu() {
    char hapus[100];
    char yakin;

    inputteks("\nMasukkan Judul Lagu yang ingin dihapus: ", hapus, sizeof(hapus));

    Lagu *temp = head;
    Lagu *prev = NULL;

    while(temp != NULL && strcmp(temp->judul, hapus) != 0){
        prev = temp;
        temp = temp->next;
    }

    if(temp == NULL){
        printf("\nLagu tidak ditemukan.\n");
        tunggu_enter();
        return;
    }

    printf("\nData Lagu\n");
    printf("judul    : %s\n", temp->judul);
    printf("Penyanyi : %s\n", temp->penyanyi);
    printf("Album    : %s\n", temp->album);
    printf("Durasi   : %.1f menit\n", temp->durasi);

    printf("Yakin ingin menghapus lagu ini? (y/t): ");
    scanf(" %c",&yakin);
    while(getchar() != '\n');

    if(yakin == 'y' || yakin == 'Y'){
        if(prev == NULL){
            head = temp->next;
        } else {
            prev->next = temp->next;
        }

        free(temp);
        simpanfile();

        printf("\nLagu berhasil dihapus.\n");
        tunggu_enter();
    } else {
        printf("Penghapusan dibatalkan.\n");
        tunggu_enter();
        return;
    }
}

/* Fungsi untuk mengurutkan daftar lagu berdasarkan alfabet Judul secara ascending (A-Z) */
void sortingjudul() {
    system("cls");
    if(head == NULL || head->next == NULL){
        printf("\nData tidak cukup untuk disorting!\n");
        tunggu_enter();
        return;
    }

    Lagu *i, *j;
    for(i = head; i->next != NULL; i = i->next){
        for(j = head; j->next != NULL; j = j->next){
            if(strcmp(j->judul, j->next->judul) > 0){
                char tempJudul[100], tempPenyanyi[100], tempAlbum[100];
                float tempDurasi;

                strcpy(tempJudul, j->judul);
                strcpy(tempPenyanyi, j->penyanyi);
                strcpy(tempAlbum, j->album);
                tempDurasi = j->durasi;

                strcpy(j->judul, j->next->judul);
                strcpy(j->penyanyi, j->next->penyanyi);
                strcpy(j->album, j->next->album);
                j->durasi = j->next->durasi;

                strcpy(j->next->judul, tempJudul);
                strcpy(j->next->penyanyi, tempPenyanyi);
                strcpy(j->next->album, tempAlbum);
                j->next->durasi = tempDurasi;
            }
        }
    }

    simpanfile();
    printf("\nPlaylist berhasil diurutkan berdasarkan judul!\n");
    tunggu_enter();
}

/* Fungsi untuk mengurutkan daftar lagu berdasarkan durasi terkecil ke terbesar */
void sortingdurasi() {
    system("cls");
    if(head == NULL || head->next == NULL){
        printf("\nData tidak cukup untuk disorting!\n");
        tunggu_enter();
        return;
    }

    Lagu *i, *j;
    for(i = head; i->next != NULL; i = i->next){
        for(j = head; j->next != NULL; j = j->next){
            if(j->durasi > j->next->durasi){
                char tempJudul[100], tempPenyanyi[100], tempAlbum[100];
                float tempDurasi;

                strcpy(tempJudul, j->judul);
                strcpy(tempPenyanyi, j->penyanyi);
                strcpy(tempAlbum, j->album);
                tempDurasi = j->durasi;

                strcpy(j->judul, j->next->judul);
                strcpy(j->penyanyi, j->next->penyanyi);
                strcpy(j->album, j->next->album);
                j->durasi = j->next->durasi;

                strcpy(j->next->judul, tempJudul);
                strcpy(j->next->penyanyi, tempPenyanyi);
                strcpy(j->next->album, tempAlbum);
                j->next->durasi = tempDurasi;
            }
        }
    }

    simpanfile();
    printf("\nPlaylist berhasil diurutkan berdasarkan durasi!\n");
    tunggu_enter();
}

int main() {
    int pilih;
    muatdarifile();

    do{
        system("cls");
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
        pilih = inputangka("Pilih Menu : ", 1, 8);

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

    Lagu *temp;
    while(head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}
