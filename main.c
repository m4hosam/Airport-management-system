#include <stdio.h>
#include <stdlib.h>

struct Landing
{
    int priority;
    int id;
    int req_time;
    int delayed;
    struct Landing *next;
    struct Landing *previous;
};

struct Landing **newNode(int priority, int id, int req_time, int delay)
{
    struct Landing **node = (struct Landing *)malloc(sizeof(struct Landing *));
    (*node)->id = id;
    (*node)->priority = priority;
    (*node)->req_time = req_time;
    (*node)->delayed = delay;
    (*node)->next = NULL;
    (*node)->previous = NULL;
    printf("77\n");
    return (*node);
}

int peek(struct Landing **node)
{
    return ((*node)->req_time);
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
    printf("node\n");
    // Create new Node
    struct Landing **new_node = newNode(p, d, t, delay);
    printf("888\n");

    // the inserting time is less than the head number
    if ((*head)->req_time > t)
    {
        // Insert New Node before head
        new_node->next = (*head);
        (*head) = new_node;
    }
    else
    {
        // if(req_time of the head is equaled to the new node)

        // Traverse the list and find a
        // position to insert new node
        while (start->next != NULL && start->next->req_time < t)
        {
            start = start->next;
        }

        // 2 12 14 , 1 15 14
        if (start->next->req_time == t)
        {
            if (start->next->priority > p) // swap and push the other element
            {
                // the whole logic is in here...

                // it has been delayed 3 times
                if (start->next->delayed == 3)
                {
                    // don't swap push directly
                    push(head, p, d, ++t, ++delay);
                }
                else
                {
                    struct Landing *tmp = start->next;
                    start->next = new_node;
                    push(head, tmp->priority, tmp->id, ++(tmp->req_time), ++(tmp->delayed));
                }
            }
            else if (start->next->priority < p)
            {
                // don't swap push directly
                push(head, p, d, ++t, ++delay);
            }
            else
            {
                // 1 12 1, 1 13 1
                if (start->next->id > d)
                {
                    // swap then push
                    struct Landing *tmp = start->next;
                    start->next = new_node;
                    push(head, tmp->priority, tmp->id, ++(tmp->req_time), ++(tmp->delayed));
                }
                else
                {
                    // don't swap push directly
                    push(head, p, d, ++t, ++delay);
                }
            }
        }
        else
        {
            // Either at the ends of the list
            // or at required position
            start->next = new_node;
        }
    }
}

int main()
{
    printf("111\n");

    struct Landing **pq = newNode(1, 1, 14, 0);
    printf("222\n");
    push(pq, 2, 2, 13, 0);
    printf("333\n");
    push(pq, 2, 3, 11, 0);
    printf("444\n");
    push(pq, 3, 4, 10, 0);

    while (!isEmpty(pq))
    {
        printf("%d ", peek(pq));
        pop(pq);
    }

    return 0;
}
