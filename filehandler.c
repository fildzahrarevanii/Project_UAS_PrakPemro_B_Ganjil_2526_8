#include "perpustakaan.h"
#ifdef _WIN32
#include <direct.h>
#else
#include <sys/stat.h>
#endif

/* membuat folder jika belum ada */
void buat_folder_data() {
#ifdef _WIN32
    _mkdir("data");
#else
    mkdir("data", 0777);
#endif
}

FILE* buka_file(const char *path, const char *mode) {
    FILE *f = fopen(path, mode);
    if (!f) {
        printf("ERROR: Tidak bisa membuka file %s\n", path);
        exit(1);
    }
    return f;
}

void ensure_data_files_exist(void) {

    buat_folder_data();   // PENTING: buat folder data/

    FILE *f;

    /* login.txt */
    f = fopen(FILE_LOGIN, "r");
    if (!f) {
        f = fopen(FILE_LOGIN, "w");
        if (f) {
            fprintf(f, "admin admin\n");
            printf("(INFO) login.txt dibuat: user=admin pass=admin\n");
            fclose(f);
        }
    } else fclose(f);

    /* setting.txt */
    f = fopen(FILE_SETTING, "r");
    if (!f) {
        f = fopen(FILE_SETTING, "w");
        if (f) {
            fprintf(f, "MAX_HARI_PINJAM=7\n");
            fprintf(f, "DENDA_PER_HARI=1000\n");
            printf("(INFO) setting.txt dibuat dengan nilai default.\n");
            fclose(f);
        }
    } else fclose(f);

    /* buku.txt */
    f = fopen(FILE_BUKU, "a");
    if (f) fclose(f);

    /* anggota.txt — WAJIB, karena header masih pakai FILE_ANGGOTA */
    f = fopen(FILE_ANGGOTA, "a");
    if (f) fclose(f);

    /* peminjaman.txt */
    f = fopen(FILE_PINJAMAN, "a");
    if (f) fclose(f);
}