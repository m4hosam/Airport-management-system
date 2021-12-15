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
struct Landing *sabiha;

struct Landing *newNode(int priority, int id, int landingTime, int delay, int req_landing)
{
    struct Landing *node = (struct Landing *)malloc(sizeof(struct Landing));
    (node)->id = id;
    (node)->priority = priority;
    (node)->landingTime = landingTime;
    (node)->req_landing = req_landing;
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

// p: priority, d: id, t: requested time, delay: delayed time
void push(struct Landing **head, int p, int d, int t, int delay, int req)
{
    struct Landing *start = (*head);

    // Create new Node
    struct Landing *new_node = newNode(p, d, t, delay, req);

    // the inserting time is less than the head number
    // first element

    if (start->next == NULL)
    {
        start->next = new_node;
        printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", start->next->id, start->next->landingTime);
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
            printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
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
                                printf("\tUcak id: %d will land on Sabiha\n\n", start->next->id);
                                while (sabiha->next != NULL)
                                    sabiha = sabiha->next;

                                sabiha->next = newNode(start->next->priority, start->next->id, start->next->landingTime, start->next->delayed, start->next->req_landing);
                                new_node->next = start->next->next;
                                start->next = new_node;
                                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                            }
                            else
                            {
                                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", d, t);
                                push(head, p, d, ++t, ++delay, req);
                            }
                        }
                        else
                        {
                            // printf("33\n");
                            struct Landing *tmp = start->next;
                            new_node->next = start->next->next;
                            start->next = new_node;
                            printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                            push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed), req);
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
                                printf("\tUcak id: %d will land on Sabiha\n\n", d);
                                while (sabiha->next != NULL)
                                    sabiha = sabiha->next;

                                sabiha->next = newNode(p, d, t, delay, req);
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed), req);
                                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                                free(tmp);
                            }
                        }
                        else
                        {
                            printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", d, t);
                            push(head, p, d, ++t, ++delay, req);
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
                                    printf("\tUcak id: %d will land on Sabiha\n\n", d);
                                    while (sabiha->next != NULL)
                                        sabiha = sabiha->next;

                                    sabiha->next = newNode(p, d, t, delay, req);
                                }
                                else
                                {
                                    printf("\tUcak id: %d will land on Sabiha\n\n", start->next->id);
                                    while (sabiha->next != NULL)
                                        sabiha = sabiha->next;

                                    sabiha->next = newNode(start->next->priority, start->next->id, start->next->landingTime, start->next->delayed, start->next->req_landing);

                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                                }
                            }
                            else
                            {
                                struct Landing *tmp = start->next;
                                new_node->next = start->next->next;
                                start->next = new_node;
                                push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed), req);
                                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                                free(tmp);
                            }
                        }
                        else
                        {
                            if (start->next->delayed == 3)
                            {
                                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", d, t);
                                push(head, p, d, ++t, ++delay, req);
                            }
                            else
                            {
                                if (start->next->id < d)
                                {
                                    printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", d, t);
                                    push(head, p, d, ++t, ++delay, req);
                                }
                                else
                                {
                                    struct Landing *tmp = start->next;
                                    new_node->next = start->next->next;
                                    start->next = new_node;
                                    push(head, tmp->priority, tmp->id, ++(tmp->landingTime), ++(tmp->delayed), req);
                                    printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
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
                    printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
                }
            }
            else
            {

                // reached at the ends of the list
                printf("\tucak id: %d inis izin talebiniz saat (%d) onaylanmistir\n", new_node->id, new_node->landingTime);
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
    struct Landing *pq = newNode(-1, -1, -1, -1, -1);
    sabiha = newNode(-1, -1, -1, -1, -1);
    struct Landing *headd = sabiha;
    int p, d, t;
    char buf[100];
    fgets(buf, 100, fp);
    while (fscanf(fp, "%d %d %d\n", &p, &d, &t) != EOF)
    {
        printf("\np: %d,id: %d,t: %d\n", p, d, t);
        push(&pq, p, d, t, 0, t);
    }

    // push(&pq, 1, 1, 14, 0);
    // push(&pq, 2, 2, 13, 0);
    // push(&pq, 2, 3, 11, 0);
    // push(&pq, 3, 4, 10, 0);
    // push(&pq, 4, 5, 16, 0);
    // push(&pq, 2, 6, 10, 0);
    // push(&pq, 3, 7, 2, 0);
    // push(&pq, 3, 8, 14, 0);

    printf("\t--printing--\n");
    while (!isEmpty(&pq))
    {
        printf("priority: %d ", pq->priority);
        printf("id: %d ", pq->id);
        printf("l_t: %d ", pq->landingTime);
        printf("req_t: %d ", pq->req_landing);
        printf(" delay: %d \n", pq->delayed);
        pop(&pq);
    }
    printf("\n\n\t\t-----Sabiha\n");
    while (headd->next != NULL)
    {
        printf("priority: %d ", headd->priority);
        printf("id: %d ", headd->id);
        printf("l_t: %d ", headd->landingTime);
        printf("req_t: %d ", headd->req_landing);
        printf(" delay: %d \n", headd->delayed);
        headd = headd->next;
    }

    return 0;
}
