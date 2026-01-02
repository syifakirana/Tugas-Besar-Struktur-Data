#include "library.h"

// ===========================================================
// ================ IMPLEMENTASI FUNGSI BST ==================
// ===========================================================

void initBST(Node*& root) {
    root = NULL;
}

Node* newNode(Buku b) {
    Node* p = new Node;
    p->data = b;
    p->left = p->right = NULL;
    return p;
}

bool insertBuku(Node*& root, Buku b) {
    if (root == NULL) {
        root = newNode(b);
        return true;
    }
    if (b.isbn == root->data.isbn) return false;
    if (b.isbn < root->data.isbn)
        return insertBuku(root->left, b);
    else
        return insertBuku(root->right, b);
}

Node* searchISBN(Node* root, string isbn) {
    if (root == NULL || root->data.isbn == isbn)
        return root;
    if (isbn < root->data.isbn)
        return searchISBN(root->left, isbn);
    return searchISBN(root->right, isbn);
}

bool updateBuku(Node* root, string isbn) {
    Node* p = searchISBN(root, isbn);
    if (!p) return false;

    cout << "Judul baru   : ";
    getline(cin, p->data.judul);
    cout << "Penulis baru : ";
    getline(cin, p->data.penulis);
    cout << "Tahun terbit : ";
    cin >> p->data.tahunTerbit;
    cin.ignore();

    cout << "Masukkan 5 tag topik:\n";
    for (int i = 0; i < 5; i++) {
        cout << "Tag ke-" << i + 1 << ": ";
        getline(cin, p->data.tag_topik[i]);
    }
    return true;
}

Node* minNode(Node* root) {
    while (root->left) root = root->left;
    return root;
}

bool deleteBuku(Node*& root, string isbn) {
    if (!root) return false;

    if (isbn < root->data.isbn)
        return deleteBuku(root->left, isbn);
    else if (isbn > root->data.isbn)
        return deleteBuku(root->right, isbn);
    else {
        if (!root->left && !root->right) {
            delete root;
            root = NULL;
        } else if (!root->left) {
            Node* t = root;
            root = root->right;
            delete t;
        } else if (!root->right) {
            Node* t = root;
            root = root->left;
            delete t;
        } else {
            Node* t = minNode(root->right);
            root->data = t->data;
            deleteBuku(root->right, t->data.isbn);
        }
        return true;
    }
}

void print(Node* p) {
    cout << p->data.isbn << " | " << p->data.judul << endl;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        print(root);
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root) {
        print(root);
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root) {
        postorder(root->left);
        postorder(root->right);
        print(root);
    }
}

void levelOrder(Node* root) {
    if (!root) return;
    Node* q[100];
    int f = 0, r = 0;
    q[r++] = root;

    while (f < r) {
        Node* p = q[f++];
        print(p);
        if (p->left) q[r++] = p->left;
        if (p->right) q[r++] = p->right;
    }
}

void searchByTag(Node* root, string tag) {
    if (!root) return;
    searchByTag(root->left, tag);

    for (int i = 0; i < 5; i++) {
        if (root->data.tag_topik[i] == tag) {
            print(root);
            break;
        }
    }
    searchByTag(root->right, tag);
}

int countBuku(Node* root) {
    if (!root) return 0;
    return 1 + countBuku(root->left) + countBuku(root->right);
}

int minTahun(Node* root) {
    if (!root) return 9999;
    int m = root->data.tahunTerbit;
    int l = minTahun(root->left);
    int r = minTahun(root->right);
    if (l < m) m = l;
    if (r < m) m = r;
    return m;
}

int maxTahun(Node* root) {
    if (!root) return 0;
    int m = root->data.tahunTerbit;
    int l = maxTahun(root->left);
    int r = maxTahun(root->right);
    if (l > m) m = l;
    if (r > m) m = r;
    return m;
}

void sumDanCount(Node* root, int &sum, int &cnt) {
    if (root != NULL) {
        sum += root->data.tahunTerbit;
        cnt++;
        sumDanCount(root->left, sum, cnt);
        sumDanCount(root->right, sum, cnt);
    }
}

float avgTahun(Node* root) {
    if (root == NULL) return 0;

    int sum = 0, cnt = 0;
    sumDanCount(root, sum, cnt);

    return (float) sum / cnt;
}

// ===================================================================
// ================= IMPLEMENTASI FUNGSI MLL =========================
// ===================================================================

