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
struct kalkis_sirasi * kalkis_ilk = NULL;
struct kalkis_sirasi * kalkis_son = NULL;

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

    yeni->oncelik_id = (deger+index)->oncelik_id;
    yeni->ucak_id = (deger+index)->ucak_id;
    yeni->inis_saati = (deger+index)->talep_inis_saati;

    if(inis_ilk == NULL){
        inis_ilk = yeni;
        inis_son = yeni;
        inis_ilk->sonraki = inis_son;
    }
    else{
        struct inis_sirasi * counter = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
        struct inis_sirasi * temp = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
        counter = inis_ilk;
        int idx = 0;
        int i = 0;
        int oncelik = 0;
        do{
            //printf("%d %d\n", (deger+index)->talep_inis_saati, counter->inis_saati);
            if((deger+index)->talep_inis_saati == counter->inis_saati){
                //printf("%d %d\n", oncelik, counter->oncelik_id);
                if(yeni->oncelik_id < counter->oncelik_id){
                    //printf("za\n");
                    oncelik = 1;
                    idx = i;
                }
            }
            counter = counter->sonraki;
            i++;
        }while(counter != inis_son);

        //printf("%d %d\n", oncelik, idx);
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
            else if(counter->sonraki == inis_son){
                inis_son->sonraki = yeni;
                yeni->sonraki = NULL;
                inis_son = yeni;
            }
            else{
                temp = counter->sonraki;
                counter->sonraki = yeni;
                yeni->sonraki = temp;
            }
        }
        else{
            inis_son->sonraki = yeni;
            inis_son = yeni;
        }

        

        /*if((deger+index)->talep_inis_saati == inis_son->inis_saati && yeni->oncelik_id < inis_son->oncelik_id){
            
            struct inis_sirasi * t = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
            t = inis_ilk;
            while(t->sonraki != inis_son){
                //printf("za\n");
                t = t->sonraki;
            }
            if(inis_son == inis_ilk && inis_ilk == t){
                //printf("za\n");
                inis_ilk = yeni;
                yeni->sonraki = t;
                t->sonraki = NULL;
                inis_son = t;
            }
            else{
                t->sonraki = yeni;
                yeni->sonraki = inis_son;
            }
        }
        else{
            inis_son->sonraki = yeni;
            inis_son = yeni;
        }*/
    }
}

struct inis_sirasi * pull_inis(){
    struct inis_sirasi * t = (struct inis_sirasi *)malloc(sizeof(struct inis_sirasi));
    t = inis_ilk;
    inis_ilk = inis_ilk->sonraki;
    return t;
}

int main(){
    input_oku();
    for(int i = 0; i < 8; i++){
        printf("%hu %d %hu\n", deger[i].oncelik_id, deger[i].ucak_id, deger[i].talep_inis_saati);
    }
    printf("\n\n");
    enqueue_inis(0);
    enqueue_inis(1);
    enqueue_inis(2);
    printf("\n\n");
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    printf("%d\n", pull_inis()->ucak_id);
    //printf("%d\n", pull_inis()->ucak_id);
    //printf("%d\n", pull_inis()->ucak_id);
    return 0;
}