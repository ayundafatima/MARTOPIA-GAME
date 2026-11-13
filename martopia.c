
#include <stdio.h>
// WARNA TAMPILAN MARTOPIA
#define RESET   "\033[0m"
#define BOLD    "\033[1m"
#define CYAN    "\033[36m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define WHITE   "\033[37m"

struct Produk {
    char kode[10];
    char nama[30];
    int harga;
    int stok;
};

struct Produk produk[5] = {
    {"P001", "Indomie", 3500, 50},
    {"P002", "Aqua 600ml", 4000, 40},
    {"P003", "Chitato", 10000, 30},
    {"P004", "SilverQueen", 15000, 20},
    {"P005", "Roti", 8000, 25}
};
int skor = 0;
int level = 1;

// Deklarasi fungsi
void cekLevel();
void tampilLevel();
void tampilProduk();
void cekStok();
void tambahStok();
void transaksi();

// Menampilkan daftar produk
void tampilProduk() {
    int i;

    printf("\n========== DAFTAR PRODUK ==========\n");
    printf("%-8s %-18s %-10s %-8s\n",
           "KODE", "NAMA", "HARGA", "STOK");

    for (i = 0; i < 5; i++) {
        printf("%-8s %-18s Rp%-8d %-8d\n",
               produk[i].kode,
               produk[i].nama,
               produk[i].harga,
               produk[i].stok);
    }

    printf("===================================\n");
}

// Menampilkan stok barang
void cekStok() {
    int i;

    printf("\n========== STOK MARTOPIA ==========\n");

    for (i = 0; i < 5; i++) {
        printf("%-18s : %d barang\n",
               produk[i].nama, produk[i].stok);
    }

    printf("===================================\n");
}

// Sistem transaksi kasir
void transaksi() {
    int keranjang[5] = {0};
    int i, jumlah, total = 0;
    int pembayaran, kembalian;
    int indeks;
    char kode[10];

    printf("\n========== TRANSAKSI MARTOPIA ==========\n");

    tampilProduk();

    printf("\nMasukkan kode produk.");
    printf("\nKetik 0 jika selesai memilih barang.\n");

    while (1) {
        printf("\nKode produk: ");
        scanf("%9s", kode);

        if (kode[0] == '0' && kode[1] == '\0') {
            break;
        }

        indeks = -1;

        // Mencari produk berdasarkan kode
        for (i = 0; i < 5; i++) {
            int cocok = 1;
            int j = 0;

            while (produk[i].kode[j] != '\0' ||
                   kode[j] != '\0') {

                if (produk[i].kode[j] != kode[j]) {
                    cocok = 0;
                    break;
                }

                j++;
            }

            if (cocok) {
                indeks = i;
                break;
            }
        }

        if (indeks == -1) {
            printf("Kode produk tidak ditemukan!\n");
            continue;
        }

        printf("Nama barang: %s\n", produk[indeks].nama);
        printf("Harga: Rp%d\n", produk[indeks].harga);

        printf("Jumlah beli: ");
        scanf("%d", &jumlah);

        if (jumlah <= 0) {
            printf("Jumlah harus lebih dari 0!\n");
            continue;
        }

        if (jumlah + keranjang[indeks] >
            produk[indeks].stok) {
            printf("Stok barang tidak mencukupi!\n");
            continue;
        }

        keranjang[indeks] += jumlah;

        printf("Barang berhasil ditambahkan!\n");
    }

    // Menghitung total belanja
    for (i = 0; i < 5; i++) {
        total += keranjang[i] * produk[i].harga;
    }

    if (total == 0) {
        printf("\nTidak ada barang yang dibeli.\n");
        return;
    }

    // Menampilkan struk sementara
    printf("\n========== RINCIAN BELANJA ==========\n");

    for (i = 0; i < 5; i++) {
        if (keranjang[i] > 0) {
            printf("%-18s x%d = Rp%d\n",
                   produk[i].nama,
                   keranjang[i],
                   keranjang[i] * produk[i].harga);
        }
    }

    printf("-------------------------------------\n");
    printf("TOTAL BELANJA : Rp%d\n", total);

    // Proses pembayaran
    do {
        printf("Uang pembayaran: Rp");
        scanf("%d", &pembayaran);

        if (pembayaran < total) {
            printf("Uang kurang! Silakan bayar kembali.\n");
        }

    } while (pembayaran < total);

    kembalian = pembayaran - total;
    skor += 10;
    cekLevel();

    printf("Skor bertambah 10 poin!\n");

    // Mengurangi stok setelah pembayaran berhasil
    for (i = 0; i < 5; i++) {
        produk[i].stok -= keranjang[i];
    }

    printf("\n========== STRUK MARTOPIA ==========\n");
    printf("Total belanja : Rp%d\n", total);
    printf("Pembayaran    : Rp%d\n", pembayaran);
    printf("Kembalian     : Rp%d\n", kembalian);
    printf("====================================\n");
    printf("Terima kasih sudah berbelanja!\n");
    
}

