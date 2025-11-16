// fungsi untuk membuka file dan memastikan folder data & file default ada

#include "perpustakaan.h"

void ensure_data_files_exist(void){
    FILE *f;

    // login.txt default
    f = fopen(FILE_LOGIN, "r");
    if(!f){
        f = fopen(FILE_LOGIN, "w");
        if(f){
            fprintf(f, "admin admin\n");
            fclose(f);
            printf("(INFO) File login.txt dibuat dengan user default: admin/admin\n");
        }
    } else{
        fclose(f);
    }

    // setting.txt default
    f = fopen(FILE_SETTING, "r");
    if(!f){
        f = fopen(FILE_SETTING, "w");
        if(f){
            fprintf(f, "MAX_HARI_PINJAM=7\n");
            fprintf(f, "DENDA_PER_HARI=1000\n");
            fclose(f);
            printf("(INFO) File setting.txt dibuat dengan nilai default.\n");
        }
    } else{
        fclose(f);
    }

    f = fopen(FILE_BUKU, "a");
    if(f) fclose(f);

    // DIHAPUS: Blok f = fopen(FILE_ANGGOTA, "a");

    f = fopen(FILE_PINJAMAN, "a");
    if(f) fclose(f);
}
