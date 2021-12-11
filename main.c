#include <stdio.h>
#include <stdlib.h>

//yapılar

struct inis_sirasi{
    int ucak_id;
    unsigned short oncelik_id;
    unsigned short inis_saati;
    struct inis_sirasi * sonraki;
};

struct kalkis_sirasi{
    int ucak_id;
    unsigned short oncelik_id;
    unsigned short kalkis_saati;
    struct kalkis_sirasi * sonraki;
};

struct input_degerleri{
    unsigned short oncelik_id;
    int ucak_id;
    unsigned short talep_inis_saati;
};

//global değişkenler

struct input_degerleri * deger = NULL;

struct inis_sirasi * inis_ilk = NULL;
struct inis_sirasi * inis_son = NULL;
int inis_uzunluk = 0;
struct kalkis_sirasi * kalkis_ilk = NULL;
struct kalkis_sirasi * kalkis_son = NULL;
int kalkis_uzunluk = 0;

//fonkisyonlar

void input_oku(){
    int i = 0;
    deger = (struct input_degerleri *)malloc(sizeof(struct input_degerleri));

    FILE * fp;
    fp = fopen("input.txt", "r");

    while(fscanf(fp, "%hu %d %hu\n", &(deger+i)->oncelik_id, &(deger+i)->ucak_id, &(deger+i)->talep_inis_saati) != EOF){
        i++;
        deger = (struct input_degerleri *)realloc(deger, sizeof(struct input_degerleri) * (i+1));
    }

    //input.txt dosyasından okunan değerlerin, talep edilen iniş saatine göre sıralanması
    int n = sizeof(deger);
    struct input_degerleri temp;
    for(int j = 0; j < n-1; j++){
        for(int k = 0; k < n-1-j; k++){
            if(deger[k].talep_inis_saati > deger[k+1].talep_inis_saati){
                temp = deger[k+1]; deger[k+1] = deger[k]; deger[k] = temp;
            }
        }
    }

    fclose(fp);
}

void enqueue_inis(int index){
    //input_oku();
    struct inis_sirasi * yeni = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));

    //input dosyasının ilgili satırından okunan değerleri sıranın yeni elemanına atar.
    yeni->oncelik_id = (deger+index)->oncelik_id;
    yeni->ucak_id = (deger+index)->ucak_id;
    yeni->inis_saati = (deger+index)->talep_inis_saati;

    if(inis_ilk == NULL){
        //eğer sıranın ilk elemanı boş ise, yeni eklenen eleman hem ilk hem de son elemandır.
        inis_ilk = yeni;
        inis_son = yeni;
        inis_ilk->sonraki = inis_son;
    }
    else{
        //sıraya öncelik gözetilerek ekleme yapılır.
        struct inis_sirasi * counter = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
        counter = inis_ilk;     //sıranın en ön elemanından başlayarak, yeni elemanın ekleneceği yeri bulmak için, sayar.
        int idx = 0;            //yeni elemanın ekleneceği yeri belirtir.
        int i = 0;
        int oncelik = 0;        //eklenecek elemanın önceliğinin düşük olması sebebiyle sıranın sonundan başka bir yere eklenip eklenmeyeceğini belirtir.
        do{
            if((deger+index)->talep_inis_saati == counter->inis_saati){
                if(yeni->oncelik_id < counter->oncelik_id){
                    oncelik = 1;
                    idx = i;
                    break;
                }
            }
            counter = counter->sonraki;
            i++;
        }while(counter != inis_son);

        counter = inis_ilk;
        if(oncelik != 0){
            for(int k = 0; k < idx-1; k++)
                counter = counter->sonraki;
            if(inis_ilk == inis_son && counter == inis_ilk){            
                inis_ilk = yeni;
                yeni->sonraki = counter;
                counter->sonraki = NULL;
                inis_son = counter;
            }
            else if(counter == inis_ilk){
                yeni->sonraki = counter;
                inis_ilk = yeni;
            }
            else{
                yeni->sonraki = counter->sonraki;
                counter->sonraki = yeni;
            }
        }
        else{
            inis_son->sonraki = yeni;
            inis_son = yeni;
        }
        inis_uzunluk++;
    }
}

struct inis_sirasi * pull_inis(){
    struct inis_sirasi * t = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
    t = inis_ilk;
    inis_ilk = inis_ilk->sonraki;
    inis_uzunluk--;
    return t;
}

int main(){
    input_oku();
    for(int i = 0; i < 8; i++){
        printf("%hu %d %hu\n", deger[i].oncelik_id, deger[i].ucak_id, deger[i].talep_inis_saati);
        enqueue_inis(i);
    }
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    return 0;
}