void tambahStok() {
    int pilihan, jumlah;

    printf("\n========== TAMBAH STOK ==========\n");

    for (int i = 0; i < 5; i++) {
        printf("%d. %-18s Stok: %d\n",
               i + 1, produk[i].nama, produk[i].stok);
    }

    printf("\nPilih nomor barang: ");
    scanf("%d", &pilihan);

    if (pilihan < 1 || pilihan > 5) {
        printf("Pilihan barang tidak tersedia!\n");
        return;
    }

    printf("Jumlah stok tambahan: ");
    scanf("%d", &jumlah);

    if (jumlah <= 0) {
        printf("Jumlah harus lebih dari 0!\n");
        return;
    }

    produk[pilihan - 1].stok += jumlah;

    printf("\nStok berhasil ditambahkan!\n");
    printf("Nama barang: %s\n",
           produk[pilihan - 1].nama);
    printf("Stok sekarang: %d barang\n",
           produk[pilihan - 1].stok);
}

void cekLevel() {

    int levelLama = level;

    if (skor >= 500) {
        level = 4;
    }
    else if (skor >= 250) {
        level = 3;
    }
    else if (skor >= 100) {
        level = 2;
    }
    else {
        level = 1;
    }

    if (level > levelLama) {
        printf("\nSELAMAT! LEVEL BERHASIL DITINGKATKAN!\n");
    }

}

void tampilLevel() {

    printf("\n========== STATUS PERMAINAN ==========\n");

    printf("Skor pemain : %d\n", skor);
    printf("Level       : %d\n", level);

    if (level == 1) {
        printf("Jabatan     : Kasir Pemula\n");
    }
    else if (level == 2) {
        printf("Jabatan     : Kasir Profesional\n");
    }
    else if (level == 3) {
        printf("Jabatan     : Manajer Minimarket\n");
    }
    else {
        printf("Jabatan     : Pemilik Minimarket\n");
    }

    printf("======================================\n");
}

void tampilHeader() {

    printf(CYAN BOLD);
    printf("\n");
    printf("============================================\n");
    printf("                 MARTOPIA                   \n");
    printf("          MINI MARKET SIMULATION            \n");
    printf("============================================\n");
    printf(RESET);

    printf(YELLOW " LEVEL : %d", level);
    printf("       SKOR : %d POIN\n" RESET, skor);

    printf(GREEN " STATUS : ACTIVE\n" RESET);

    printf("--------------------------------------------\n");
}
int main() {
    int pilihan;

    do {
        printf("\n====================================\n");
        printf("              MARTOPIA              \n");
        printf("       MINI MARKET SIMULATION       \n");
        printf("====================================\n");

      
        printf("\033[2J\033[H");

tampilHeader();

        printf(CYAN BOLD "\n              MAIN MENU\n" RESET);

        printf(WHITE "  [1] " GREEN "Mulai Transaksi\n" RESET);
        printf(WHITE "  [2] " "Daftar Produk\n");
        printf(WHITE "  [3] " "Cek Stok Barang\n");
        printf(WHITE "  [4] " "Tambah Stok Barang\n");
        printf(WHITE "  [5] " YELLOW "Status Skor dan Level\n" RESET);
        printf(WHITE "  [6] " "Petunjuk Permainan\n");
        printf(WHITE "  [7] " RED "Keluar\n" RESET);

        printf(CYAN "\n--------------------------------------------\n" RESET);

        printf(YELLOW "Masukkan pilihan: " RESET);
        scanf("%d", &pilihan);

        switch (pilihan) {

    case 1:
        transaksi();
        break;

    case 2:
        tampilProduk();
        break;

    case 3:
        cekStok();
        break;

    case 4:
        tambahStok();
        break;

    case 5:
        tampilLevel();
        break;

    case 6:
        printf("\nLayani pelanggan dengan benar!\n");
        printf("Selesaikan transaksi untuk mendapatkan skor.\n");
        break;

    case 7:
        printf("\nTerima kasih sudah bermain Martopia!\n");
        break;

    default:
        printf("\nPilihan tidak tersedia!\n");
}

    } while (pilihan != 7);

    return 0;
}
