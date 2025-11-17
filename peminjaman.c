#include "perpustakaan.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id_transaksi;
    int id_anggota;
    int id_buku;
    char tanggal_pinjam[20];
    char tanggal_kembali[20];
    int denda;
} Transaksi;

/* simpan transaksi baru */
void simpan_transaksi(Transaksi t) {
    FILE *fp = fopen(FILE_PINJAMAN, "a");
    if (!fp) {
        printf("Gagal membuka %s!\n", FILE_PINJAMAN);
        return;
    }

    fprintf(fp, "%d|%d|%d|%s|%s|%d\n",
            t.id_transaksi, t.id_anggota, t.id_buku,
            t.tanggal_pinjam, t.tanggal_kembali, t.denda);

    fclose(fp);
}

/* ---- PINJAM BUKU ---- */
void pinjam_buku() {
    Transaksi t;

    printf("ID Transaksi: ");
    scanf("%d", &t.id_transaksi);

    printf("ID Anggota: ");
    scanf("%d", &t.id_anggota);

    printf("ID Buku: ");
    scanf("%d", &t.id_buku);

    printf("Tanggal Pinjam (YYYY-MM-DD): ");
    scanf("%s", t.tanggal_pinjam);

    strcpy(t.tanggal_kembali, "-");
    t.denda = 0;

    simpan_transaksi(t);

    printf("Peminjaman disimpan.\n");
}

/* ---- KEMBALIKAN BUKU ---- */
void kembalikan_buku() {
    int id;
    char tanggal_kembali[20];

    printf("ID Transaksi yang dikembalikan: ");
    scanf("%d", &id);

    printf("Tanggal Kembali (YYYY-MM-DD): ");
    scanf("%s", tanggal_kembali);

    FILE *fp = fopen(FILE_PINJAMAN, "r");
    if (!fp) {
        printf("Gagal membuka %s.\n", FILE_PINJAMAN);
        return;
    }

    FILE *temp = fopen("data/temp.txt", "w");
    if (!temp) {
        printf("Gagal membuat file temp.\n");
        fclose(fp);
        return;
    }

    Transaksi t;
    int found = 0;

    while (fscanf(fp, "%d|%d|%d|%[^|]|%[^|]|%d",
                  &t.id_transaksi, &t.id_anggota, &t.id_buku,
                  t.tanggal_pinjam, t.tanggal_kembali, &t.denda) != EOF)
    {
        if (t.id_transaksi == id && strcmp(t.tanggal_kembali, "-") == 0) {

            strcpy(t.tanggal_kembali, tanggal_kembali);

            int denda_per_hari = get_denda_per_hari();

            /* hitung denda manual (sederhana) */
            t.denda = 0;  // kamu boleh pasang logika tambahan nanti

            found = 1;
            printf("Buku %d dikembalikan oleh anggota %d.\n", t.id_buku, t.id_anggota);
        }

        fprintf(temp, "%d|%d|%d|%s|%s|%d\n",
                t.id_transaksi, t.id_anggota, t.id_buku,
                t.tanggal_pinjam, t.tanggal_kembali, t.denda);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_PINJAMAN);
    rename("data/temp.txt", FILE_PINJAMAN);

    if (!found)
        printf("Transaksi tidak ditemukan atau sudah dikembalikan.\n");
    else
        printf("Pengembalian berhasil.\n");
}

/* ---- RIWAYAT PEMINJAMAN ---- */
void tampilkan_riwayat_peminjaman(void) {
    int id;
    printf("ID Anggota: ");
    scanf("%d", &id);

    FILE *fp = fopen(FILE_PINJAMAN, "r");
    if (!fp) {
        printf("Tidak ada data peminjaman.\n");
        return;
    }

    Transaksi t;
    printf("\n===== RIWAYAT ANGGOTA %d =====\n", id);

    while (fscanf(fp, "%d|%d|%d|%[^|]|%[^|]|%d",
                  &t.id_transaksi, &t.id_anggota, &t.id_buku,
                  t.tanggal_pinjam, t.tanggal_kembali, &t.denda) != EOF)
    {
        if (t.id_anggota == id) {
            printf("Transaksi %d | Buku %d | %s -> %s | Denda: %d\n",
                   t.id_transaksi, t.id_buku,
                   t.tanggal_pinjam, t.tanggal_kembali, t.denda);
        }
    }

    fclose(fp);
}