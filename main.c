#include "perpustakaan.h"

int main(void){
    ensure_data_files_exist();

    clear_screen();
    printf("=== SISTEM PERPUSTAKAAN MINI ===\n");

    if(!login_pustakawan()){
        printf("Login gagal. Program keluar.\n");
        pause_screen();
        return 0;
    }

    tampilkan_menu_utama();

    return 0;
}