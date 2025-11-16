// buku.c
// Implementasi CRUD, pencarian, dan kategori untuk buku
// Semua fungsi membaca dan menulis ke FILE_BUKU (data/buku.txt)

#include "perpustakaan.h"

// Prototipe fungsi helper internal
static int dapatkan_id_buku_baru(void);
static void cetak_header_buku(void);
static void cetak_data_buku(buku b);

// Fungsi untuk mendapatkan ID unik baru (ID terakhir + 1)
static int dapatkan_id_buku_baru(void) {
    FILE *file = fopen(FILE_BUKU, "r");
    if (!file) {
        return 1; // File belum ada, ID pertama adalah 1
    }

    buku b;
    int id_terakhir = 0;
    char line[512];

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            if (b.id > id_terakhir) {
                id_terakhir = b.id;
            }
        }
    }
    fclose(file);
    return id_terakhir + 1;
}

// Fungsi untuk mencetak header tabel buku
static void cetak_header_buku(void) {
    printf("+----+--------------------------------+----------------------+------------------+-----------+\n");
    printf("| ID | Judul                          | Penulis              | Kategori         | Tersedia  |\n");
    printf("+----+--------------------------------+----------------------+------------------+-----------+\n");
}

// Fungsi untuk mencetak satu baris data buku
static void cetak_data_buku(buku b) {
    printf("| %-2d | %-30s | %-20s | %-16s | %-9s |\n",
           b.id, b.judul, b.penulis, b.kategori, b.tersedia ? "Ya" : "Tidak");
}

// --- Implementasi Fungsi CRUD ---

// 1. TAMBAH BUKU
void tambah_buku(void) {
    buku b;
    clear_screen();
    printf("=== TAMBAH BUKU BARU ===\n");

    b.id = dapatkan_id_buku_baru();
    
    printf("Judul: ");
    scanf(" %[^\n]", b.judul);
    printf("Penulis: ");
    scanf(" %[^\n]", b.penulis);
    printf("Kategori (Fiksi, Non-Fiksi, Komik, dll): ");
    scanf(" %[^\n]", b.kategori);
    
    b.tersedia = 1;       // Buku baru pasti tersedia
    b.jumlah_dipinjam = 0; // Buku baru belum pernah dipinjam

    FILE *file = fopen(FILE_BUKU, "a");
    if (!file) {
        printf("Error: Gagal membuka file %s\n", FILE_BUKU);
        return;
    }

    // Format: id|judul|penulis|kategori|tersedia|jumlah_dipinjam
    fprintf(file, "%d|%s|%s|%s|%d|%d\n",
            b.id, b.judul, b.penulis, b.kategori, b.tersedia, b.jumlah_dipinjam);
    
    fclose(file);
    printf("\nBuku '%s' (ID: %d) berhasil ditambahkan!\n", b.judul, b.id);
}

// 2. TAMPILKAN SEMUA BUKU
void tampilkan_daftar_buku(void) {
    FILE *file = fopen(FILE_BUKU, "r");
    if (!file) {
        printf("Error: Gagal membuka file %s. Mungkin belum ada buku.\n", FILE_BUKU);
        return;
    }

    buku b;
    char line[512];
    int count = 0;

    clear_screen();
    printf("=== DAFTAR SEMUA BUKU ===\n");
    cetak_header_buku();

    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            cetak_data_buku(b);
            count++;
        }
    }
    printf("+----+--------------------------------+----------------------+------------------+-----------+\n");
    
    if (count == 0) {
        printf("Tidak ada data buku.\n");
    }
    fclose(file);
}

// 3. EDIT BUKU
void edit_buku(void) {
    int id_edit;
    int found = 0;
    buku b;
    char line[512];

    clear_screen();
    printf("=== EDIT DATA BUKU ===\n");
    printf("Masukkan ID buku yang akan diedit: ");
    scanf("%d", &id_edit);
    getchar(); // clear newline buffer

    FILE *file_asli = fopen(FILE_BUKU, "r");
    FILE *file_temp = fopen("temp_buku.txt", "w");

    if (!file_asli || !file_temp) {
        printf("Error: Gagal memproses file.\n");
        if(file_asli) fclose(file_asli);
        if(file_temp) fclose(file_temp);
        return;
    }

    while (fgets(line, sizeof(line), file_asli)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            
            if (b.id == id_edit) {
                found = 1;
                printf("Buku ditemukan: %s - %s\n", b.judul, b.penulis);
                printf("Masukkan Judul baru (lama: %s): ", b.judul);
                scanf(" %[^\n]", b.judul);
                printf("Masukkan Penulis baru (lama: %s): ", b.penulis);
                scanf(" %[^\n]", b.penulis);
                printf("Masukkan Kategori baru (lama: %s): ", b.kategori);
                scanf(" %[^\n]", b.kategori);
                
                // Tulis data yang sudah diubah ke file temp
                fprintf(file_temp, "%d|%s|%s|%s|%d|%d\n",
                        b.id, b.judul, b.penulis, b.kategori, b.tersedia, b.jumlah_dipinjam);
                printf("Buku (ID: %d) berhasil diperbarui.\n", b.id);
            } else {
                // Tulis data lama ke file temp
                fprintf(file_temp, "%s", line);
            }
        }
    }

    fclose(file_asli);
    fclose(file_temp);

    remove(FILE_BUKU);
    rename("temp_buku.txt", FILE_BUKU);

    if (!found) {
        printf("Error: Buku dengan ID %d tidak ditemukan.\n", id_edit);
    }
}

