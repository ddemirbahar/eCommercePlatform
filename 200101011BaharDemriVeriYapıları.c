#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Kullanici bilgisi icin struct yapisi
struct musteri {
    char ad[50];
    char soyad[50];
    char eposta[100];
    struct musteri *next;
};

// HEAD & TAIL (listenin basini ve sonunu belirtmek icin)
struct musteri *head = NULL;
struct musteri *tail = NULL;

// Ürün bilgisi
struct urun {
    int urunID;
    char urunAdi[50];
    float urunFiyati;
    char kategori[20];
    struct urun *sol;
    struct urun *sag;
};

// Kuyruk yapısı
struct Queue {
    struct urun *front; // Kuyruğun başı
    struct urun *rear;  // Kuyruğun sonu
    float toplamTutar;  // Toplam sepet tutari
};

// Sepet yapısı
struct Sepet {
    struct Queue kuyruk; // Ürünleri tutmak
    
};

// Kuyruğu başlat
void initQueue(struct Queue *q) {
    q->front = q->rear = NULL;
    q-> toplamTutar = 0.0; // Baslangic toplam tutari sifir
}

// Kuyruğa ürün ekle
void enqueue(struct Queue *q, struct urun *urun) {
    struct urun *newUrun = (struct urun *)malloc(sizeof(struct urun));
    newUrun->urunID = urun->urunID;
    strcpy(newUrun->urunAdi, urun->urunAdi);
    newUrun->urunFiyati = urun->urunFiyati;
    strcpy(newUrun->kategori, urun->kategori);
    newUrun->sol = newUrun->sag = NULL;
    q-> toplamTutar += urun -> urunFiyati;

    if (q->rear == NULL) {
        q->front = q->rear = newUrun;
    } else {
        q->rear->sag = newUrun;
        q->rear = newUrun;
    }
}

// Kuyruktan ürün çıkar
void dequeue(struct Queue *q) {
    if (q->front == NULL) {
        printf("Hata: Kuyruk bos.\n");
        return;
    }

    struct urun *temp = q->front;
    q->front = q->front->sag;

    if (q->front == NULL) {
        q->rear = NULL;
    }

    free(temp);
}

// Sepeti yazdır
void printSepet(struct Queue *q) {
    printf("Sepet:\n");
    struct urun *current = q->front;
    while (current != NULL) {
        printf("Urun ID: %d, Urun Adi: %s, Urun Fiyati: %.2f, Kategori: %s\n", current->urunID, current->urunAdi, current->urunFiyati, current->kategori);
        current = current->sag;
    }
    printf("Sepet Tutari: %.2f\n\n", q-> toplamTutar);
}

// Ağacı inorder gezerek ürünleri yazdır
void inOrderYazdir(struct urun *root) {
    if (root != NULL) {
        inOrderYazdir(root->sol);
        printf("Urun ID: %d, Urun Adi: %s, Urun Fiyati: %.2f, Kategori: %s\n", root->urunID, root->urunAdi, root->urunFiyati, root->kategori);
        inOrderYazdir(root->sag);
    }
}

// Ağaca ürün ekle
struct urun *urunEkle(struct urun *root, int urunID, const char urunAdi[], float urunFiyati, const char kategori[]) {
    if (root == NULL) {
        struct urun *yeniUrun = (struct urun *)malloc(sizeof(struct urun));
        yeniUrun->urunID = urunID;
        strcpy(yeniUrun->urunAdi, urunAdi);
        yeniUrun->urunFiyati = urunFiyati;
        strcpy(yeniUrun->kategori, kategori);
        yeniUrun->sol = yeniUrun->sag = NULL;
        return yeniUrun;
    }

    if (urunID < root->urunID) {
        root->sol = urunEkle(root->sol, urunID, urunAdi, urunFiyati, kategori);
    } else if (urunID > root->urunID) {
        root->sag = urunEkle(root->sag, urunID, urunAdi, urunFiyati, kategori);
    } else {
        printf("Hata: Ayni urunID'ye sahip baska bir urun zaten var. Urun eklenemedi.\n");
    }
    return root;
}

// Ağaçta ürün ara
struct urun *urunAra(struct urun *root, int urunID) {
    while (root != NULL) {
        if (urunID == root->urunID) {
            return root;
        } else if (urunID < root->urunID) {
            root = root->sol;
        } else {
            root = root->sag;
        }
    }
    return NULL;
}
// Yeni musteri ekler (listenin sonuna)
char addMusteri(char ad[], char soyad[], char eposta[]) {
    // linked list bos ise
    if (head == NULL) {
        struct musteri *new = (struct musteri *)malloc(sizeof(struct musteri));
        strcpy(new->ad, ad);
        strcpy(new->soyad, soyad);
        strcpy(new->eposta, eposta);
        new->next = NULL;
        head = tail = new;
    }
    // linked dolu ise (yeni musteriyi listenin sonuna ekler)
    else {
        struct musteri *new = (struct musteri *)malloc(sizeof(struct musteri));
        strcpy(new->ad, ad);
        strcpy(new->soyad, soyad);
        strcpy(new->eposta, eposta);
        new->next = NULL;

        tail->next = new;
        tail = new;
    }

    return 1;
}
// listenin basina ekler
char addMusteriHead(char ad[], char soyad[], char eposta[]) {
    // Linked list bos ise
    if (head == NULL) {
        struct musteri *new = (struct musteri *)malloc(sizeof(struct musteri));
        strcpy(new->ad, ad);
        strcpy(new->soyad, soyad);
        strcpy(new->eposta, eposta);
        new->next = NULL;
        head = tail = new;
    }
    // linked list dolu ise
    else {
        struct musteri *new = (struct musteri *)malloc(sizeof(struct musteri));
        strcpy(new->ad, ad);
        strcpy(new->soyad, soyad);
        strcpy(new->eposta, eposta);
        new->next = head;
        head = new;
    }
}

