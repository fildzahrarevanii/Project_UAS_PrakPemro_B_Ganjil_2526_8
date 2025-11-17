#include "perpustakaan.h"

void tampilkan_menu_utama() {
    int pilihan;

    while (1) {
        clear_screen();
        printf("=== MENU UTAMA ===\n");
        printf("1. Kelola Buku\n");
        printf("2. Kelola Anggota\n");
        printf("3. Peminjaman / Pengembalian\n");
        printf("4. Keluar\n");
        printf("Pilih menu: ");

        pilihan = read_int_safe();

        switch (pilihan) {
            case 1:
                tampilkan_sub_menu_buku();
                break;

            case 2:
                tampilkan_sub_menu_anggota();
                break;

            case 3:
                tampilkan_sub_menu_peminjaman();
                break;

            case 4:
                printf("Keluar dari program...\n");
                return;

            default:
                printf("Pilihan tidak valid!\n");
                pause_screen();
        }
    }
}

void tampilkan_sub_menu_buku() {
    int p;
    while (1) {
        clear_screen();
        printf("=== MENU BUKU ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Edit Buku\n");
        printf("3. Hapus Buku\n");
        printf("4. Lihat Daftar Buku\n");
        printf("5. Cari Buku\n");
        printf("6. Kembali\n");
        printf("Pilih menu: ");

        p = read_int_safe();

        switch (p) {
            case 1: tambah_buku(); break;
            case 2: edit_buku(); break;
            case 3: hapus_buku(); break;
            case 4: tampilkan_daftar_buku(); break;
            case 5: cari_buku(); break;
            case 6: return;
            default: printf("Pilihan tidak valid!\n"); pause_screen();
        }
    }
}

void tampilkan_sub_menu_anggota() {
    int p;
    while (1) {
        clear_screen();
        printf("=== MENU ANGGOTA ===\n");
        printf("1. Tambah Anggota\n");
        printf("2. Edit Anggota\n");
        printf("3. Hapus Anggota\n");
        printf("4. Lihat Daftar Anggota\n");
        printf("5. Kembali\n");
        printf("Pilih menu: ");

        p = read_int_safe();

        switch (p) {
            case 1: tambah_anggota(); break;
            case 2: edit_anggota(); break;
            case 3: hapus_anggota(); break;
            case 4: tampilkan_daftar_anggota(); break;
            case 5: return;
            default: printf("Pilihan tidak valid!\n"); pause_screen();
        }
    }
}

void tampilkan_sub_menu_peminjaman() {
    int p;
    while (1) {
        clear_screen();
        printf("=== MENU PEMINJAMAN ===\n");
        printf("1. Pinjam Buku\n");
        printf("2. Kembalikan Buku\n");
        printf("3. Riwayat Peminjaman\n");
        printf("4. Kembali\n");
        printf("Pilih menu: ");

        p = read_int_safe();

        switch (p) {
            case 1: pinjam_buku(); break;
            case 2: kembalikan_buku(); break;
            case 3: tampilkan_riwayat_peminjaman(); break;
            case 4: return;
            default: printf("Pilihan tidak valid!\n"); pause_screen();
        }
    }
}