typedef struct position
    {
        int x;
        int y;
    }pos_t;

#define MAX 100

struct stack
    {
        pos_t a[MAX];
        int top;
    };
typedef struct stack stack_t;

typedef struct node
    {
        int info;
        pos_t pos;
        int block;
        struct node *right;
        struct node *down;
    }node_t;

typedef struct list
    {
        node_t *head;
        struct list *down;
    }list_t;

typedef struct multilist
    {
        list_t *head;
    }multi_t;


void readFile(multi_t *t);
void init(multi_t*);
node_t* create_node(int, int, int, int);
list_t* create_list();
void insert_node(list_t*, int, int, int, int);
list_t* insert_row(multi_t*);
void display(multi_t*);
int rows();
void initialize_down(multi_t*);
int columns();
void initStack(stack_t*);
int push(stack_t*, int, int);
int pop(stack_t*, pos_t*);
int isEmpty(stack_t*);
int pathFinder(multi_t*);
void displayPath(stack_t*);
node_t* initStart(multi_t*, int, int);
pos_t peep(stack_t*);

