#include"header.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void init(multi_t *t)
    {
        t->head = NULL;                
    }

void initStack(stack_t *t)
    {
        t->top = -1;
    }

int push(stack_t *p, int x, int y)
    {
        if(p->top == MAX-1)
            return -1; 
        p->top++;
        p->a[p->top].x = x;
        p->a[p->top].y = y;
        return 1;    
    }

int pop(stack_t *p, pos_t *popped)
    {
        if(isEmpty(p))
            return -1;
        *popped = p->a[p->top];
        p->top--;
        return 2;
    }

int isEmpty(stack_t *p)
    {
        return p->top == -1;
    }

pos_t peep(stack_t *p)
    {
        pos_t end;
        
        if(p->top == -1)
            end.x = end.y = -1;
        else
            end = p->a[p->top];
        return end;
    }

node_t* create_node(int info, int x, int y, int block)
    {
        node_t *temp = (node_t*)malloc(sizeof(node_t));
        temp->info = info;
        temp->pos.x = x;
        temp->pos.y = y;
        temp->block = block;
        temp->right = NULL;
        temp->down = NULL;
        return temp;
    }

list_t* create_list()
    {
        list_t *temp = (list_t*)malloc(sizeof(list_t));
        temp->head = NULL;
        temp->down = NULL;
        return temp;
    }

int rows()
    {
        FILE *fp = fopen("input.txt", "r");
        int row = 0;
        char line[100];
        while(fgets(line, 100, fp))
            {
                row++;
            }
        fclose(fp);
        return row-2;
    }

int columns()
    {
        FILE *fp = fopen("input.txt", "r");
        char line[100];
        int col = 0;
        fgets(line, 100, fp);
        fgets(line, 100, fp);
        fgets(line, 100, fp);
        for(int i = 0; i<strlen(line); i++)
            {
                if(line[i] != '\n' && line[i] != ' ')
                    col++;
            }
        fclose(fp);
        return col;
    }

void insert_node(list_t *p, int info, int x, int y, int block)
    {
        node_t *temp = create_node(info, x, y, block);
        if(p->head == NULL)
        {
            p->head = temp;
        }
        else
        {
            node_t *pres = p->head;
            while(pres->right != NULL)
            {
                pres = pres->right;
            }
            pres->right = temp;
        }
    }

list_t* insert_row(multi_t *t)
    {
        list_t *templist = create_list();
        list_t *preslist = t->head;

        if(t->head == NULL)
        {
            t->head = templist;
            return t->head;
        }
        else
        {
            while(preslist->down != NULL)
            {
                preslist = preslist->down;
            }
            preslist->down = templist;
        }
        return preslist->down;
    }

void readFile(multi_t *t)
    {
        FILE *fp = fopen("input.txt", "r");
        char line[100];
        char line2[100];
        int row = 0;
        int col = 0;
        int info;

        fgets(line, 100, fp);
        fgets(line, 100, fp);
        while(fgets(line, 100, fp))
        {
            col = 0;
            list_t* current_row = insert_row(t);
            info = atoi(strtok(line, " "));
            if(info == 0)
                insert_node(current_row, info, row, col, 0);
            while(col < columns()-1)
            {
                col++;
                info = atoi(strtok(NULL, " "));
                if(info == 0)
                    insert_node(current_row, info, row, col, 0);
            }
            row++;
        }
        fclose(fp);
    }

void initialize_down(multi_t *t)
    {
        node_t *pres;
        node_t *next;
        if(t->head == NULL)
        {
            printf("No rows available..\n");
        }
        else
        {
            list_t *preslist = t->head;
            list_t *nextlist = t->head->down;
            while(nextlist != NULL)
            {
                pres = preslist->head;
                next = nextlist->head;
                while(next != NULL)
                {
                    if(pres != NULL && pres->pos.y == next->pos.y)
                    {
                        pres->down = next;
                        pres = pres->right;
                        next = next->right;
                    }
                    else
                    {
                        if(pres == NULL)
                        {
                            pres = preslist->head;
                            next = next->right;
                        }
                        else
                        {
                            pres = pres->right;
                        }
                    }
                }
                preslist = nextlist;
                nextlist = nextlist->down;
            }
        }
    }

