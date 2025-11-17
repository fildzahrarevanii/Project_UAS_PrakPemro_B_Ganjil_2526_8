#include "perpustakaan.h"
#include <stdlib.h>

/* membersihkan buffer input */
void clear_input(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){
        // buang karakter sisa
    }
}

/* membersihkan layar */
void clear_screen(void){
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* pause */
void pause_screen(){
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}

/* membaca string aman */
void read_line(char *buffer, int size){
    if(fgets(buffer, size, stdin)){
        size_t len = strlen(buffer);
        if(len > 0 && buffer[len-1] == '\n'){
            buffer[len-1] = '\0';
        } else {
            clear_input();
        }
    }
}

/* membaca integer dengan validasi */
int read_int_safe(void){
    int angka;
    while(1){
        if(scanf("%d", &angka) == 1){
            clear_input();
            return angka;
        } else {
            printf("Input tidak valid. Masukkan angka: ");
            clear_input();
        }
    }
}

/* helper membaca setting */
static int get_setting_value(const char *key, int default_val){
    FILE *f = fopen(FILE_SETTING, "r");
    if(!f) return default_val;

    char line[100];
    char k[50];
    int v;

    while(fgets(line, sizeof(line), f)){
        if(sscanf(line, "%49[^=]=%d", k, &v) == 2){
            if(strcmp(k, key) == 0){
                fclose(f);
                return v;
            }
        }
    }

    fclose(f);
    return default_val;
}

/* nilai setting */
int get_max_hari_pinjam(void){
    return get_setting_value("MAX_HARI_PINJAM", 7);
}

int get_denda_per_hari(void){
    return get_setting_value("DENDA_PER_HARI", 1000);
}