#include "perpustakaan.h"

#define TMP_FILE "data/tmp.txt"

/* =========================
   TAMBAH ANGGOTA
========================= */
void tambah_anggota(void) {
    FILE *fp = fopen(FILE_ANGGOTA, "a");
    if (!fp) {
        printf("Gagal membuka file anggota!\n");
        return;
    }

    anggota a;
    int last_id = 0;
    FILE *fp_read = fopen(FILE_ANGGOTA, "r");
    if (fp_read) {
        char line[MAX_LINE];
        while (fgets(line, sizeof(line), fp_read)) {
            int id;
            sscanf(line, "%d|", &id);
            if (id > last_id) last_id = id;
        }
        fclose(fp_read);
    }
    a.id = last_id + 1;

    printf("Nama      : ");
    read_line(a.nama, sizeof(a.nama));

    printf("Alamat    : ");
    read_line(a.alamat, sizeof(a.alamat));

    printf("No HP     : ");
    read_line(a.nohp, sizeof(a.nohp));

    fprintf(fp, "%d|%s|%s|%s\n", a.id, a.nama, a.alamat, a.nohp);
    fclose(fp);

    printf("Anggota berhasil ditambahkan!\n");
}

/* =========================
   LIHAT SEMUA ANGGOTA
========================= */
void tampilkan_daftar_anggota(void) {
    FILE *fp = fopen(FILE_ANGGOTA, "r");
    if (!fp) {
        printf("Belum ada data anggota.\n");
        return;
    }

    char line[MAX_LINE];
    printf("\n===== DAFTAR ANGGOTA =====\n");

    while (fgets(line, sizeof(line), fp)) {
        anggota a;
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);
        printf("%d. %s | %s | %s\n", a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
}

/* =========================
   EDIT ANGGOTA
========================= */
void edit_anggota(void) {
    int id;
    printf("Masukkan ID anggota yang ingin diedit: ");
    id = read_int_safe();
    clear_input();

    FILE *fp = fopen(FILE_ANGGOTA, "r");
    FILE *temp = fopen(TMP_FILE, "w");
    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        return;
    }

    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        anggota a;
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id) {
            found = 1;
            printf("Nama baru : ");
            read_line(a.nama, sizeof(a.nama));
            printf("Alamat baru : ");
            read_line(a.alamat, sizeof(a.alamat));
            printf("No HP baru : ");
            read_line(a.nohp, sizeof(a.nohp));
        }

        fprintf(temp, "%d|%s|%s|%s\n", a.id, a.nama, a.alamat, a.nohp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_ANGGOTA);
    rename(TMP_FILE, FILE_ANGGOTA);

    if (found)
        printf("Data anggota berhasil diperbarui.\n");
    else
        printf("ID anggota tidak ditemukan.\n");
}

/* =========================
   HAPUS ANGGOTA
========================= */
void hapus_anggota(void) {
    int id;
    printf("Masukkan ID anggota yang ingin dihapus: ");
    id = read_int_safe();
    clear_input();

    FILE *fp = fopen(FILE_ANGGOTA, "r");
    FILE *temp = fopen(TMP_FILE, "w");
    if (!fp || !temp) {
        printf("Gagal membuka file!\n");
        return;
    }

    char line[MAX_LINE];
    int found = 0;
    while (fgets(line, sizeof(line), fp)) {
        anggota a;
        sscanf(line, "%d|%[^|]|%[^|]|%s",
               &a.id, a.nama, a.alamat, a.nohp);

        if (a.id == id)
            found = 1;  // skip
        else
            fputs(line, temp);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_ANGGOTA);
    rename(TMP_FILE, FILE_ANGGOTA);

    if (found)
        printf("Anggota berhasil dihapus.\n");
    else
        printf("ID anggota tidak ditemukan.\n");
}