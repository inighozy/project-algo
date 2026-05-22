#include <iostream>
#include <iomanip>
using namespace std;

struct handphone{
    string merk;
    string tipe;
    int harga;
    int stok;
};

struct node{
    handphone hp;
    node *next;
    node *prev;
};

node *head = NULL;

void loadList(){
    head = NULL;
    FILE *dt = fopen("sewa.txt","r");
    if(dt==NULL){
        return;
    }
    char merk[100], tipe[100];
    int harga, stok;
    while(fscanf(dt,"%[^\n]\n%[^\n]\n%d\n%d\n",
        merk, tipe, &harga, &stok)!=EOF){
        node *baru = new node;
        
        baru->hp.merk = merk;
        baru->hp.tipe = tipe;
        baru->hp.harga = harga;
        baru->hp.stok = stok;

        baru->next = NULL;
        baru->prev = NULL;

        if(head==NULL){
            head = baru;
        }else{
            node *temp = head;
            
            while(temp->next!=NULL){
                temp = temp->next;
            }
            temp->next = baru;
            baru->prev = temp;
        }
    }
    fclose(dt);
}

void simpanFile(){
    FILE *dt = fopen("sewa.txt","w");
    node *temp = head;
    while(temp!=NULL){

        fprintf(dt,"%s\n%s\n%d\n%d\n",
            temp->hp.merk.c_str(),
            temp->hp.tipe.c_str(),
            temp->hp.harga,
            temp->hp.stok);

        temp = temp->next;
    }
    fclose(dt);
}

void tambah(){
    FILE *dt = fopen("sewa.txt","a");
    if(dt==NULL){
        cout<<"File error\n";
        return;
    }
    int n;
    cout<<"Jumlah data handphone : ";
    cin>>n;
    cin.ignore();

    for(int i=0;i<n;i++){
        string merk, tipe;
        int harga, stok;
        cout<<"\nData handphone ke-"<<i+1<<endl;
        
        cout<<"Merk  : ";
        getline(cin,merk);

        cout<<"Tipe  : ";
        getline(cin,tipe);

        cout<<"Harga : ";
        cin>>harga;

        cout<<"Stok  : ";
        cin>>stok;

        cin.ignore();

        fprintf( dt,"%s\n%s\n%d\n%d\n",
            merk.c_str(), tipe.c_str(), harga, stok );
    }
    fclose(dt);
    cout<<"\nData handphone berhasil ditambah\n";
}

void tampil(){
    loadList();
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }
    
    int pilih;
    cout<<"\n1. Harga Sewa Termurah";
    cout<<"\n2. Harga Sewa Termahal";
    cout<<"\nPilih : ";
    cin>>pilih;
    
    if (pilih != 1 && pilih != 2) {
        cout << "\nPilihan tidak valid!\n";
        return;
    }

    for(node *i=head;i!=NULL;i=i->next){
        for(node *j=i->next;j!=NULL;j=j->next){
            if((pilih==1 && i->hp.harga > j->hp.harga) || (pilih==2 && i->hp.harga < j->hp.harga)){
                handphone temp = i->hp;
                i->hp = j->hp;
                j->hp = temp;
            }
        }
    }

    cout<<"\n====================================================================\n";
    cout<<left
        <<setw(5)<<"No"
        <<setw(15)<<"Merk"
        <<setw(20)<<"Tipe"
        <<setw(15)<<"Harga"
        <<setw(10)<<"Stok"<<endl;
    cout<<"====================================================================\n";

    int no = 1;
    node *temp = head;
    while(temp!=NULL){
        cout<<setw(5)<<no++
            <<setw(15)<<temp->hp.merk
            <<setw(20)<<temp->hp.tipe
            <<setw(15)<<("Rp " + to_string(temp->hp.harga))
            <<setw(10)<<temp->hp.stok
            <<endl;
        temp = temp->next;
    }
    cout<<"====================================================================\n";
}