void display(multi_t *p)
    {
        if(p->head == NULL)
        {
            printf("No rows available..\n");
        }
        else
        {
            list_t *preslist = p->head;
            while(preslist != NULL)
            {
                node_t *presnode = preslist->head;
                while(presnode != NULL)
                {
                    printf("%d:(%d,%d)  ", presnode->info, presnode->pos.x, presnode->pos.y);
                    presnode = presnode->right;
                }
                printf("\n");
                preslist = preslist->down;
            }
        }
    }

node_t* initStart(multi_t *t, int x, int y)
    {
        list_t *preslist = t->head;
        node_t *pres = preslist->head;
        
        while (preslist != NULL)
        {
            while (pres != NULL)
            {
                if(pres->pos.x == x && pres->pos.y == y)
                    return pres;
                pres = pres->right;
            }
            preslist = preslist->down;
            pres = preslist->head;
        }
        
        
        printf("\ninitStart: %d, %d", pres->pos.x, pres->pos.y);
        
    }

void reverseStack(stack_t *old, stack_t *new)
    {
        pos_t popped;
        while(!isEmpty(old))
        {
            pop(old, &popped);
            push(new, popped.x, popped.y);
        }
    }

int check(pos_t start, pos_t end)
    {
        if(start.x == end.x && start.y == end.y)
            return 0;
        else if(start.x == end.x && start.y != end.y)
            return 1;
        else if(start.x != end.x && start.y == end.y)
            return 1;
    }

void pathMatch(multi_t *t)
    {
        stack_t s;
        initStack(&s);

        pos_t start;
        pos_t end;

        FILE *fp = fopen("input.txt", "r");
        fscanf(fp, "%d %d", &start.x, &start.y);
        fscanf(fp, "%d %d", &end.x, &end.y);
        printf("start:(%d, %d) end:(%d, %d)\n", start.x, start.y, end.x, end.y);

        list_t *preslist = t->head;
        node_t *pres = initStart(t, start.x, start.y);

        while(check(pres->pos, end) && initStart(t, start.x, start.y)->block != 1)
        {
            if(pres != NULL)
            {
                if(pres->right != NULL && (pres->pos.y+1 == pres->right->pos.y) && pres->right->block != 1)
                {
                    push(&s, pres->pos.x, pres->pos.y);
                    pres = pres->right;
                    if(pres->pos.x == end.x && pres->pos.y == end.y)
                        break;
                }
                else if(pres->down != NULL && pres->down->block != 1)
                {
                    push(&s, pres->pos.x, pres->pos.y);
                    pres = pres->down;
                }
                else
                {
                    if(check(pres->pos, end))
                    {
                        pres->block = 1;
                        initStack(&s);
                        pres = initStart(t, start.x, start.y);
                    }
                }
            }
        }
        push(&s, pres->pos.x, pres->pos.y);
        pres = initStart(t, start.x, start.y);

        if((end.x != peep(&s).x) || (end.y != peep(&s).y))
        {
            printf("Bot cannot reach the specified location...!");
        }
        else
        {
            displayPath(&s);
        }
    }

int pathFinder(multi_t *t)
    {
        FILE *fp = fopen("input.txt", "r");
        pos_t start;
        pos_t end;

        fscanf(fp, "%d %d", &start.x, &start.y);
        fscanf(fp, "%d %d", &end.x, &end.y);

        list_t *preslist = t->head;
        node_t *pres = initStart(t, start.x, start.y);

        if(pres->right != NULL && (pres->pos.y+1 == pres->right->pos.y))
        {
            pathMatch(t);
        }
        else if(pres->down != NULL)
        {
            pathMatch(t);
        }
        else
        {
            printf("Bot cannot reach the specified location...!\n");
        }    
    }

void displayPath(stack_t *p)
    {
        pos_t popped;
        stack_t path;
        initStack(&path);
        reverseStack(p, &path);
        FILE *fp = fopen("output.txt", "w");
        printf("Path Found\n");
        while(!isEmpty(&path))
        {
            pop(&path, &popped);
            printf("(%d, %d)\n", popped.x, popped.y);
            fprintf(fp, "%d, %d\n", popped.x, popped.y);    
        }
    }