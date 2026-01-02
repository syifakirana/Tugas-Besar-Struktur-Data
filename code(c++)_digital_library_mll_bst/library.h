#ifndef LIBRARY_H
#define LIBRARY_H

#include <iostream>
#include <string>
using namespace std;

// ================================================================
// ================ BAGIAN BST (KATALOG BUKU) =====================
// ================================================================

struct Buku {
    string isbn;
    string judul;
    string penulis;
    int tahunTerbit;
    string tag_topik[5];
};

struct Node {
    Buku data;
    Node* left;
    Node* right;
};

// --- Primitif BST (CRUD) --
void initBST(Node*& root);
bool insertBuku(Node*& root, Buku b);
Node* searchISBN(Node* root, string isbn);
bool updateBuku(Node* root, string isbn);
bool deleteBuku(Node*& root, string isbn);

// Traversal pada BST --
void inorder(Node* root);
void preorder(Node* root);
void postorder(Node* root);
void levelOrder(Node* root);

// -- Fitur Tambahan dan Challenge --
void searchByTag(Node* root, string tag);
int countBuku(Node* root);
int minTahun(Node* root);
int maxTahun(Node* root);
float avgTahun(Node* root);

// ===================================================================
// ================ BAGIAN MLL (Peminjaman Buku) =====================
// ===================================================================

// -- Definisi Struktur MLL --

// -- child elemen (Buku yang dipinjam)
struct  Peminjaman {
    string judulBuku;
    string tglPinjam;
};
typedef struct ElmPinjam *adrPinjam;
struct ElmPinjam {
    Peminjaman info;
    adrPinjam next;
};

// -- Parent Element (Member Perpus)
struct Member {
    string idMember; // key Parent
    string nama;
    string noTelp;
};
typedef struct ElmMember *adrMember;
struct ElmMember {
    Member info;
    adrMember next; // pointer ke member selanjutnya
    adrPinjam firstPinjam; // pointer ke child
};

// -- list MLL
struct ListMLL {
    adrMember first;
};

// --- Primitif MLL ---
// Dasar MLL 
void createListMLL(ListMLL &L);
bool isEmptyMLL(ListMLL L);
adrMember alokasiMember(Member data);
adrPinjam alokasiPinjam(string judul, string tgl);
void dealokasiMember(adrMember &P);
void dealokasiPinjam(adrPinjam &P);

// Operasi CRUD Parent (Member)
// -- insert
void insertFirstMember(ListMLL &L, adrMember P);
void insertLastMember(ListMLL &L, adrMember P);
void insertAfterMember(ListMLL &L, adrMember prec, adrMember P);
// -- delete
void deleteFirstMember(ListMLL &L, adrMember &P);
void deleteLastMember(ListMLL &L, adrMember &P);
void deleteMemberByID(ListMLL &L, string idMember);
// -- search
adrMember searchMember(ListMLL L, string idMember);

// Operasi Crud Child (Peminjaman)
void insertPinjaman(ListMLL &L, string idMember, adrPinjam C);
void deletePinjaman(ListMLL &L, string idMember, string judulBuku);

// CHALLENGE
// -- apakah buku sedang dipinjam oleh member tertentu
bool isBookBorrowed(adrMember P, string judulBuku);
// -- tampilkan seluruh data (parent beserta child)
void showAllData(ListMLL L);
// -- tampilkan member yang paling aktif dan sedikit aktif
void showMostActiveMember(ListMLL L);
void showLeastActiveMember(ListMLL L);
// -- filter jumlah (menampilkan member dengan jumlah pinjaman tertentu)
void showMembersWithXLoans(ListMLL L, int x);
// -- mencari pinjaman berdasarkan judul buku
Node* searchJudul(Node* root, string judul);

#endif
