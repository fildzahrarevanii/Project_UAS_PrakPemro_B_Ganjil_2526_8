<<<<<<< HEAD
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANGGOTA_FILE "data/anggota.txt"
#define PINJAM_FILE  "data/peminjaman.txt"

struct Anggota {
    int id;
    char nama[100];
    char alamat[150];
    char nohp[20];
};

void menu();
void tambahAnggota();
void lihatAnggota();
void editAnggota();
void hapusAnggota();
void riwayatAnggota();
int getLastId();

/* ============================
   CLEAR SCREEN
============================ */
void clear() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ============================
   PROGRAM UTAMA
============================ */
int main() {
    menu();
    return 0;
}

/* ============================
   MENU UTAMA
============================ */
void menu() {
    int pilih;

    do {
        printf("\n===== MENU ANGGOTA PERPUSTAKAAN =====\n");
        printf("1. Tambah Anggota\n");
        printf("2. Lihat Daftar Anggota\n");
        printf("3. Edit Anggota\n");
        printf("4. Hapus Anggota\n");
        printf("5. Lihat Riwayat Peminjaman Anggota\n");
        printf("0. Keluar\n");
        printf("Pilih menu: ");
        scanf("%d", &pilih);
        getchar();

        switch (pilih) {
        case 1: tambahAnggota(); break;
        case 2: lihatAnggota(); break;
        case 3: editAnggota(); break;
        case 4: hapusAnggota(); break;
        case 5: riwayatAnggota(); break;
        }
    } while (pilih != 0);
}

/* ============================
   DAPATKAN ID TERAKHIR
============================ */
int getLastId() {
    FILE *fp = fopen(ANGGOTA_FILE, "r");
    if (!fp) return 0;

    int last = 0;
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), fp)) {
        int id;
        sscanf(buffer, "%d|", &id);
        if (id > last)
            last = id;
    }

    fclose(fp);
    return last;
}

/* ============================
   TAMBAH ANGGOTA
============================ */
void tambahAnggota() {
    FILE *fp = fopen(ANGGOTA_FILE, "a");
    if (!fp) {
        printf("Gagal membuka file anggota.txt!\n");
        return;
    }

    struct Anggota a;
    a.id = getLastId() + 1;

    printf("Nama: ");
    fgets(a.nama, sizeof(a.nama), stdin);
    a.nama[strcspn(a.nama, "\n")] = 0;

    printf("Alamat: ");
    fgets(a.alamat, sizeof(a.alamat), stdin);
    a.alamat[strcspn(a.alamat, "\n")] = 0;

    printf("No HP: ");
    fgets(a.nohp, sizeof(a.nohp), stdin);
    a.nohp[strcspn(a.nohp, "\n")] = 0;

    fprintf(fp, "%d|%s|%s|%s\n", a.id, a.nama, a.alamat, a.nohp);
    fclose(fp);

    printf("Anggota berhasil ditambahkan!\n");
}

