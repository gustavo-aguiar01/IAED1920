/*========================= PROJECT NO 1 IAED 2019/2020 IST ========================*/
/*                        ist195587 - Gustavo Almeida Aguiar                        */
/*                                                                                  */
/* This project's goal is to implement a logistics system which allows the user to  */
/* manage its own stock of products and orders.                                     */
/*==================================================================================*/

/*==================================== HEADERS =====================================*/

#include <stdio.h>
#include <string.h>

/*===================================== MACROS =====================================*/

#define MAXDESC 64     /* Max product description size */
#define MAXPRODS 10000 /* Max number of different products */
#define MAXORDS 500    /* Max number of different orders */
#define MAXWGT 200     /* Max weight of one single order */
#define ID 0           /* Used as index for my orders' products ID's */
#define QTY 1          /* Used as index for the amount of a certain product in an order */
#define TRUE 2         /* Used to return true */
#define FALSE 3        /* Used to return false */
#define LESS 4         /* Used to return int functions that evaluate if x < y */
#define MORE 5         /* Used to return int fucntions that fail to evaluate that x < y */

/*=================================== DATA TYPES ===================================*/

/* Data type for all the products */
typedef struct
{

    int price;
    char name[MAXDESC];
    int weight;
    int stock;

} Product;

/* Data type for all the orders */
/* An order is a set of products */
typedef struct
{
    int weight;
    /* I've set MAXWGT to rows because an order can't have more than 
    200 products due to min weight of products = 1 */
    /* There are 2 columns because we only need the PID and its qty in the order */
    int products[MAXWGT][2];
    int nprods;

} Order;

/*================================ GLOBAL VARIABLES ================================*/

/* Array of products */
Product products[MAXPRODS];
/* Array of orders */
Order orders[MAXORDS];
/* Global variables for product ID and order ID */
int pid, oid;

/*============================== AUXILIARY FUNCTIONS ===============================*/
int pidExists(int tpid);    /* Checks if a given product ID is in the system */
int oidExists(int toid);    /* Checks if a given order ID is in the system */
int cmpPrice(int x, int y); /* Checks if product from pid x has lower price than product from pid y */
int cmpName(int x, int y);  /* Compares 2 strings and returns TRUE if strcmp(prod[x].name, prod[y].name) > 0 */

void a(); /* Adds a product to the system */
void q(); /* Adds stock to an existing product */
void r(); /* Removes stock to an existing product */
void p(); /* Updates an existing product's price */
void l(); /* Sorts products and lists them by asceding price order */
void m(); /* Lists order id where a given product has the most qty */
void N(); /* Adds a new order to the system */
void A(); /* Adds a product to an existing order */
void R(); /* Removes an existing product from an order */
void C(); /* Calculates the total cost of a given order */
void E(); /* Lists name & qty of given product from given order */
void L(); /* Sorts all items from a given order alphabetically */

void mergeSortl(int ids[], int e, int d);    /* Stable merge sort algorith for command 'l' */
void mergel(int ids[], int e, int m, int d); /* Merges sorted arrays */

void bubbleSwap(int toid, int p1, int p2); /* Swaps 2 product indexes and qty from a given order */

/*====================================== MAIN ======================================*/

int main()
{

    /* Control variable */
    /* Depending on the char, different commands will be done */
    int cmd;

    /* If it reads the EOF, nothing left to do */
    while ((cmd = getchar()) != EOF)
    {

        /* Depending on which command was read - different cases */
        switch (cmd)
        {
        /*------------PRODUCTS----------*/
        /* Adds a product to the system */
        case 'a':
            a();
            break;

        /* Adds stock to an existing product */
        case 'q':
            q();
            break;

        /* Removes stock to an existing product */
        case 'r':
            r();
            break;

        /* Changes an existing product's price */
        case 'p':
            p();
            break;
        /* Lists the order id where a given product has the most stock */
        case 'm':
            m();
            break;
        /* Sorts products and lists them by asceding price order */
        case 'l':
            l();
            break;

        /*----------ORDERS----------*/
        /* Adds a new order to system */
        case 'N':
            N();
            break;
        /* Adds an existing product to an order */
        case 'A':
            A();
            break;
        /* Removes an existing product from an order */
        case 'R':
            R();
            break;
        /* Calculates the total cost of a given order */
        case 'C':
            C();
            break;
        /* Lists name & qty of given product from given order */
        case 'E':
            E();
            break;
        /* Sorts all items from a given order alphabetically */
        case 'L':
            L();
            break;

        /*-----------END------------*/
        case 'x':
            break;
        }
    }
    return 0;
}

