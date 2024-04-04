#include "product.h"


#define MAXTAM_NAME 64

struct product
{
    char name[MAXTAM_NAME];
    float price;
    float discount;
    int qtd;
    int sales;
};

Product *product_constructor(const char *name, float price, int qtd){

    if(price < 0 || qtd < 0){
        printf("VALOR INVALIDO\n");
        return NULL;
    }

    Product* p = (Product*)calloc(1,sizeof(Product));

    strcpy(p->name,name);
    p->price = price;
    p->qtd = qtd;

    return p;
}

const char *product_get_name(Product *p){
    return p->name;
}
float product_get_price(Product *p){
    return p->price;
}
float product_get_discount(Product *p){
    return p->discount;
}
int product_get_qtd(Product *p){
    return p->qtd;
}
int product_get_sales(Product *p){
    return p->sales;
}

void product_set_name(Product *p, const char *name){
    strcpy(p->name,name);
}
void product_set_price(Product *p, float price){
    if(price < 0){
        printf("VALOR INVALIDO\n");
        return;
    }
    p->price = price;
}
void product_set_discount(Product *p, float discount){
    if(discount < 0 || discount > 1){
        printf("VALOR INVALIDO\n");
        return;
    }
    p->discount = discount;
}

void product_sell(Product *p, int quantity){
    if(quantity > p->qtd){
        printf("ESTOQUE INSUFICIENTE\n");
        return;
    }
    if(quantity<0){
        printf("QUANTIDADE INVALIDA\n");
        return;
    }
    p->qtd -= quantity;
    p->sales += quantity;
}
void product_buy(Product *p, int quantity){
    if(quantity<0){
        printf("QUANTIDADE INVALIDA\n");
        return;
    }
    
    p->qtd += quantity;
}

float product_get_price_with_discount(Product *p){
    float pwd = p->price * (1.0 - p->discount);
    
    return pwd;
}
void product_print(Product *p){
    printf("Product(%s, %.2f, %.2f, %.2f, %d, %d)\n",
                p->name, p->price, p->discount,
                product_get_price_with_discount(p),p->qtd, p->sales);
}

void product_destructor(Product *p){
    if(p!=NULL) free(p);
}

int product_compare_name(void* produto1, void* produto2){
    Product* p1 = *((Product**)produto1);
    Product* p2 = *((Product**)produto2);

    printf("VAIDAMERDA");
    printf("%s || %s || TESTE\n",product_get_name(p1),product_get_name(p2));

    return strcmp(p1->name,p2->name);
}

int product_compare_price(void* produto1, void* produto2){
    Product* p1 = *((Product**)produto1);
    Product* p2 = *((Product**)produto2);

    if(p1->price > p2->price) return 1;
    if(p1->price < p2->price) return -1;
    return 0;
}

int product_compare_sales(void* produto1, void* produto2){
    Product* p1 = *((Product**)produto1);
    Product* p2 = *((Product**)produto2);

    if(p1->sales > p2->sales) return 1;
    if(p1->sales < p2->sales) return -1;
    return 0;
}