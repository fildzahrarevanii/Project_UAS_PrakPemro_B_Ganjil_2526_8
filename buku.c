#include "perpustakaan.h"

static int next_buku_id() {
    FILE *f = fopen(FILE_BUKU, "r");
    if (!f) return 1;

    int id, last_id = 0;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d|", &id) == 1) {
            if (id > last_id) last_id = id;
        }
    }

    fclose(f);
    return last_id + 1;
}

static void simpan_buku(buku b) {
    FILE *f = fopen(FILE_BUKU, "a");
    if (!f) {
        printf("Gagal membuka file buku.\n");
        return;
    }

    fprintf(f, "%d|%s|%s|%s|%d|%d\n",
            b.id, b.judul, b.penulis, b.kategori,
            b.tersedia, b.jumlah_dipinjam);

    fclose(f);
}

void tambah_buku() {
    buku b;
    b.id = next_buku_id();

    printf("\n=== Tambah Buku ===\n");
    printf("Judul: ");
    read_line(b.judul, sizeof(b.judul));
    printf("Penulis: ");
    read_line(b.penulis, sizeof(b.penulis));
    printf("Kategori: ");
    read_line(b.kategori, sizeof(b.kategori));

    b.tersedia = 1;
    b.jumlah_dipinjam = 0;

    simpan_buku(b);

    printf("Buku berhasil ditambahkan dengan ID %d.\n", b.id);
    pause_screen();
}

void tampilkan_daftar_buku() {
    FILE *f = fopen(FILE_BUKU, "r");
    if (!f) {
        printf("Belum ada data buku.\n");
        pause_screen();
        return;
    }

    printf("\n=== Daftar Buku ===\n");

    buku b;
    char line[MAX_LINE];

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori,
                   &b.tersedia, &b.jumlah_dipinjam) == 6) {

            printf("ID: %d\n", b.id);
            printf("Judul: %s\n", b.judul);
            printf("Penulis: %s\n", b.penulis);
            printf("Kategori: %s\n", b.kategori);
            printf("Status: %s\n", b.tersedia ? "Tersedia" : "Dipinjam");
            printf("Dipinjam: %d kali\n", b.jumlah_dipinjam);
            printf("-------------------------\n");
        }
    }

    fclose(f);
    pause_screen();
}

void hapus_buku() {
    int id_hapus;
    printf("Masukkan ID buku yang ingin dihapus: ");
    id_hapus = read_int_safe();

    FILE *f = fopen(FILE_BUKU, "r");
    FILE *tmp = fopen("data/buku_tmp.txt", "w");

    if (!f || !tmp) {
        printf("Gagal membuka file.\n");
        return;
    }

    buku b;
    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori,
                   &b.tersedia, &b.jumlah_dipinjam) == 6) {

            if (b.id == id_hapus) {
                found = 1;
                continue;
            }

            fprintf(tmp, "%d|%s|%s|%s|%d|%d\n",
                    b.id, b.judul, b.penulis, b.kategori,
                    b.tersedia, b.jumlah_dipinjam);
        }
    }

    fclose(f);
    fclose(tmp);

    remove(FILE_BUKU);
    rename("data/buku_tmp.txt", FILE_BUKU);

    if (found)
        printf("Buku berhasil dihapus.\n");
    else
        printf("ID buku tidak ditemukan.\n");

    pause_screen();
}

void edit_buku() {
    int id_edit;
    printf("Masukkan ID buku yang ingin diedit: ");
    id_edit = read_int_safe();

    FILE *f = fopen(FILE_BUKU, "r");
    FILE *tmp = fopen("data/buku_tmp.txt", "w");

    if (!f || !tmp) {
        printf("Gagal membuka file.\n");
        return;
    }

    buku b;
    char line[MAX_LINE];
    int found = 0;

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori,
                   &b.tersedia, &b.jumlah_dipinjam) == 6) {

            if (b.id == id_edit) {
                found = 1;

                printf("Judul (%s): ", b.judul);
                read_line(b.judul, sizeof(b.judul));

                printf("Penulis (%s): ", b.penulis);
                read_line(b.penulis, sizeof(b.penulis));

                printf("Kategori (%s): ", b.kategori);
                read_line(b.kategori, sizeof(b.kategori));
            }

            fprintf(tmp, "%d|%s|%s|%s|%d|%d\n",
                    b.id, b.judul, b.penulis, b.kategori,
                    b.tersedia, b.jumlah_dipinjam);
        }
    }

    fclose(f);
    fclose(tmp);

    remove(FILE_BUKU);
    rename("data/buku_tmp.txt", FILE_BUKU);

    if (found)
        printf("Buku berhasil diedit.\n");
    else
        printf("ID buku tidak ditemukan.\n");

    pause_screen();
}

void cari_buku() {
    char keyword[100];
    printf("Masukkan kata kunci: ");
    read_line(keyword, sizeof(keyword));

    FILE *f = fopen(FILE_BUKU, "r");
    if (!f) {
        printf("Belum ada data buku.\n");
        pause_screen();
        return;
    }

    buku b;
    char line[MAX_LINE];
    int ditemukan = 0;

    printf("\n=== Hasil Pencarian ===\n");

    while (fgets(line, sizeof(line), f)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori,
                   &b.tersedia, &b.jumlah_dipinjam) == 6) {

            if (strstr(b.judul, keyword) ||
                strstr(b.penulis, keyword) ||
                strstr(b.kategori, keyword)) {

                printf("ID: %d\n", b.id);
                printf("Judul: %s\n", b.judul);
                printf("Penulis: %s\n", b.penulis);
                printf("Kategori: %s\n", b.kategori);
                printf("Status: %s\n", b.tersedia ? "Tersedia" : "Dipinjam");
                printf("-------------------------\n");
                ditemukan = 1;
            }
        }
    }

    if (!ditemukan)
        printf("Tidak ada buku yang cocok.\n");

    fclose(f);
    pause_screen();
}