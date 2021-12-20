#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Landing
{
    int priority;
    int id;
    int landingTime;
    int delayed;
    struct Landing *next;
};
int sabiha[30];
int count = 0;

struct Landing *newNode(int priority, int id, int landingTime, int delay)
{
    struct Landing *node = (struct Landing *)malloc(sizeof(struct Landing));
    (node)->id = id;
    (node)->priority = priority;
    (node)->landingTime = landingTime;
    (node)->delayed = delay;
    (node)->next = NULL;
    return (node);
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

// p: priority, d: id, t: requested time, delay: delayed time
void push(struct Landing **head, int p, int d, int t, int delay)
{
    struct Landing *start = (*head);

    // Create new Node
    struct Landing *new_node = newNode(p, d, t, delay);

    // the inserting time is less than the head number
    // first element

    if (start->next == NULL)
    {
        start->next = new_node;
        printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", start->next->id, start->next->landingTime);
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
            printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
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
                        if (start->next->delayed == 3)
                        {
                            // don't swap push directly
                            if (delay == 3)
                            {
                                printf("\t-iki ucak 3 kere ertelenmis oldugundan dolayi dusuk oncelik [%d] id olan ucak Sabiha Gokcen'e yonlendirilmistir\n", start->next->id);
                                sabiha[count] = start->next->priority;
                                count++;

                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("\t-yuksek oncelik-[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                            }
                            else
                            {
                                printf("\t-3 kere ertelen ucak yer aldigindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", d, t);
                                // t = (t == 24) ? 0 : t;
                                push(head, p, d, ++t, ++delay);
                            }
                        }
                        else
                        {
                            struct Landing *tmp = start->next;
                            new_node->next = start->next->next;
                            start->next = new_node;
                            printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                            printf("\t-dusuk oncelik-[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", tmp->id, tmp->landingTime);
                            // tmp->landingTime = (tmp->landingTime == 24) ? 0 : tmp->landingTime;
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
                                printf("\t-iki ucagin 3 kere ertelenmis olmasindan dolayi dusuk oncelikli [%d] id olan ucak Sabiha Gokcen'e yonlendirilmistir\n", d);
                                sabiha[count] = d;
                                count++;
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("\t-3 kere ertelen ucak yer almasindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", tmp->id, tmp->landingTime);
                                printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                                // tmp->landingTime = (tmp->landingTime == 24) ? 0 : tmp->landingTime;
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));

                                free(tmp);
                            }
                        }
                        else
                        {
                            printf("\t-dusuk oncelik-[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", d, t);
                            // t = (t == 24) ? 0 : t;
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
                                {
                                    printf("\t-iki ucagin 3 kere ertelenmis olmasindan dolayi yuksek id olan [%d] ucak Sabiha Gokcen'e yonlendirilmistir\n", d);
                                    sabiha[count] = d;
                                    count++;
                                }
                                else
                                {
                                    printf("\t-iki ucagin 3 kere ertelenmis olmasindan dolayi yuksek id olan [%d] ucak Sabiha Gokcen'e yonlendirilmistir\n", start->next->id);
                                    sabiha[count] = start->next->id;
                                    count++;

                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                                }
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("\t-3 kere ertelen ucak yer almasindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", tmp->id, tmp->landingTime);
                                printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                                // tmp->landingTime = (tmp->landingTime == 24) ? 0 : tmp->landingTime;
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
                                free(tmp);
                            }
                        }
                        else
                        {
                            if (start->next->delayed == 3)
                            {
                                printf("\t-3 kere ertelen ucak yer almasindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", d, t);
                                // t = (t == 24) ? 0 : t;
                                push(head, p, d, ++t, ++delay);
                            }
                            else
                            {
                                if (start->next->id < d)
                                {
                                    printf("\t-ayni oncelik yuksek id- olmasindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", d, t);
                                    // t = (t == 24) ? 0 : t;
                                    push(head, p, d, ++t, ++delay);
                                }
                                else
                                {
                                    struct Landing *tmp = start->next;
                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    printf("\t-ayni oncelik yuksek id- olmasindan dolayi [%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmamistir\n", tmp->id, tmp->landingTime);
                                    printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                                    // tmp->landingTime = (tmp->landingTime == 24) ? 0 : tmp->landingTime;
                                    push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed));
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
                    printf("\t[%d] id olan ucak inis izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                }
            }
            else
            {

                // reached at the ends of the list
                printf("\t[%d] id olan ucak izin talebiniz saat (%d) icin onaylanmistir\n", new_node->id, new_node->landingTime);
                start->next = new_node;
            }
        }
    }
}

int main()
{
    FILE *fp;
    if ((fp = fopen("input.txt", "r")) == NULL)
    {
        printf("File not found");
        return 1;
    }
    struct Landing *pq = newNode(-1, -1, -1, -1);
    int p, d, t, kalkis, req_time, landingTime;

    char buf[100];
    fgets(buf, 100, fp);
    while (fscanf(fp, "%d %d %d\n", &p, &d, &t) != EOF)
    {
        printf("\np: %d,id: %d,t: %d\n", p, d, t);
        push(&pq, p, d, t, 0);
    }

    FILE *outFile;
    if ((outFile = fopen("output.txt", "w")) == NULL)
    {
        printf("File not found");
        return 1;
    }
    fprintf(outFile, "oncelik_id\t|\tucak_id\t|\ttalep_edilen_inis_saati\t|\tinisSaat\t|\tgecikme_suresi\t|\tkalkis\n");

    printf("\t--printing--\n");
    int i = 0;
    char tracker[100] = "\t\t";
    while (!isEmpty(&pq))
    {

        req_time = (pq->landingTime) - (pq->delayed);
        landingTime = pq->landingTime;
        kalkis = (pq->landingTime) + 1;

        if (pq->landingTime >= 24)
        {
            if (pq->landingTime == 24)
            {
                kalkis = (pq->landingTime) - 23;
            }
            else
            {
                landingTime = (pq->landingTime) - 24;
                strcpy(tracker, " ErtesiGun/Sabiha");
                kalkis = (pq->landingTime) - 23;
            }
        }

        if (pq->id != -1)
            fprintf(outFile, "%d\t\t\t %d\t\t\t %d\t\t\t\t\t\t\t %d%s\t\t %d\t\t\t\t %d%s\n", pq->priority, pq->id, req_time, landingTime, tracker, pq->delayed, kalkis, tracker);
        printf("[%d]priority: %d ", i, pq->priority);
        printf("id: %d ", pq->id);
        printf("l_t: %d ", landingTime);
        printf(" delay: %d \n", pq->delayed);
        pop(&pq);
        i++;
    }
    printf("\n\n\t\t-----Sabiha Gokcen'e Yonlendirilenler-----\n");
    for (int i = 0; i < count; i++)
    {
        printf("[%d]Ucak id: %d Sabiha Gokcen'e yonlendirildi\n", i + 1, sabiha[i]);
    }
    fclose(fp);
    fclose(outFile);

    return 0;
}