// Dasar MLL
void createListMLL(ListMLL &L) {
    L.first = NULL;
}

bool isEmptyMLL(ListMLL L) {
    return L.first == NULL;
}

adrMember alokasiMember(Member data) {
    adrMember P = new ElmMember;
    P -> info = data;
    P -> next = NULL;
    P -> firstPinjam = NULL; // inisialisasi child kosong
    return P;
}

adrPinjam alokasiPinjam(string judul, string tgl) {
    adrPinjam P = new ElmPinjam;
    P -> info.judulBuku = judul;
    P -> info.tglPinjam = tgl;
    P -> next = NULL;
    return P;
}

void dealokasiMember(adrMember &P) {
    delete P;
    P = NULL;
}

void dealokasiPinjam(adrPinjam &P) {
    delete P;
    P = NULL;
}

// Operasi CRUD Parent (Member)
// -- insert
void insertFirstMember(ListMLL &L, adrMember P) {
    if (isEmptyMLL(L)) {
        L.first = P;
    } else {
        P -> next = L.first;
        L.first = P;
    }
}

void insertLastMember(ListMLL &L, adrMember P) {
    if (isEmptyMLL(L)) {
        L.first = P;
    } else {
        adrMember Q = L.first;
        while (Q -> next != NULL) {
            Q = Q -> next;
        }
        Q -> next = P;
    }
}

void insertAfterMember(ListMLL &L, adrMember prec, adrMember P) {
    if (prec != NULL) {
        P -> next = prec -> next;
        prec -> next = P;
    }
}

// -- delete member
void deleteFirstMember(ListMLL &L, adrMember &P) {
        if (!isEmptyMLL(L)) {
            P = L.first;
            L.first = L.first -> next;

            // hapus semua child
            adrPinjam C = P -> firstPinjam;
            while (C != NULL) {
                adrPinjam temp = C;
                C = C -> next;
                dealokasiPinjam(temp);
            }
            dealokasiMember(P);
        } else {
            P = NULL; // list kosong
        }
}

void deleteLastMember(ListMLL &L, adrMember &P) {
    if (!isEmptyMLL(L)) {
        // Jika hanya 1 elemen
        if (L.first -> next == NULL) {
            deleteFirstMember(L, P);
        } else {
            // cari elemen sebelum akhir
            adrMember Q = L.first;
            while (Q -> next -> next != NULL) {
                Q = Q -> next;
            }
            P = Q -> next;
            Q -> next = NULL;
            // hapus semua child 
            adrPinjam C = P -> firstPinjam;
            while (C != NULL) {
                adrPinjam temp = C;
                C = C -> next;
                dealokasiPinjam(temp);
            }
            dealokasiMember(P);
        }
    } else {
        P = NULL; // list kosong
    }
}

void deleteMemberByID(ListMLL &L, string idMember) {
    // Cari dulu posisi
    adrMember P = L.first;
    adrMember prec = NULL;

    while (P != NULL && P->info.idMember != idMember) {
        prec = P;
        P = P->next;
    }

    if (P != NULL) {
        if (prec == NULL)
            L.first = P->next;
        else
            prec->next = P->next;

        // hapus semua pinjaman
        adrPinjam C = P->firstPinjam;
        while (C != NULL) {
            adrPinjam temp = C;
            C = C->next;
            dealokasiPinjam(temp);
        }
        dealokasiMember(P);
        cout << "Member dengan ID " << idMember << " berhasil dihapus beserta semua pinjamannya(childnya)\n";
    } else {
        cout << "Member dengan ID " << idMember << " tidak ditemukan.\n";
    }
}
// -- search
adrMember searchMember(ListMLL L, string idMember) {
    adrMember P = L.first;
    while (P != NULL) {
        if (P -> info.idMember == idMember) {
            return P;
        }
        P = P -> next;
    }
    return NULL;
}