void cariHP(){
    loadList();
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }

    int pilih;
    cout<<"\n===== CARI HP =====\n";
    cout<<"1. Cari berdasarkan merk\n";
    cout<<"2. Cari berdasarkan tipe\n";
    cout<<"Pilih : ";
    cin>>pilih;
    
    if (pilih != 1 && pilih != 2) {
        cout << "\nPilihan tidak valid!\n";
        return;
    }
    cin.ignore();
    string cari;
    if(pilih==1){
        cout<<"Masukkan merk : ";
    }else{
        cout<<"Masukkan tipe : ";
    }
    getline(cin,cari);

    bool ketemu = false;
    node *temp = head;

    cout<<"\n====================================================================\n";
    cout<<left
        <<setw(5)<<"No"
        <<setw(15)<<"Merk"
        <<setw(20)<<"Tipe"
        <<setw(15)<<"Harga"
        <<setw(10)<<"Stok"<<endl;
    cout<<"====================================================================\n";

    int no = 1;
    while(temp!=NULL){
        if((pilih==1 && temp->hp.merk == cari) || (pilih==2 && temp->hp.tipe == cari)){
            ketemu = true;
            cout<<setw(5)<<no++
                <<setw(15)<<temp->hp.merk
                <<setw(20)<<temp->hp.tipe
                <<setw(15)<<("Rp " + to_string(temp->hp.harga))
                <<setw(10)<<temp->hp.stok
                <<endl;
        }
        temp = temp->next;
    }
    cout<<"====================================================================\n";

    if(!ketemu){
        cout<<"Data tidak ditemukan\n";
    }
}

void hapusData(){
    loadList();
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }
    cin.ignore();
    string cari;

    cout<<"Masukkan tipe HP yang ingin dihapus : ";
    getline(cin,cari);

    node *hapus = head;
    bool ketemu = false;

    while(hapus!=NULL){
        if(hapus->hp.tipe == cari){
            ketemu = true;
            
            if(hapus == head){
                head = head->next;
                
                if(head!=NULL){
                    head->prev = NULL;
                }
            }else{
                if(hapus->prev!=NULL){
                    hapus->prev->next = hapus->next;
                }
                if(hapus->next!=NULL){
                    hapus->next->prev = hapus->prev;
                }
            }
            delete hapus;
            break;
        }
        hapus = hapus->next;
    }
    
    if(!ketemu){
        cout<<"Data tidak ditemukan\n";
        return;
    }
    simpanFile();
    cout<<"Data berhasil dihapus\n";
}

void sewa(){
    loadList();
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }
    cin.ignore();
    string penyewa, cari;

    cout<<"Nama Penyewa : ";
    getline(cin,penyewa);

    cout<<"Tipe Hp      : ";
    getline(cin,cari);

    node *temp = head;
    bool ketemu = false;
    while(temp!=NULL){
        if(temp->hp.tipe == cari && temp->hp.stok > 0){
            temp->hp.stok--;
            ketemu = true;

            int lama;
            cout<<"Lama sewa (hari)    : ";
            cin>>lama;
            int total = temp->hp.harga * lama;

            FILE *p = fopen("penyewa.txt","a");
            if(p!=NULL){
                fprintf(p,"%s\n%s\n%s\n%d\n%d\n\n",
                    penyewa.c_str(), temp->hp.merk.c_str(), temp->hp.tipe.c_str(), lama, total);
					fclose(p);
            }

            FILE *r = fopen("riwayat.txt","a");
            if(r!=NULL){
                fprintf(r,"%s\n%s\n%s\n%d\n%d\n\n",
                    penyewa.c_str(), temp->hp.merk.c_str(), temp->hp.tipe.c_str(), lama, total);
					fclose(r);
            }
            simpanFile();
            cout<<"\n===== STRUK =====\n";
            cout<<"Nama  : "<<penyewa<<endl;
            cout<<"HP    : "<<temp->hp.merk<<" "<<temp->hp.tipe<<endl;
            cout<<"Total : Rp "<<total<<endl;

            break;
        }
        temp = temp->next;
    }

    if(!ketemu){
        cout<<"HP tidak ditemukan / stok habis\n";
    }
}

