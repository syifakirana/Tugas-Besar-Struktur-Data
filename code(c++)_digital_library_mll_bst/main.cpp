
#include <iostream>
#include "library.h"
using namespace std;

// --- FUNGSI MENU TAMPILAN ---
void menuUtama() {
    cout << "\n===== MENU UTAMA =====\n";
    cout << "1. Katalog Buku (BST)\n";
    cout << "2. Peminjaman Anggota (MLL)\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}

void menuBST() {
    cout << "\n===== MENU BST =====\n";
    cout << "1. Tambah Buku\n";
    cout << "2. Cari Buku (ISBN)\n";
    cout << "3. Update Buku\n";
    cout << "4. Hapus Buku\n";
    cout << "5. Tampilkan Data Buku\n";
    cout << "6. Cari Buku by Tag Topik\n";
    cout << "7. Hitung Total Buku\n";
    cout << "8. Pengolahan Tahun Terbit\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
}

void menuTraversal() {
    cout << "\n--- TAMPILKAN DATA BUKU ---\n";
    cout << "1. Inorder\n";
    cout << "2. Preorder\n";
    cout << "3. Postorder\n";
    cout << "4. Level Order\n";
    cout << "0. Kembali\n";
    cout << "Pilih: ";
}

// -- HELPER INPUT BUKU --
Buku inputBuku() {
    Buku b;

    cout << "ISBN          : ";
    getline(cin, b.isbn);

    cout << "Judul         : ";
    getline(cin, b.judul);

    cout << "Penulis       : ";
    getline(cin, b.penulis);

    cout << "Tahun Terbit  : ";
    cin >> b.tahunTerbit;
    cin.ignore();

    cout << "Masukkan 5 Tag Topik:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Tag ke-" << i + 1 << ": ";
        getline(cin, b.tag_topik[i]);
    }

    return b;
}

// --- PROGRAM UTAMA (MAIN) ---
int main() {
    Node* root;
    initBST(root);


    int pilihUtama;
    do {
        menuUtama();
        cin >> pilihUtama;
        cin.ignore();

        // ======== BAGIAN Menu BST ========
        if (pilihUtama == 1) {
            int pilihBST;
            do {
                menuBST();
                cin >> pilihBST;
                cin.ignore();

                if (pilihBST == 1) {
                    Buku b = inputBuku();
                    if (insertBuku(root, b))
                        cout << "Buku berhasil ditambahkan.\n";
                    else
                        cout << "ISBN sudah terdaftar.\n";
                }
                else if (pilihBST == 2) {
                    string isbn;
                    cout << "Masukkan ISBN: ";
                    getline(cin, isbn);
                    Node* p = searchISBN(root, isbn);
                    if (p)
                        cout << "Ditemukan: " << p->data.judul << endl;
                    else
                        cout << "Buku tidak ditemukan.\n";
                }
                else if (pilihBST == 3) {
                    string isbn;
                    cout << "ISBN buku: ";
                    getline(cin, isbn);
                    if (updateBuku(root, isbn))
                        cout << "Update berhasil.\n";
                    else
                        cout << "Buku tidak ditemukan.\n";
                }
                else if (pilihBST == 4) {
                    string isbn;
                    cout << "ISBN buku: ";
                    getline(cin, isbn);
                    if (deleteBuku(root, isbn))
                        cout << "Buku berhasil dihapus.\n";
                    else
                        cout << "Buku tidak ditemukan.\n";
                }
                else if (pilihBST == 5) {
                    int t;
                    do {
                        menuTraversal();
                        cin >> t;
                        cin.ignore();

                        if (t == 1) inorder(root);
                        else if (t == 2) preorder(root);
                        else if (t == 3) postorder(root);
                        else if (t == 4) levelOrder(root);

                    } while (t != 0);
                }
                else if (pilihBST == 6) {
                    string tag;
                    cout << "Masukkan Tag Topik: ";
                    getline(cin, tag);
                    searchByTag(root, tag);
                }
                else if (pilihBST == 7) {
                    cout << "Total Buku: " << countBuku(root) << endl;
                }
                else if (pilihBST == 8) {
                    cout << "Tahun Terlama : " << minTahun(root) << endl;
                    cout << "Tahun Terbaru : " << maxTahun(root) << endl;
                    cout << "Rata-rata     : " << avgTahun(root) << endl;
                }

            } while (pilihBST != 0);
        }

        // ======== BAGIAN MENU MLL ========
        else if (pilihUtama == 2) {
            cout << "\n[Menu MLL belum diimplementasikan]\n";
            cout << "Dikerjakan oleh anggota lain.\n";
        }

    } while (pilihUtama != 0);

    cout << "Program selesai.\n";
    return 0;
}