/*=================================== FUNCTIONS =====================================*/
/* All variables started with t are used as temporaryx, eg, toid -> temp order id    */
/*------------------------------VERIFICATION FUNCTIONS-------------------------------*/

/* Checks if a given product ID is in the system */
int pidExists(int tpid)
{

    if (tpid > (pid - 1))
    {
        return FALSE;
    }
    return TRUE;
}

/* Checks if a given order ID is in the system */
int oidExists(int toid)
{

    if (toid > (oid - 1))
    {
        return FALSE;
    }
    return TRUE;
}

/* Compares 2 products prices given 2 pid's and returns LESS
if price of product x is < than price of product y; else 
returns MORE */

int cmpPrice(int x, int y)
{

    if (x <= pid - 1 && y <= pid - 1)
    {
        if (products[x].price < products[y].price)
        {
            return LESS;
        }
    }
    return MORE;
}

/* Compares 2 names of products and returns TRUE
if the first unmatched character of product x is greater
than the character from product y */
int cmpName(int x, int y)
{

    if (strcmp(products[x].name, products[y].name) > 0)
    {
        return TRUE;
    }
    return FALSE;
}

/*--------------------------------PRODUCT FUNCTIONS----------------------------------*/

/* Adds a new product */
void a()
{

    scanf(" %[^:]:%d:%d:%d", products[pid].name, &products[pid].price, &products[pid].weight, &products[pid].stock);
    printf("Novo produto %d.\n", pid);
    pid++;

}

/* Adds stock to an existing product */
void q()
{

    int tpid, qty;
    scanf("%d:%d", &tpid, &qty);
    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel adicionar produto %d ao stock. Produto inexistente.\n", tpid);
        return;
    }

    products[tpid].stock += qty;

}

/* Removes a given amount of stock from a given product */
void r()
{

    int tpid, qty; /* qty = amount being removed */

    scanf("%d:%d", &tpid, &qty);

    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel remover stock do produto %d. Produto inexistente.\n", tpid);
        return;
    }
    /* If the given oid doesnt exist in the system print error */
    if ((products[tpid].stock - qty) < 0)
    {
        printf("Impossivel remover %d unidades do produto %d do stock. Quantidade insuficiente.\n", qty, tpid);
        return;
    }

    products[tpid].stock -= qty;

}

/* Updates a product's price */
void p()
{

    int tpid, price;
    scanf("%d:%d", &tpid, &price);

    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel alterar preco do produto %d. Produto inexistente.\n", tpid);
        return;
    }

    products[tpid].price = price;

}

/* Sorts products and lists them by asceding price order */
void l()
{

    /* Array of all productd ID's */
    int ids[MAXPRODS];
    int i;

    for (i = 0; i < pid; i++)
    {
        ids[i] = i;
    }

    /* Sort array of id's by price */
    mergeSortl(ids, 0, pid - 1);

    /* Print sorted array by ascending price order */
    printf("Produtos\n");
    for (i = 0; i < pid; i++)
    {
        printf("* %s %d %d\n", products[ids[i]].name, products[ids[i]].price, products[ids[i]].stock);
    }

}

/*-----------------------------------------------------------------------------------*/
/* Lists order id where a given product has the most qty */
void m()
{

    int tpid;
    /* Max -> biggest amount of a certain product in all orders */
    /* o -> order ID that contains the most of a a given product */
    /* k -> index of the product in the order */
    int max = -1;
    int i, j, ord;
    scanf("%d", &tpid);

    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel listar maximo do produto %d. Produto inexistente.\n", tpid);
        return;
    }

    /* Go through all orders 1 by 1 */
    for (i = 0; i < oid; i++)
    {
        /* Go through every product of each order */
        for (j = 0; j < orders[i].nprods; j++)
        {
            /* If we find the product we're trying to list its max then */
            if (orders[i].products[j][ID] == tpid)
            {
                /* If in that order the given product has more stock than it has on other orders updates max */
                /* It also saves the order ID and the product index in that order */
                if (orders[i].products[j][QTY] > max)
                {
                    max = orders[i].products[j][QTY];
                    ord = i;
                }
            }
        }
    }

    /* If max remains unchanged that means the product doesn't exist in any order */
    if (max != -1)
    {
        printf("Maximo produto %d %d %d.\n", tpid, ord, max);
    }

}
/*---------------------------------ORDER FUNCTIONS-----------------------------------*/
/* Adds a new order to the system */
void N()
{

    printf("Nova encomenda %d.\n", oid);
    oid++;
}

