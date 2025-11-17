#ifndef DENDA_H
#define DENDA_H

int hitung_selisih_hari(const char *tanggal1, const char *tanggal2);

int hitung_denda(const char *tanggal_peminjaman,
                 const char *tanggal_pengembalian,
                 int denda_per_hari);

int baca_setting_denda();
int baca_setting_max_durasi();

#endif