// 4. HAPUS BUKU
void hapus_buku(void) {
    int id_hapus;
    int found = 0;
    buku b;
    char line[512];
    char judul_terhapus[100];

    clear_screen();
    printf("=== HAPUS BUKU ===\n");
    printf("Masukkan ID buku yang akan dihapus: ");
    scanf("%d", &id_hapus);
    getchar(); // clear newline buffer

    FILE *file_asli = fopen(FILE_BUKU, "r");
    FILE *file_temp = fopen("temp_buku.txt", "w");

    if (!file_asli || !file_temp) {
        printf("Error: Gagal memproses file.\n");
        if(file_asli) fclose(file_asli);
        if(file_temp) fclose(file_temp);
        return;
    }

    while (fgets(line, sizeof(line), file_asli)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            
            if (b.id == id_hapus) {
                found = 1;
                strcpy(judul_terhapus, b.judul);
                // Jangan tulis (skip) baris ini ke file temp
            } else {
                // Tulis data lain ke file temp
                fprintf(file_temp, "%s", line);
            }
        }
    }

    fclose(file_asli);
    fclose(file_temp);

    remove(FILE_BUKU);
    rename("temp_buku.txt", FILE_BUKU);

    if (found) {
        printf("Buku '%s' (ID: %d) berhasil dihapus.\n", judul_terhapus, id_hapus);
    } else {
        printf("Error: Buku dengan ID %d tidak ditemukan.\n", id_hapus);
    }
}


// --- Implementasi Fitur Tambahan ---

// 5. CARI BUKU (berdasarkan judul)
void cari_buku(void) {
    char judul_cari[100];
    int found = 0;
    buku b;
    char line[512];

    clear_screen();
    printf("=== CARI BUKU (BERDASARKAN JUDUL) ===\n");
    printf("Masukkan judul/kata kunci: ");
    scanf(" %[^\n]", judul_cari);

    FILE *file = fopen(FILE_BUKU, "r");
    if (!file) {
        printf("Error: Gagal membuka file %s.\n", FILE_BUKU);
        return;
    }

    cetak_header_buku();
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            
            // strstr mencari substring (case-sensitive)
            // ubah judul_cari dan b.judul ke strlwr() jika ingin case-insensitive
            if (strstr(b.judul, judul_cari)) {
                cetak_data_buku(b);
                found++;
            }
        }
    }
    printf("+----+--------------------------------+----------------------+------------------+-----------+\n");

    if (found == 0) {
        printf("Tidak ada buku yang ditemukan dengan judul '%s'.\n", judul_cari);
    } else {
        printf("Ditemukan %d buku.\n", found);
    }
    fclose(file);
}

// 6. KATEGORIKAN BUKU (Tampilkan berdasarkan kategori)
void kategorikan_buku(void) {
    char kategori_cari[30];
    int found = 0;
    buku b;
    char line[512];

    clear_screen();
    printf("=== TAMPILKAN BUKU BERDASARKAN KATEGORI ===\n");
    printf("Masukkan kategori (Fiksi, Non-Fiksi, Komik, dll): ");
    scanf(" %[^\n]", kategori_cari);

    FILE *file = fopen(FILE_BUKU, "r");
    if (!file) {
        printf("Error: Gagal membuka file %s.\n", FILE_BUKU);
        return;
    }

    printf("\nMenampilkan buku untuk kategori: %s\n", kategori_cari);
    cetak_header_buku();
    while (fgets(line, sizeof(line), file)) {
        if (sscanf(line, "%d|%99[^|]|%99[^|]|%29[^|]|%d|%d",
                   &b.id, b.judul, b.penulis, b.kategori, &b.tersedia, &b.jumlah_dipinjam) == 6) {
            
            // strcmp membandingkan string (case-sensitive)
            if (strcmp(b.kategori, kategori_cari) == 0) {
                cetak_data_buku(b);
                found++;
            }
        }
    }
    printf("+----+--------------------------------+----------------------+------------------+-----------+\n");

    if (found == 0) {
        printf("Tidak ada buku yang ditemukan untuk kategori '%s'.\n", kategori_cari);
    } else {
        printf("Ditemukan %d buku.\n", found);
    }
    fclose(file);
}
