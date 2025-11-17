#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 512

/* path file data */
#define FILE_BUKU "data/buku.txt"
#define FILE_ANGGOTA "data/anggota.txt"
#define FILE_PINJAMAN "data/peminjaman.txt"
#define FILE_LOGIN "data/login.txt"
#define FILE_SETTING "data/setting.txt"

/* struktur buku */
typedef struct {
    int id;
    char judul[100];
    char penulis[100];
    char kategori[30];
    int tersedia; /* 1 tersedia, 0 dipinjam */
    int jumlah_dipinjam;
} buku;

/* struktur anggota */
typedef struct {
    int id;
    char nama[100];
    char alamat[150];
    char nohp[30];
} anggota;

/* struktur peminjaman */
typedef struct {
    int id_peminjaman;
    int id_buku;
    int id_anggota;
    char tanggal_pinjam[20];
    char tanggal_kembali[20];
    int lama_pinjam;
    int hari_terlambat;
    int status; /* 0 belum kembali, 1 kembali */
    int denda;
} peminjaman;

/* prototipe */
int main(void);

/* menu.c */
void tampilkan_menu_utama(void);
void tampilkan_sub_menu_buku(void);
void tampilkan_sub_menu_anggota(void);
void tampilkan_sub_menu_peminjaman(void);
void tampilkan_sub_menu_setting(void);

/* login.c */
int login_pustakawan(void);

/* buku.c */
void tambah_buku(void);
void hapus_buku(void);
void edit_buku(void);
void tampilkan_daftar_buku(void);
void cari_buku(void);

/* anggota.c */
void tambah_anggota(void);
void hapus_anggota(void);
void edit_anggota(void);
void tampilkan_daftar_anggota(void);

/* peminjaman.c */
void pinjam_buku(void);
void kembalikan_buku(void);
void tampilkan_riwayat_peminjaman(void);

/* filehandler.c */
FILE* buka_file(const char *path, const char *mode);
void ensure_data_files_exist(void);

/* util.c */
void clear_screen(void);
void pause_screen(void);
int read_int_safe(void);
void read_line(char *buffer, int size);
void clear_input(void);  /* <-- ditambahkan agar warning hilang */

/* setting helpers */
int get_max_hari_pinjam(void);
int get_denda_per_hari(void);

#endif