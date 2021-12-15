#include <stdio.h>
#include <stdlib.h>

struct Landing
{
    int priority;
    int id;
    int landingTime;
    int delayed;
    int req_landing;
    struct Landing *next;
};


//for sorting
struct FileData
{
    int priority;
    int id;
    int req_landing;
};

struct FileData * data;


//for sorting
int ReadFile(){
    int i = 0;
    data = (struct FileData *)malloc(sizeof(struct FileData));

    FILE * fp;
    fp = fopen("input.txt", "r");

    while(fscanf(fp, "%d %d %d\n", &(data+i)->priority, &(data+i)->id, &(data+i)->req_landing) != EOF){
        i++;
        data = (struct FileData *)realloc(data, sizeof(struct FileData) * (i+1));
    }

    //Sort the data based on requested landing time
    int n = sizeof(data);
    struct FileData temp;
    for(int k = 0; k < n-1; k++){
        for(int j = 0; j < n-1-k; j++){
            if(data[j].req_landing > data[j+1].req_landing){
                temp = data[j+1];
                data[j+1] = data[j];
                data[j] = temp;
            }
        }
    }

    return n;
}

struct Landing *newNode(int priority, int id, int landingTime, int delay)
{
    struct Landing *node = (struct Landing *)malloc(sizeof(struct Landing));
    (node)->id = id;
    (node)->priority = priority;
    (node)->landingTime = landingTime;
    (node)->req_landing = landingTime;
    (node)->delayed = delay;
    (node)->next = NULL;
    return (node);
}

int peek(struct Landing **node)
{
    return ((*node)->landingTime);
}

void pop(struct Landing **head)
{
    struct Landing *tmp = (*head);
    (*head) = (*head)->next;
    free(tmp);
}

int isEmpty(struct Landing **node)
{
    return ((*node) == NULL);
}

int LandingCount = 0;