// Operasi Crud Child (Peminjaman)
void insertPinjaman(ListMLL &L, string idMember, adrPinjam C) {
    // gunakan konsep insertLast pada child agar urutan pinjaman terjaga
    adrMember P = searchMember(L, idMember);
    if (P != NULL) {
        if (P -> firstPinjam == NULL) {
            P -> firstPinjam = C;
        } else {
            adrPinjam Q = P -> firstPinjam;
            while (Q -> next != NULL) {
                Q = Q -> next;
            }
            Q -> next = C;
        }
    } else {
        cout << "Member tidak ditemukan, tidak dapat menambahkan pinjaman.\n";
    }
}
void deletePinjaman(ListMLL &L, string idMember, string judulBuku) {
    adrMember P = searchMember(L, idMember);
    if (P != NULL) {
        adrPinjam C = P -> firstPinjam;
        adrPinjam prec = NULL;

        // Cari buku di list child
        while (C != NULL && C->info.judulBuku != judulBuku) {
            prec = C;
            C = C->next;
        }

        if (C != NULL) { // Buku ketemu
            if (prec == NULL) {
                // Hapus buku pertama
                P->firstPinjam = C->next;
            } else {
                // Hapus buku di tengah/akhir
                prec->next = C->next;
            }
            dealokasiPinjam(C);
            cout << ">> Buku '" << judulBuku << "' berhasil dikembalikan.\n";
        } else {
            cout << ">> Buku tidak ditemukan di data peminjaman member ini.\n";
        }
    } else {
        cout << ">> Member tidak ditemukan.\n";
    }
}

// CHALLENGE
bool isBookBorrowed(adrMember P, string judulBuku) {
    if (P == NULL) {
        return false;
    }
    adrPinjam C = P -> firstPinjam;
    while (C != NULL) {
        if (C -> info.judulBuku == judulBuku) {
            return true;
        }
        C = C -> next;
    }
    return false;
}

void showAllData(ListMLL L) {
    if (isEmptyMLL(L)) {
        cout << ">> Data Kosong.\n";
        return;
    }
    adrMember P = L.first;
    int i = 1;
    while (P != NULL) {
        cout << i++ << ". [MEMBER] " << P -> info.nama << " (ID: " << P -> info.idMember << ")\n";
        
        adrPinjam C = P->firstPinjam;
        if (C == NULL) {
            cout << "    - Belum ada pinjaman.\n";
        } else {
            while (C != NULL) {
                cout << "    -> [PINJAM] " << C->info.judulBuku 
                     << " (Tgl: " << C -> info.tglPinjam << ")\n";
                C = C->next;
            }
        }
        cout << endl;
        P = P->next;
    }
}

// Helper hitung jumlah pinjaman
int countPinjaman(adrMember P) {
    int count = 0;
    adrPinjam C = P -> firstPinjam;
    while (C != NULL) {
        count++;
        C = C -> next;
    }
    return count;
}

void showMostActiveMember(ListMLL L) {
    if (isEmptyMLL(L)) {
        cout << "Data Kosong.\n";
        return;
    }
    adrMember P = L.first;
    adrMember MaxP = P;
    int maxCount = countPinjaman(P);

    while (P != NULL) {
        int currentCount = countPinjaman(P);
        if (currentCount > maxCount) {
            maxCount = currentCount;
            MaxP = P;
        }
        P = P->next;
    }

    cout << ">> Member Paling Aktif: " << MaxP->info.nama << " dengan " << maxCount << " buku.\n";

}

void showLeastActiveMember(ListMLL L) {
    if (isEmptyMLL(L)) return;

    adrMember P = L.first;
    adrMember MinP = P;
    int minCount = countPinjaman(P);

    while (P != NULL) {
        int currentCount = countPinjaman(P);
        if (currentCount < minCount) {
            minCount = currentCount;
            MinP = P;
        }
        P = P->next;
    }

    cout << ">> Member Paling Pasif: " << MinP->info.nama 
         << " dengan " << minCount << " buku.\n";
}

void showMembersWithXLoans(ListMLL L, int x) {
    cout << ">> Member dengan " << x << " buku pinjaman:\n";
    adrMember P = L.first;
    bool found = false;
    while (P != NULL) {
        if (countPinjaman(P) == x) {
            cout << "   - " << P->info.nama << endl;
            found = true;
        }
        P = P->next;
    }
    if (!found) cout << "   (Tidak ada)\n";
}

// Cari Buku by Judul (Untuk Validasi MLL)
Node* searchJudul(Node* root, string judul) {
    if (root == NULL) return NULL;
    
    if (root->data.judul == judul) {
        return root;
    }
    // Cari di kiri
    Node* res = searchJudul(root->left, judul);
    if (res != NULL) return res;
    // Cari di kanan
    return searchJudul(root->right, judul);
}
