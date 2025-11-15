#include "perpustakaan.h"

void clear_input(){
    int c;
    while((c = getchar()) != '\n' && c != EOF){
        // buang karakter sisa input
    }
}

void pause_screen(){
    printf("Tekan Enter untuk melanjutkan...");
    getchar();
}

static int get_setting_value(const char *key, int default_val){
    FILE *f = fopen(FILE_SETTING, "r");
    if(!f) return default_val;

    char line[100];
    char k[50];
    int v;

    while (fgets(line, sizeof(line), f)){
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

int get_max_hari_pinjam(void){
    return get_setting_value("MAX_HARI_PINJAM", 7);
}

int get_denda_per_hari(void){
    return get_setting_value("DENDA_PER_HARI", 1000);
}