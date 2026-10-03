#include <stdio.h>
#include <string.h>

#define MAKS_MAHASISWA 5
#define JUMLAH_MK 3

void inputData(char nama[][30], int nilai[][JUMLAH_MK], int jumlah);
float hitungRataRata(int nilai[][JUMLAH_MK], int index);
char tentukanGrade(float rata);
void tampilkanRapor(
    char nama[][30],
    int nilai[][JUMLAH_MK],
    float rataRata[],
    int jumlah
);
int nilaiTertinggi(int nilai[][JUMLAH_MK], int jumlah);
int nilaiTerendah(int nilai[][JUMLAH_MK], int jumlah);
int mahasiswaTerbaik(float rataRata[], int jumlah);
int cariMahasiswa(char nama[][30], int jumlah, char target[]);

int main() {
    char nama[MAKS_MAHASISWA][30];
    int nilai[MAKS_MAHASISWA][JUMLAH_MK];
    float rataRata[MAKS_MAHASISWA];
    int jumlah, i, idx;
    char target[30];

    printf("=============================================\n");
    printf("            SISTEM RAPOR DIGITAL\n");
    printf("=============================================\n");

    printf("Jumlah mahasiswa (1-%d): ", MAKS_MAHASISWA);
    scanf("%d", &jumlah);

    if (jumlah < 1 || jumlah > MAKS_MAHASISWA) {
        printf("Jumlah mahasiswa tidak valid!\n");
        return 0;
    }

    inputData(nama, nilai, jumlah);

    for (i = 0; i < jumlah; i++) {
        rataRata[i] = hitungRataRata(nilai, i);
    }

    tampilkanRapor(nama, nilai, rataRata, jumlah);

    /* ===== Tugas: statistik ===== */
    printf("\nNilai tertinggi   : %d\n", nilaiTertinggi(nilai, jumlah));
    printf("Nilai terendah    : %d\n", nilaiTerendah(nilai, jumlah));
    printf("Mahasiswa terbaik : %s\n", nama[mahasiswaTerbaik(rataRata, jumlah)]);

    /* ===== Tugas: pencarian ===== */
    printf("\nMasukkan nama yang dicari: ");
    scanf("%29s", target);

    idx = cariMahasiswa(nama, jumlah, target);
    if (idx == -1) {
        printf("Mahasiswa tidak ditemukan.\n");
    } else {
        printf("Nama      : %s\n", nama[idx]);
        printf("Rata-rata : %.2f\n", rataRata[idx]);
        printf("Grade     : %c\n", tentukanGrade(rataRata[idx]));
        printf("Status    : %s\n", rataRata[idx] >= 70 ? "LULUS" : "TIDAK LULUS");
    }

    return 0;
}

void inputData(char nama[][30], int nilai[][JUMLAH_MK], int jumlah) {
    int i, j;

    for (i = 0; i < jumlah; i++) {
        printf("\nMahasiswa ke-%d\n", i + 1);
        printf("Nama              : ");
        scanf("%29s", nama[i]);

        for (j = 0; j < JUMLAH_MK; j++) {
            if (j == 0) {
                printf("Nilai Algoritma   : ");
            } else if (j == 1) {
                printf("Nilai Pemrograman : ");
            } else {
                printf("Nilai Basis Data  : ");
            }
            scanf("%d", &nilai[i][j]);
        }
    }
}

float hitungRataRata(int nilai[][JUMLAH_MK], int index) {
    int j, total = 0;

    for (j = 0; j < JUMLAH_MK; j++) {
        total += nilai[index][j];
    }

    return (float) total / JUMLAH_MK;
}

char tentukanGrade(float rata) {
    if (rata >= 90) return 'A';
    else if (rata >= 80) return 'B';
    else if (rata >= 70) return 'C';
    else if (rata >= 60) return 'D';
    else return 'E';
}

void tampilkanRapor(
    char nama[][30],
    int nilai[][JUMLAH_MK],
    float rataRata[],
    int jumlah
) {
    int i, j;

    printf("\n===================================================\n");
    printf("                   RAPOR DIGITAL\n");
    printf("===================================================\n");
    printf("%-15s%-8s%-8s%-8s%-10s%-7s%-s\n",
           "Nama", "Alg", "Prog", "BD", "Rata-rata", "Grade", "Status");
    printf("---------------------------------------------------\n");

    for (i = 0; i < jumlah; i++) {
        printf("%-15s", nama[i]);

        for (j = 0; j < JUMLAH_MK; j++) {
            printf("%-8d", nilai[i][j]);
        }
        printf("%-10.2f%-7c", rataRata[i], tentukanGrade(rataRata[i]));

        if (rataRata[i] >= 70) {
            printf("%s", "LULUS");
        } else {
            printf("%s", "TIDAK LULUS");
        }
        printf("\n");
    }
    printf("===================================================\n");
}

int nilaiTertinggi(int nilai[][JUMLAH_MK], int jumlah) {
    int i, j, maks = nilai[0][0];

    for (i = 0; i < jumlah; i++) {
        for (j = 0; j < JUMLAH_MK; j++) {
            if (nilai[i][j] > maks) {
                maks = nilai[i][j];
            }
        }
    }
    return maks;
}

int nilaiTerendah(int nilai[][JUMLAH_MK], int jumlah) {
    int i, j, min = nilai[0][0];

    for (i = 0; i < jumlah; i++) {
        for (j = 0; j < JUMLAH_MK; j++) {
            if (nilai[i][j] < min) {
                min = nilai[i][j];
            }
        }
    }
    return min;
}

int mahasiswaTerbaik(float rataRata[], int jumlah) {
    int i, idxTerbaik = 0;

    for (i = 1; i < jumlah; i++) {
        if (rataRata[i] > rataRata[idxTerbaik]) {
            idxTerbaik = i;
        }
    }
    return idxTerbaik;
}

int cariMahasiswa(char nama[][30], int jumlah, char target[]) {
    int i;

    for (i = 0; i < jumlah; i++) {
        if (strcmp(nama[i], target) == 0) {
            return i;
        }
    }
    return -1;
}
