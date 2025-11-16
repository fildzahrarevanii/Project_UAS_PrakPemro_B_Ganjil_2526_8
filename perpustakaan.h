// Header utama: deklarasi struct & prototype fungsi untuk Perpustakaan Mini

#ifndef PERPUSTAKAAN_H
#define PERPUSTAKAAN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOK 1000
#define MAX_MEMBER 1000
#define MAX_LOAN 1000

// path file data
#define FILE_BUKU "data/buku.txt"
// DIHAPUS: #define FILE_ANGGOTA "data/anggota.txt"
#define FILE_PINJAMAN "data/peminjaman.txt"
#define FILE_LOGIN "data/login.txt"
#define FILE_SETTING "data/setting.txt"

// struktur data
typedef struct {
    int id;              
    char judul[100];
    char penulis[100];
    char kategori[30];      // Fiksi, Non-Fiksi, Komik, Majalah, Referensi
    int tersedia;           // 1 = tersedia, 0 = dipinjam
    int jumlah_dipinjam;    // untuk ranking (dibiarkan, masih dipakai di buku.c)
} buku;

// DIHAPUS: typedef struct { ... } anggota;

typedef struct {
    int id_peminjaman;
    int id_buku;
    int id_anggota; // Dibiarkan agar peminjaman.c tetap berfungsi
    char tanggal_pinjam[20];   // format YYYY-MM-DD
    char tanggal_kembali[20];  // saat pinjam
    int lama_pinjam; // total hari pinjam
    int hari_terlambat; // hari telat
    int status;               // 0 = belum kembali, 1 = sudah
    int denda;                // denda saat dikembalikan
} peminjaman;

// prototype fungsi

// main.c 
int main(void);

// menu.c
void tampilkan_menu_utama(void);
void tampilkan_sub_menu_buku(void);
void tampilkan_sub_menu_peminjaman(void);

// login.c
int login_pustakawan(void);

// buku.c
void tambah_buku(void);
void hapus_buku(void);
void edit_buku(void);
void tampilkan_daftar_buku(void);
void cari_buku(void);
void kategorikan_buku(void);

// DIHAPUS: Blok fungsi anggota.c

// peminjaman.c
void pinjam_buku();
void kembalikan_buku();
void tampilkan_riwayat_peminjaman(void);

// DIHAPUS: Blok fungsi ranking.c

// filehandler.c
FILE* buka_file(const char *path, const char *mode);
void ensure_data_files_exist(void);

// util.c
void clear_screen(void);
void pause_screen(void);
int get_max_hari_pinjam(void);
int get_denda_per_hari(void);

#endif