// listeyi yazdirir
char print() {
    printf("MUSTERI LISTESI \n");
    struct musteri *current = head;
    while (current != NULL) {
        printf("Ad: %s , Soyad: %s , Eposta: %s \n ", current->ad, current->soyad, current->eposta);
        current = current->next;
    }
    printf("\n");
    return 1;
}

// Dugum silme
int musteriSil(char ad[], char soyad[], char eposta[]) {
    struct musteri *prev = NULL;
    struct musteri *current = head;

    // linked list bos ise
    if (head == NULL) {
        printf("Musteri yok!");
        return 1;
    }

    // HEAD
    if (strcmp(head->ad, ad) == 0 && strcmp(head->soyad, soyad) == 0 && strcmp(head->eposta, eposta) == 0) {
        struct musteri *t = head;
        head = head->next;
        free(t);
        return 1;
    }

    while (current != NULL && (strcmp(current->ad, ad) != 0 || strcmp(current->soyad, soyad) != 0 || strcmp(current->eposta, eposta) != 0)) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Musteri bulunamadi.\n");
        return 1;
    }

    prev->next = current->next;

    // Eger silinen dugum, tail (kuyruk) ise tail'i guncelle
    if (tail == current) {
        tail = prev;
    }

    free(current);
    return 1;
}

int main() {
   
    // Musteri islemleri
    addMusteri("Bahar", "Demir", "bahardemir421@gmail.com");
    addMusteri("Ismail", "Aydin", "ismailaydin@example.com");
    addMusteri("oktay", "demir", "oktay@example.com");
    addMusteri("leyla", "demir", "leyla@example.com");
    print();
    addMusteriHead("ayse", "demir", "aysedemir@example.com");
    print();
    musteriSil("Ismail", "Aydin", "ismailaydin@example.com");
    musteriSil("Bahar", "Demir", "bahardemir421@gmail.com");
    print();
   
   
    struct Sepet sepet;
    initQueue(&sepet.kuyruk);

    // Ağaca ürünleri ekle
    struct urun *agac = NULL;
    agac = urunEkle(agac, 100, "Laptop", 2500.0, "Akilli Cihazlar");
    agac = urunEkle(agac, 101, "Telefon", 1500.0, "Akilli Cihazlar");
    agac = urunEkle(agac, 102, "Tablet", 1800.0, "Akilli Cihazlar");
    agac = urunEkle(agac, 103, "Kulaklik", 1000.0, "Akilli Cihazlar");
    agac = urunEkle(agac, 200, "Camasir Makinesi", 15000.0, "Ev Aletleri");
    agac = urunEkle(agac, 201, "Bulasik Makinesi", 17000.0, "Ev Aletleri");
    agac = urunEkle(agac, 202, "Tost Makinesi", 8000.0, "Ev Aletleri");
    agac = urunEkle(agac, 203, "Supurge", 12000.0, "Ev Aletleri");


    // Ağacı yazdır
    printf("Teknolojik Urunler: \n");
    inOrderYazdir(agac);

    // Kullanıcıdan ürün ID al
    int urunID;
    printf("Urun ID: ");
    scanf("%d", &urunID);

    // Ağaçta bu ürünü ara
    struct urun *secilenUrun = urunAra(agac, urunID);

    // Eğer ürün bulunduysa, sepete ekle ve sepeti yazdır
    if (secilenUrun != NULL) {
        enqueue(&sepet.kuyruk, secilenUrun);
        printSepet(&sepet.kuyruk);
    } else {
        printf("Hata: Belirtilen ID'ye sahip urun bulunamadi.\n");
    }

    // Birkaç kez ürün ekleme işlemi yapalım
    while (1) {
        printf("Urun ID (0 cikis icin): ");
        scanf("%d", &urunID);

        // Kullanıcı çıkış yapmak istiyorsa döngüden çık
        if (urunID == 0) {
            break;
        }

        // Ağaçta bu ürünü ara
        secilenUrun = urunAra(agac, urunID);

        // Eğer ürün bulunduysa, sepete ekle ve sepeti yazdır
        if (secilenUrun != NULL) {
            enqueue(&sepet.kuyruk, secilenUrun);
            printSepet(&sepet.kuyruk);
        } else {
            printf("Hata: Belirtilen ID'ye sahip urun bulunamadi.\n");
        }
    }

    printSepet(&sepet.kuyruk);
    return 0;
}