void pengembalian(){
    loadList();
    if(head==NULL){
        cout<<"Data kosong\n";
        return;
    }

    cin.ignore();
    string cari;
    cout<<"Tipe HP yang dikembalikan : ";
    getline(cin,cari);

    node *temp = head;
    bool ketemu = false;
    while(temp!=NULL){
        if(temp->hp.tipe == cari){
            temp->hp.stok++;
            ketemu = true;
            break;
        }
        temp = temp->next;
    }

    if(!ketemu){
        cout<<"Data HP tidak ditemukan\n";
        return;
    }
    simpanFile();

    FILE *p = fopen("penyewa.txt","r");
    FILE *tmp = fopen("temp.txt","w");

    if(p!=NULL && tmp!=NULL){
        char nama[100], merk[100], tipe[100];
        int lama, total;
        while(fscanf(p,"%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n\n",
            nama,merk,tipe,&lama,&total)!=EOF){
            if(string(tipe) != cari){
                fprintf(tmp,"%s\n%s\n%s\n%d\n%d\n\n",
                    nama, merk, tipe, lama, total);
            }
        }
        fclose(p);
        fclose(tmp);

        remove("penyewa.txt");
        rename("temp.txt","penyewa.txt");
    }
    cout<<"Pengembalian berhasil\n";
}

void tampilPenyewa(){
    FILE *p = fopen("penyewa.txt","r");
    if(p==NULL){
        cout<<"Belum ada data penyewa\n";
        return;
    }

    char nama[100], merk[100], tipe[100];
    int lama, total;

    cout<<"\n===== DATA PENYEWA AKTIF =====\n";

    while(fscanf(p,"%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n\n",
        nama,merk,tipe,&lama,&total)!=EOF){

        cout<<"Nama  : "<<nama<<endl;
        cout<<"HP    : "<<merk<<" "<<tipe<<endl;
        cout<<"Hari  : "<<lama<<endl;
        cout<<"Total : Rp "<<total<<endl;

        cout<<"--------------------------\n";
    }
    fclose(p);
}

void tampilRiwayat(){
    FILE *r = fopen("riwayat.txt","r");
    if(r==NULL){
        cout<<"Belum ada riwayat\n";
        return;
    }

    char nama[100], merk[100], tipe[100];
    int lama, total;

    cout<<"\n===== RIWAYAT TRANSAKSI =====\n";

    while(fscanf(r,"%[^\n]\n%[^\n]\n%[^\n]\n%d\n%d\n\n",
        nama,merk,tipe,&lama,&total)!=EOF){

        cout<<"Nama  : "<<nama<<endl;
        cout<<"HP    : "<<merk<<" "<<tipe<<endl;
        cout<<"Hari  : "<<lama<<endl;
        cout<<"Total : Rp "<<total<<endl;

        cout<<"--------------------------\n";
    }
    fclose(r);
}

int main(){
    int menu;
    do{
        cout<<"\n===== SULE RENTAL HP =====\n";
        cout<<"1. Tambah Data Handphone\n";
        cout<<"2. Tampilkan Data Handphone\n";
        cout<<"3. Cari Handphone\n";
        cout<<"4. Hapus Data Handphone\n";
        cout<<"5. Sewa Handphone\n";
        cout<<"6. Pengembalian Handphone\n";
        cout<<"7. Data Penyewa\n";
        cout<<"8. Riwayat Transaksi\n";
        cout<<"9. Keluar\n";

        cout<<"Pilih : ";
        cin>>menu;

        switch(menu){
            case 1:
                tambah();
                break;
            case 2:
                tampil();
                break;
            case 3:
                cariHP();
                break;
            case 4:
                hapusData();
                break;
            case 5:
                sewa();
                break;
            case 6:
                pengembalian();
                break;
            case 7:
                tampilPenyewa();
                break;
            case 8:
                tampilRiwayat();
                break;
        }
    }while(menu!=9);
    return 0;
}
