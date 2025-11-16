// denda.c - Implementasi fungsi denda (dengan main() untuk test standalone)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "denda.h"  // Pastikan file denda.h ada di direktori sama

// Fungsi untuk menghitung selisih hari antara dua tanggal (diperbaiki dengan validasi)
int hitung_selisih_hari(char *tanggal1, char *tanggal2) {
    if (!tanggal1 || !tanggal2 || strlen(tanggal1) != 10 || strlen(tanggal2) != 10) {
        printf("Error: Format tanggal salah (harus YYYY-MM-DD).\n");
        return -1;
    }
    
    struct tm tm1 = {0}, tm2 = {0};
    if (sscanf(tanggal1, "%d-%d-%d", &tm1.tm_year, &tm1.tm_mon, &tm1.tm_mday) != 3 ||
        sscanf(tanggal2, "%d-%d-%d", &tm2.tm_year, &tm2.tm_mon, &tm2.tm_mday) != 3) {
        printf("Error: Gagal parsing tanggal.\n");
        return -1;
    }
    
    tm1.tm_year -= 1900;  // tm_year adalah tahun sejak 1900
    tm1.tm_mon -= 1;      // tm_mon adalah 0-11
    tm2.tm_year -= 1900;
    tm2.tm_mon -= 1;
    
    time_t time1 = mktime(&tm1);
    time_t time2 = mktime(&tm2);
    if (time1 == -1 || time2 == -1) {
        printf("Error: Tanggal invalid (misalnya, hari > 31 atau bulan > 12).\n");
        return -1;
    }
    double diff = difftime(time2, time1) / (60 * 60 * 24);  // Selisih dalam hari
    return (int)diff;
}

// Fungsi untuk menghitung denda (diperbaiki dengan pengecekan selisih)
int hitung_denda(char *tanggal_peminjaman, char *tanggal_pengembalian, int denda_per_hari) {
    int selisih = hitung_selisih_hari(tanggal_peminjaman, tanggal_pengembalian);
    if (selisih < 0) {
        printf("Error: Tanggal pengembalian lebih awal dari peminjaman atau parsing gagal.\n");
        return 0;
    }
    if (selisih > 7) {  // Asumsi batas 7 hari tanpa denda
        return (selisih - 7) * denda_per_hari;
    }
    return 0;
}