/* Adds a product to an existing order */
void A()
{

    int p;
    int toid, tpid, qty;

    scanf("%d:%d:%d", &toid, &tpid, &qty);
    /* If the given oid doesnt exist in the system print error */
    if (oidExists(toid) == FALSE)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Encomenda inexistente.\n", tpid, toid);
        return;
    }
    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Produto inexistente.\n", tpid, toid);
        return;
    }
    /* Insufficient product stock to add to order */
    if (products[tpid].stock < qty)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Quantidade em stock insuficiente.\n", tpid, toid);
        return;
    }
    /* Order weight + Product * Qty can't exceed MAXWGT */
    if (orders[toid].weight + (products[tpid].weight * qty) > MAXWGT)
    {
        printf("Impossivel adicionar produto %d a encomenda %d. Peso da encomenda excede o maximo de 200.\n", tpid, toid);
        return;
    }

    /* Update order's total weight */
    /* Remove product's stock when adding to order */
    orders[toid].weight += (products[tpid].weight * qty);
    products[tpid].stock -= qty;

    /* If product is already in the order add more stock to order */
    for (p = 0; p < orders[toid].nprods; p++)
    {
        if (orders[toid].products[p][ID] == tpid)
        {
            orders[toid].products[p][QTY] += qty;
            return;
        }
    }

    /* If product is not in order we have to put it in there */
    orders[toid].products[orders[toid].nprods][ID] = tpid;
    orders[toid].products[orders[toid].nprods][QTY] = qty;
    orders[toid].nprods++;

}

/* Removes an existing product from an order */
void R()
{

    int i, j;
    int toid, tpid;
    scanf("%d:%d", &toid, &tpid);
    /* If the given oid doesnt exist in the system print error */
    if (oidExists(toid) == FALSE)
    {
        printf("Impossivel remover produto %d a encomenda %d. Encomenda inexistente.\n", tpid, toid);
        return;
    }
    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel remover produto %d a encomenda %d. Produto inexistente.\n", tpid, toid);
        return;
    }
    /* Go through all order's products */
    for (i = 0; i < orders[toid].nprods; i++)
    {
        /* If product ID of prudoct = product ID of item being removed */
        if (orders[toid].products[i][ID] == tpid)
        {
            /* Update product's stock and order's weight */
            products[tpid].stock += orders[toid].products[i][QTY];
            orders[toid].weight -= (products[tpid].weight * orders[toid].products[i][QTY]);
            /* All products that have a bigger index -- */
            for (j = i; j < orders[toid].nprods - 1; j++)
            {
                orders[toid].products[j][ID] = orders[toid].products[j + 1][ID];
                orders[toid].products[j][QTY] = orders[toid].products[j + 1][QTY];
            }
            /* After removing one index to all products that have a higher index
            than the product that was removed, udpate order's total products */
            orders[toid].nprods--;
        }
    }

}

/* Calculates the total cost of a given order */
void C()
{

    int toid, cost = 0;
    int tpid, qty, i;
    scanf("%d", &toid);

    /* If the given oid doesnt exist in the system print error */
    if (oidExists(toid) == FALSE)
    {
        printf("Impossivel calcular custo da encomenda %d. Encomenda inexistente.\n", toid);
        return;
    }
    /* Go through all products in given order and calculate its cost by 
    multiplying the product's price by its qty in order */
    for (i = 0; i < orders[toid].nprods; i++)
    {
        tpid = orders[toid].products[i][ID];
        qty = orders[toid].products[i][QTY];
        cost += (products[tpid].price * qty);
    }

    printf("Custo da encomenda %d %d.\n", toid, cost);
    
}