// p: priority, d: id, t: requested time, delay: delayed time
void push(struct Landing **head, int p, int d, int t, int delay)
{
    struct Landing *start = (*head);
    struct Landing *new_node = newNode(p, d, t, delay);

    /*if(LandingCount == 24){
        printf("Havalimani gunluk kapasitesini doldurmustur. %d ID'li ucus Sabiha Gokcen Havaalanına yonlendiriliyor.\n", new_node->id);
    }*/
    if (start->next == NULL)
    {
        start->next = new_node;
        printf("%d ID'li ucak icin %d saatli inis talebi onaylanmistir.\n", start->next->id, start->next->landingTime);
    }
    else
    {
        // printf("v: %d,t: %d\n", start->next->landingTime, t);
        if ((*head)->next->landingTime > t)
        {
            // Insert New Node before head
            struct Landing *temp = start->next;
            (*head)->next = new_node;
            new_node->next = temp;
            printf("%d ID'li ucak icin %d saatli inis talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
        }
        else if(LandingCount == 24){
            while (start->next != NULL && start->next->landingTime < t){
                start = start->next;
            }
            if(start->next->priority > p){
                struct Landing * tmp = start->next;
                new_node->next = start->next->next;
                new_node->landingTime = start->next->landingTime;
                LandingCount--;
                printf("%d ID'li ucak icin %d saatli inis talebi onaylanmistir.\n", d, t);
                printf("%d ID'li ucak, kapasite dolu oldugu icin Sabiha Gokcen Havalimani'na yonlendirilmistir.", tmp->id);
                free(tmp);
            }
            else if(start->next == NULL){
                LandingCount--;
                printf("Kapasite doldugu icin %d ID'li ucak Sabiha Gokcen Havalimani'na yonlendirilmistir.\n", d);
            }
            else{
                push(head, p, d, ++t, ++delay);
            }
        }
        else
        {
            while (start->next != NULL && start->next->landingTime < t)
            {
                start = start->next;
            }

            // 2 12 14 , 1 15 14
            if ((start->next) != NULL)
            {

                if (start->next->landingTime == t)
                {

                    if (start->next->priority > p) // swap and push the other element
                    {
                        // the whole logic is in here...
                        // it has been delayed 3 times
                        // printf("22");
                        if (start->next->delayed == 3)
                        {
                            // don't swap push directly
                            if (delay == 3)
                            {
                                printf("%d ID'li ucak Sabiha Gokcen Havalimani'na yonlendirilmistir.\n", start->next->id);
                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("%d ID'li ucak icin %d saatli inis talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                            }
                            else
                            {
                                printf("%d ID'li ucagin ucusu %d saatine ertelenmistir.\n", d, t + 1);
                                push(head, p, d, ++t, ++delay);
                            }
                        }
                        else
                        {
                            struct Landing *tmp = start->next;
                            new_node->next = start->next->next;
                            start->next = new_node;
                            printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                            printf("%d ID'li ucagin ucusu %d saatine ertelenmistir.\n", tmp->id, tmp->landingTime + 1);
                            push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
                            free(tmp);
                        }
                    }
                    else if (start->next->priority < p)
                    {
                        // don't swap push directly
                        if (delay == 3)
                        {
                            if (start->next->delayed == 3)
                            {
                                printf("%d ID'li ucak Sabiha Gokcen Havalimani'na yonlendirilmistir.\n", d);
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("%d ID'li ucagin ucusunun daha fazla ertelenmemesi adina %d ID'li ucagin ucusu %d saatine ertelenmistir.\n", d, tmp->id, tmp->landingTime + 1);
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
                                printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                                free(tmp);
                            }
                        }
                        else
                        {
                            printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", d, t);
                            push(head, p, d, ++t, ++delay);
                        }
                    }
                    else
                    {
                        // Same priority diffrent id and delays

                        if (delay == 3)
                        {
                            if (start->next->delayed == 3)
                            {
                                // smaller id have the priority to land first
                                if (start->next->id < d)
                                    printf("%d ID'li ucak Sabiha Gokcen Havalimani'na yonlendirilmistir.\n", d);
                                else
                                {
                                    printf("%d ID'li ucak Sabiha Gokcen Havalimani'na yonlendirilmistir.\n", start->next->id);
                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                                }
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
                                printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                                free(tmp);
                            }
                        }
                        else
                        {
                            if (start->next->delayed == 3)
                            {
                                printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", d, t);
                                push(head, p, d, ++t, ++delay);
                            }
                            else
                            {
                                if (start->next->id < d)
                                {
                                    printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", d, t);
                                    push(head, p, d, ++t, ++delay);
                                }
                                else
                                {
                                    struct Landing *tmp = start->next;
                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
                                    printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                                    free(tmp);
                                }
                            }
                        }
                    }
                }
                else
                {
                    // if the number is in beteen the linked list
                    new_node->next = start->next;
                    start->next = new_node;
                    printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                }
            }
            else
            {

                // reached at the ends of the list
                printf("%d ID'li ucagin %d saatli ucus talebi onaylanmistir.\n", new_node->id, new_node->landingTime);
                start->next = new_node;
            }
        }
    }
}

int main()
{
    /*FILE *fp;
    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        printf("File not found");
        return 1;
    }*/
    int count = ReadFile();
    struct Landing *pq = newNode(-1, -1, -1, -1);
    //int p, d, t;
    /*while (fscanf(fp, "%d %d %d\n", &p, &d, &t) != EOF)
    {
        printf("\np: %d,id: %d,t: %d\n", p, d, t);
        push(&pq, p, d, t, 0);
        LandingCount++;
    }*/

    //assigning sorted values
    for(int i = 0; i < count; i++){
        printf("p: %d, id: %d, t: %d\n", data[i].priority, data[i].id, data[i].req_landing);
        push(&pq, data[i].priority, data[i].id, data[i].req_landing, 0);
        LandingCount++;
    }

    pq = pq->next;
    while (!isEmpty(&pq))
    {
        printf("priority: %d ", pq->priority);
        printf("id: %d ", pq->id);
        printf(" time: %d ", pq->landingTime);
        printf(" delay: %d \n", pq->delayed);
        pop(&pq);
    }

    printf("\n%d\n", LandingCount);

    return 0;
}