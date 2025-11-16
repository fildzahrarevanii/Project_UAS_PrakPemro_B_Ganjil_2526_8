// login
// login pustakawan: baca FILE_LOGIN (username password per baris)

#include "perpustakaan.h"

int login_pustakawan() {
    ensure_data_files_exist();
    char user[64], pass[64];

    printf("=== LOGIN PUSTAKAWAN ===\n");
    printf("Username: ");
    scanf("%63s", user);
    printf("Password: ");
    scanf("%63s", pass);

    FILE *fp = fopen(FILE_LOGIN, "r");
    if (!fp) {
        printf("File login tidak ditemukan.\n");
        return 0;
    }

    char u[64], p[64];
    while (fscanf(fp, "%63s %63s", u, p) == 2) {
        if (strcmp(u, user) == 0 && strcmp(p, pass) == 0) {
            fclose(fp);
            printf("Login berhasil. Selamat bekerja, %s!\n", user);
            return 1;
        }
    }

    fclose(fp);
    printf("Username/Password salah.\n");
    return 0;
}