/* ============================
   LIHAT SEMUA ANGGOTA
============================ */
void lihatAnggota() {
    FILE *fp = fopen(ANGGOTA_FILE, "r");
    if (!fp) {
        printf("Belum ada data anggota.\n");
        return;
    }

    char line[256];
    printf("\n===== DAFTAR ANGGOTA =====\n");

    while (fgets(line, sizeof(line), fp)) {
        struct Anggota a;
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        printf("%d. %s | %s | %s\n", a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
}

/* ============================
   EDIT ANGGOTA
============================ */
void editAnggota() {
    int id;
    printf("Masukkan ID anggota yang ingin diedit: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(ANGGOTA_FILE, "r");
    FILE *temp = fopen("data/tmp.txt", "w");

    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        return;
    }

    char line[256];
    int found = 0;
    struct Anggota a;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id) {
            found = 1;

            printf("Nama baru: ");
            fgets(a.nama, sizeof(a.nama), stdin);
            a.nama[strcspn(a.nama, "\n")] = 0;

            printf("Alamat baru: ");
            fgets(a.alamat, sizeof(a.alamat), stdin);
            a.alamat[strcspn(a.alamat, "\n")] = 0;

            printf("No HP baru: ");
            fgets(a.nohp, sizeof(a.nohp), stdin);
            a.nohp[strcspn(a.nohp, "\n")] = 0;

            fprintf(temp, "%d|%s|%s|%s\n", a.id, a.nama, a.alamat, a.nohp);
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(ANGGOTA_FILE);
    rename("data/tmp.txt", ANGGOTA_FILE);

    if (found)
        printf("Data anggota berhasil diperbarui!\n");
    else
        printf("ID anggota tidak ditemukan.\n");
}

/* ============================
   HAPUS ANGGOTA
============================ */
void hapusAnggota() {
    int id;
    printf("Masukkan ID anggota yang ingin dihapus: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(ANGGOTA_FILE, "r");
    FILE *temp = fopen("data/tmp.txt", "w");

    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        return;
    }

    char line[256];
    int found = 0;
    struct Anggota a;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id) {
            found = 1; // skip (hapus)
        } else {
            fputs(line, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(ANGGOTA_FILE);
    rename("data/tmp.txt", ANGGOTA_FILE);

    if (found)
        printf("Anggota berhasil dihapus.\n");
    else
        printf("ID anggota tidak ditemukan.\n");
}

/* ============================
   RIWAYAT PEMINJAMAN ANGGOTA
============================ */
void riwayatAnggota() {
    int id;
    printf("Masukkan ID anggota: ");
    scanf("%d", &id);
    getchar();

    FILE *fp = fopen(PINJAM_FILE, "r");
    if (!fp) {
        printf("File peminjaman.txt tidak ditemukan.\n");
        return;
    }

    char line[256];
    int found = 0;

    printf("\n===== RIWAYAT PEMINJAMAN ANGGOTA %d =====\n", id);

    while (fgets(line, sizeof(line), fp)) {
        int id_pinjam, id_buku, id_anggota;
        char tgl_pinjam[20], tgl_kembali[20];

        sscanf(line, "%d|%d|%d|%[^|]|%s",
               &id_pinjam, &id_buku, &id_anggota,
               tgl_pinjam, tgl_kembali);

        if (id_anggota == id) {
            found = 1;
            printf("Pinjam #%d | Buku ID %d | %s -> %s\n",
                   id_pinjam, id_buku, tgl_pinjam, tgl_kembali);
        }
    }

    fclose(fp);

    if (!found)
        printf("Tidak ada riwayat peminjaman untuk anggota ini.\n");
=======
#include "perpustakaan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TMP_FILE "data/tmp.txt"

// Ambil ID terakhir
static int get_last_id() {
    FILE *fp = fopen(FILE_ANGGOTA, "r");
    if (!fp) return 0;

    int last = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp)) {
        int id;
        sscanf(line, "%d|", &id);
        if (id > last) last = id;
    }
    fclose(fp);
    return last;
}

/* =========================== TAMBAH =========================== */

void tambah_anggota() {
    FILE *fp = fopen(FILE_ANGGOTA, "a");
    if (!fp) {
        printf("Gagal membuka %s\n", FILE_ANGGOTA);
        return;
    }

    anggota a;
    a.id = get_last_id() + 1;

    printf("Nama      : ");
    read_line(a.nama, sizeof(a.nama));

    printf("Alamat    : ");
    read_line(a.alamat, sizeof(a.alamat));

    printf("No HP     : ");
    read_line(a.nohp, sizeof(a.nohp));

    fprintf(fp, "%d|%s|%s|%s\n",
            a.id, a.nama, a.alamat, a.nohp);

    fclose(fp);

    printf("Anggota berhasil ditambahkan.\n");
}

/* ======================== TAMPILKAN DATA ======================== */

void tampilkan_daftar_anggota() {
    FILE *fp = fopen(FILE_ANGGOTA, "r");
    if (!fp) {
        printf("Belum ada data anggota.\n");
        return;
    }

    anggota a;
    char line[256];

    printf("\n==== DAFTAR ANGGOTA ====\n");

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        printf("%d. %s | %s | %s\n", a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
}

/* =========================== EDIT =========================== */

void edit_anggota() {
    int id;
    printf("Masukkan ID anggota yang ingin diedit: ");
    scanf("%d", &id);
    clear_input();

    FILE *fp = fopen(FILE_ANGGOTA, "r");
    FILE *temp = fopen(TMP_FILE, "w");

    if (!fp || !temp) {
        printf("Gagal membuka file.\n");
        return;
    }

    anggota a;
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id) {
            found = 1;

            printf("Nama baru   : ");
            read_line(a.nama, sizeof(a.nama));

            printf("Alamat baru : ");
            read_line(a.alamat, sizeof(a.alamat));

            printf("No HP baru  : ");
            read_line(a.nohp, sizeof(a.nohp));
        }

        fprintf(temp, "%d|%s|%s|%s\n",
                a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_ANGGOTA);
    rename(TMP_FILE, FILE_ANGGOTA);

    if (found)
        printf("Data anggota berhasil diupdate.\n");
    else
        printf("ID anggota tidak ditemukan.\n");
}

/* =========================== HAPUS =========================== */

void hapus_anggota() {
    int id;
    printf("Masukkan ID anggota yang ingin dihapus: ");
    scanf("%d", &id);
    clear_input();

    FILE *fp = fopen(FILE_ANGGOTA, "r");
    FILE *temp = fopen(TMP_FILE, "w");

    if (!fp || !temp) {
        printf("Gagal membuka file.\n");
        return;
    }

    anggota a;
    char line[256];
    int found = 0;

    while (fgets(line, sizeof(line), fp)) {
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id) {
            found = 1;
            continue; // skip yang dihapus
        }

        fprintf(temp, "%d|%s|%s|%s\n",
                a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_ANGGOTA);
    rename(TMP_FILE, FILE_ANGGOTA);

    if (found)
        printf("Anggota berhasil dihapus.\n");
    else
        printf("ID tidak ditemukan.\n");
>>>>>>> 7b89aa2 (Simpan perubahan lokal sebelum pull)
}