/* Lists name & qty of given product from given order */
void E()
{

    int toid, tpid;
    int p;
    scanf("%d:%d", &toid, &tpid);
    /* If the given oid doesnt exist in the system print error */
    if (oidExists(toid) == FALSE)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", toid);
        return;
    }
    /* If the given pid doesnt exist in the system print error */
    if (pidExists(tpid) == FALSE)
    {
        printf("Impossivel listar produto %d. Produto inexistente.\n", tpid);
        return;
    }
    /* Prints amount of the given product in the given order */
    for (p = 0; p < orders[toid].nprods; p++)
    {
        if (orders[toid].products[p][ID] == tpid)
        {
            printf("%s %d.\n", products[tpid].name, orders[toid].products[p][QTY]);
            return;
        }
    }
    /* If there's no products in that order associated with the given pid */
    printf("%s 0.\n", products[tpid].name);

}

/* Swaps 2 product indexes in a given order */
void bubbleSwap(int toid, int p1, int p2)
{

    /* Variables used to switch between products in order */
    int tempid, tempqt;
    /* Save ID and QTY */
    tempid = orders[toid].products[p1][ID];
    tempqt = orders[toid].products[p1][QTY];
    /* Switch */
    orders[toid].products[p1][ID] = orders[toid].products[p2][ID];
    orders[toid].products[p1][QTY] = orders[toid].products[p2][QTY];
    /* Put them back */
    orders[toid].products[p2][ID] = tempid;
    orders[toid].products[p2][QTY] = tempqt;

}

/* Sorts all items from a given order alphabetically */
void L()
{

    int toid;
    int i, j;

    /* Variables used to save the product's id to further compare product's names */
    int pidi, pidj;

    scanf("%d", &toid);

    /* If the given oid doesnt exist in the system print error */
    if (oidExists(toid) == FALSE)
    {
        printf("Impossivel listar encomenda %d. Encomenda inexistente.\n", toid);
        return;
    }

    printf("Encomenda %d\n", toid);

    /* Go through all order products */
    for (i = 0; i < orders[toid].nprods; i++)
    {
        /* Go through products in front */
        for (j = i + 1; j < orders[toid].nprods; j++)
        {
            /* Save product ID for the first element and the elements in front */
            pidi = orders[toid].products[i][ID];
            pidj = orders[toid].products[j][ID];
            /* If product with pid pidj is less than product with pid i, then switch */
            if (cmpName(pidi, pidj) == TRUE)
            {
                /* Bubble sort */
                bubbleSwap(toid, i, j);
            }
        }
    }
    /* Prints all products' name, price and qty in order */
    for (i = 0; i < orders[toid].nprods; i++)
    {
        printf("* %s %d %d\n", products[orders[toid].products[i][ID]].name,
                               products[orders[toid].products[i][ID]].price,
                               orders[toid].products[i][QTY]);
    }

}

/*---------------------------------SORTING ALGORITHM-----------------------------------*/
int aux[MAXPRODS]; /* array used for auxiliary purposes */

void mergel(int ids[], int left, int mid, int right)
{ 

    int i, j, k;
    /* Puts elements in aux */
    for (i = mid+1; i > left; i--) {
        aux[i-1] = ids[i-1];
    }
    for (j = mid; j < right; j++) {
        aux[right+mid-j] = ids[j+1];
    }
    /* Checks left elements and right elements and compares them */
    for (k = left; k <= right; k++) {
        /* If price associated with pid that's in the right is less than the one in the left */
        /* Or i that starts with mid+1 is bigger than mid, in order to avoid stability loss */
        /* We swap them */
        if ((cmpPrice(aux[j], aux[i]) == LESS) || i > mid) {
            ids[k] = aux[j--];
        } 
        /* It's already sorted and put it in left side of ids */
        else {
            ids[k] = aux[i++];
        }
    }

}


/* Main call of the merge sort algorithm */
void mergeSortl(int ids[], int left, int right)
{

    if (left < right) 
    {
        int mid = left + (right - left) / 2;
        /* Break until we get 1 element arrays */
        mergeSortl(ids, left, mid);
        mergeSortl(ids, mid + 1, right);
        /* Then merge them and sort them */
        mergel(ids, left, mid, right);
    }

}

