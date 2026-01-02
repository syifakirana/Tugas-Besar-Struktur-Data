#include <iostream>
#include "library.h"
using namespace std;

// ---- FUNGSI MENU TAMPILAN ----
void menuUtama() {
    cout << "\n===== MENU UTAMA =====\n";
    cout << "1. Katalog Buku (BST)\n";
    cout << "2. Peminjaman Anggota (MLL)\n";
    cout << "0. Keluar\n";
    cout << "Pilih: ";
}
// -- Bagian Menu BST --
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

void menuMLL() {
    cout << "\n===== MENU PEMINJAMAN (MLL) =====\n";
    cout << "--- Create / Insert ---\n";
    cout << "1. Registrasi Member (Insert Last - Standard)\n";
    cout << "2. Registrasi VIP (Insert First - Testing)\n";
    cout << "3. Registrasi Sisipan (Insert After - Testing)\n";
    cout << "--- Read & Delete ---\n";
    cout << "4. Tampilkan Semua Data\n";
    cout << "5. Cari Member\n";
    cout << "6. Hapus Member by ID (Delete Specific)\n";
    cout << "7. Hapus Member Awal (Delete First)\n";
    cout << "8. Hapus Member Akhir (Delete Last)\n";
    cout << "--- Peminjaman (Child) ---\n";
    cout << "9. PINJAM BUKU (Integrasi BST)\n";
    cout << "10. KEMBALIKAN BUKU\n";
    cout << "--- Statistik (Challenge) ---\n";
    cout << "11. Statistik Aktivitas Member (Min/Max)\n";
    cout << "12. Filter Jumlah Pinjaman\n";
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
// -- HELPER INPUT MEMBER --
Member inputMember() {
    Member m;
    cout << "ID Member : "; getline(cin, m.idMember);
    cout << "Nama      : "; getline(cin, m.nama);
    cout << "No Telp   : "; getline(cin, m.noTelp);
    return m;
}

// --- PROGRAM UTAMA (MAIN) ---
int main() {
    Node* root;
    initBST(root);

    // Inisialisasi MLL
    ListMLL L;
    createListMLL(L);

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
            int pilihMLL;
            do {
                menuMLL();
                cin >> pilihMLL;
                cin.ignore();

                if (pilihMLL == 1) { // Insert Last 
                    cout << "--- Registrasi Member (Last) ---\n";
                    Member m = inputMember();
                    if (searchMember(L, m.idMember) == NULL) {
                        insertLastMember(L, alokasiMember(m));
                        cout << "Member berhasil didaftarkan.\n";
                    } else cout << "ERROR: ID Member sudah terdaftar!\n";
                }
                else if (pilihMLL == 2) { // Insert First
                    cout << "--- Registrasi VIP (First) ---\n";
                    Member m = inputMember();
                    if (searchMember(L, m.idMember) == NULL) {
                        insertFirstMember(L, alokasiMember(m)); // TESTING INSERT FIRST
                        cout << "Member VIP berhasil didaftarkan di urutan awal.\n";
                    } else cout << "Eror: ID Member sudah terdaftar!\n";
                }
                else if (pilihMLL == 3) { // Insert After
                    cout << "--- Registrasi Sisipan (After) ---\n";
                    string idPrec;
                    cout << "Masukkan ID Member Sebelumnya (Predecessor): "; getline(cin, idPrec);
                    adrMember prec = searchMember(L, idPrec);
                    if (prec != NULL) {
                        Member m = inputMember();
                        if (searchMember(L, m.idMember) == NULL) {
                            insertAfterMember(L, prec, alokasiMember(m)); // TESTING INSERT AFTER
                            cout << "Member berhasil disisipkan setelah " << prec->info.nama << ".\n";
                        } else cout << "ERROR: ID Member sudah terdaftar!\n";
                    } else cout << "ERROR: ID Predecessor tidak ditemukan.\n";
                }
                else if (pilihMLL == 4) { // Show All
                    showAllData(L);
                }
                else if (pilihMLL == 5) { // Cari Member
                    string id;
                    cout << "Masukkan ID Member: "; getline(cin, id);
                    adrMember P = searchMember(L, id);
                    if (P) cout << "Ditemukan: " << P->info.nama << " - " << P->info.noTelp << endl;
                    else cout << "Member tidak ditemukan.\n";
                }
                else if (pilihMLL == 6) { // Hapus Member by ID
                    string id;
                    cout << "Masukkan ID Member dihapus: "; getline(cin, id);
                    deleteMemberByID(L, id);
                }
                else if (pilihMLL == 7) { // Delete First
                    adrMember P;
                    deleteFirstMember(L, P); // TESTING DELETE FIRST
                    if(P) cout << "Member urutan pertama berhasil dihapus.\n";
                    else cout << "List kosong.\n";
                }
                else if (pilihMLL == 8) { // Delete Last
                    adrMember P;
                    deleteLastMember(L, P); // TESTING DELETE LAST
                    if(P) cout << "Member urutan terakhir berhasil dihapus.\n";
                    else cout << "List kosong.\n";
                }
                else if (pilihMLL == 9) { // PINJAM BUKU (INTEGRASI)
                    string id, judul, tgl;
                    cout << "ID Member   : "; getline(cin, id);
                    
                    adrMember M = searchMember(L, id);
                    if (M == NULL) {
                        cout << "ERROR: Member tidak ditemukan.\n";
                    } else {
                        cout << "Judul Buku  : "; getline(cin, judul);
                        
                        // Validasi BST
                        if (searchJudul(root, judul) == NULL) {
                            cout << "ERROR: Buku tidak terdaftar di Katalog Perpustakaan.\n";
                        } else {
                            if (!isBookBorrowed(M, judul)) {
                                cout << "Tanggal Pinjam: "; getline(cin, tgl);
                                insertPinjaman(L, id, alokasiPinjam(judul, tgl));
                                cout << "Berhasil meminjam buku.\n";
                            } else {
                                cout << "ERROR: Member sedang meminjam buku ini.\n";
                            }
                        }
                    }
                }
                else if (pilihMLL == 10) { // Kembalikan Buku
                    string id, judul;
                    cout << "ID Member   : "; getline(cin, id);
                    cout << "Judul Buku  : "; getline(cin, judul);
                    deletePinjaman(L, id, judul);
                }
                else if (pilihMLL == 11) { // Statistik Min Max
                    showMostActiveMember(L);
                    showLeastActiveMember(L);
                }
                else if (pilihMLL == 12) { // Filter
                    int x;
                    cout << "Tampilkan member dengan jumlah pinjaman: "; cin >> x;
                    showMembersWithXLoans(L, x);
                }
            } while (pilihMLL != 0);
        }

    } while (pilihUtama != 0);

    cout << "Program selesai.\n";
    return 0;
}
