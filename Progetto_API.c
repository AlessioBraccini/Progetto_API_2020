#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
    
    int** key;
    
    int postores, v, s, e, tracket;
    
    short valid;
    
    char c;
    
    struct node *next; 
    struct node* prev;
     
}op; 

typedef struct testo{
    
    char *txt;
    
    struct testo* next;
    
    
}righe;

short global = 0;

short seizero = 0;

int *res[300000];

int contop = 0;

int contot = 0;

int contu = 0;

int checkp = 0;

int v = 0;

int tracke = 0;

righe *primo;
righe *last;

op *ultimo;
op *ptru;

op * ope = NULL;

void freelista(){
    
    op *ptr;
    op *temp;
    
    short gg = 0;
    
    if(ultimo == NULL){
        
        ptr = ope;
        
        gg = 1;
    }
    
    /*else
        
        ptr = ultimo->next;
    
    while (ptr != NULL)
    { 
        temp = ptr;
        ptr = ptr -> next;
        free(temp);
    }*/
    
    if(gg == 1){
        
        ope = NULL;
        
        //tracke = 0;
        
    }
    
    return;
}

op * append(op * h, righe *a, int s, int e, char c, int tracke)
{
	op * n, * ptr;
        righe *txt;
        int i, opt, tracke2;
        
        i = 0;
        
	n = malloc(sizeof(op));
        
        n->s = s;
        
        if (c == 'c'){
        
            //inizio copia

            if (global == 0){

                n->key = malloc (v * sizeof(int*));

                while (i < e){

                    n->key[i] = a->txt;

                    res[i] = a->txt;

                    a = a->next;

                    i++;
                    
                }
                
                global = 1;
                
            }

            else{

                int ip = e-s+1;

                int contat;

                n->key = malloc (ip * sizeof(int*));

                txt = primo;

                if (v > s-1){                              //append in mezzo

                    for (opt = s-1, contat = 0; opt < e; opt++, txt = txt->next, contat++){

                        n->key[contat] = txt->txt;

                        res[opt] = txt->txt;

                    }

                }

                else{                                           //append in coda

                    for (opt = 0; opt < ip; opt++){

                        n->key[opt] = txt->txt;

                        res[opt+s-1] = txt->txt;

                        txt = txt->next;

                    }
                } 
            } 
   
            n->v = v;

            n->e = e;
            
            n->valid = 1;

            //fine copia
        }
        
        else{
            
            if (e > 0 && s >= 0){
            
                if (e != 0 && s <= tracke){

                    n->key = malloc (v * sizeof(int*));

                    for (i = 0; i < v; i++)

                        n->key[i] = *(&res[i]);


                    n->v = v;

                    n->e = e;

                    n->valid = 1;
                }
            
            
                else{
                    
                    n->valid = 0;
                    
                }
                
            }
            
        }
        if (n->valid == 1){
            
            if(c == 'd'){

                tracke2 = tracke - (e-s+1);

                if (tracke2 < 0)
                    tracke2 = 0;

                n->tracket = tracke2;
            }

            else 

                n->tracket = tracke;
        }
        
        else
            
            n->tracket = -1;

        n->next = NULL;

        if(!h){

            h = n;
            
            n->prev = NULL;
            
        }
        
        else{

            ptr = ultimo;

            n->prev = ultimo;
                
            ptr->next = n;
                  
        }
        
        n->c = c;
        
        ultimo = n;   
        
        contop++;
        
        contot++;
        
	return h;
}

righe * appendtxt(righe * h, int i)
{
	righe * n, * ptr;
        int y;
        
        char temp[1025];
        
        n = (righe *)malloc(sizeof(righe));
        
        gets(temp);
        
        y = strlen(temp);
        
        n->txt = malloc ((y+1)*sizeof(char));
        
        strcpy(n->txt, temp);
        
        n->next = NULL;

        if(!h)

            h = n;

        else{
            
            ptr = last;
            
            ptr->next = n;
        } 
        
        if (i == 0)
            primo = n;
        
        last = n;
        
	return h;

}

void undo(char c){
    
    int i, gg, pos, kk, contg;
    op *ptr, *ptr2;
    
    gg = 0;
    kk = 0;
    
    contg = -(contu - contop);
    
    for (ptru = ultimo, i = 0; i < contg && ptru != NULL && gg == 0; i++, ptru = ptru->prev)
        if (i+1 == contop)
            gg = 1;
   
    ptr2 = ptru;
    
    if(ptru->valid == 0){
            
        ultimo = ptru;

        while (ptr2->valid == 0){
            
            ptr2 = ptr2->prev;
            
            if(0 == ptr2){
                
                v = 0;
       
                ultimo = NULL;
                ptru = NULL;
                contop = 0;
                tracke = 0;
                
                if(c == 'd' || c == 'c'){
                            
                    freelista(ope);
                        
                }
                
                seizero = 1;
                
                return;
                
            }
                
            kk = 1;
        }
    }
    
    v = ptr2->v;
    
    if(ptr2->c == 'c'){
    
        if (ptr2->s == 1 && ptr2->e >= v){     //primo caso undo 

            for (i = 0; i < v; i++)

                *(&res[i]) = *(&ptr2->key[i]);

        }

        else{

            
            
            for (ptr = ope; ptr != ptr2->next; ptr = ptr->next){

                pos = ptr->s - 1;

                int kl = ptr->e - ptr->s + 1;
                
                if(ptr->c == 'c'){
                    
                    if (kl >= ptr->v)

                        for (i = 0; i < ptr->v; i++, pos++){

                            *(&res[pos]) = *(&ptr->key[i]);

                        }

                    else

                        for (i = 0; i < kl; i++, pos++){

                            *(&res[pos]) = *(&ptr->key[i]);

                        }
                }
                
                else {
                
                    for (i = 0; i < ptr->v; i++, pos++){

                        *(&res[i]) = *(&ptr->key[i]);

                    }
                }
            }
        }        
    }
    
    else {
        
        for (i = 0; i < v; i++, pos++){

            *(&res[i]) = *(&ptr2->key[i]);

        }
    }
    
    if (kk == 0)
        
        ultimo = ptr2;
    
    if (c == 'd' || c == 'c'){                            //free(ope);
        
        freelista();
        
    }
    
    contop = contop - contg;
    
    tracke = ptr2->tracket;

    return;
    
    //fare gli altri casi
    
}

void redo (int contr, char c){         //non va
    
    int i, j, pos, gg;
    op *ptr;
    
    gg = 0;
    
    if (ultimo == NULL)
        
        ptr = ope;
    
    else
        
        ptr = ptru->next;
    
    for (j = 0; j < contr && gg == 0; j++, ptr = ptr->next){
        
        if(ptr->next == NULL){
            
            gg = 1;
            
            if (ptr->valid == 1){
            
                v = ptr->v;
            
                tracke = ptr->tracket;

            }
            
            ultimo = ptr;
            
            ptru = ultimo;
            
            

        }
        
        if (ptr->valid == 1){

            v = ptr->v;

            tracke = ptr->tracket;
            
            pos = ptr->s - 1;

            int kl = ptr->e - ptr->s + 1;
            
            if (ptr->c == 'c'){
                
                if (kl >= v)

                    for (i = 0; i < v; i++, pos++)

                        *(&res[pos]) = *(&ptr->key[i]);

                else

                    for (i = 0; i < kl; i++, pos++)

                        *(&res[pos]) = *(&ptr->key[i]);
            }
            
            else {
                
                for (i = 0; i < ptr->v; i++, pos++){

                        *(&res[i]) = *(&ptr->key[i]);

                    }
            }
        }

    }
    
    if (gg == 0){
        
        if (ptr->prev->valid == 1){
        
            v = ptr->prev->v;          
        
            tracke = ptr->prev->tracket;
        
        }
        
        ultimo = ptr->prev;

        ptru = ultimo;
        
        
    }
    
    if (c == 'd' || c == 'c'){                            //free(ope);
        
        freelista();
        
    }
    
    contop = contop + j;
    
    return;
}

int main(){
    
    int i;
    
    int l, s, e, ctrl, ctrlr;
    
    char c, b, inp[20];
    
    righe * rig = NULL;
    ctrl = 0;
    
    gets(inp);
    if (inp[0] != (int)'q')
        sscanf(inp, "%d %c %d %c %*c", &s, &b, &e, &c);
    else
        return 0;

    while (c != 'q'){
        
        if (c == 'c' && b == ','){
            
            if(e > v)
                
                tracke = e;

            //conto dimensione array
            if (ope == 0)
                
                v = e - s + 1;
            
            else if(s > v)
                
                v = v + e - s + 1;
            
            else if (s <= v && e > v)
                
                v = e;
            
            //fine conto
            
            l = e - s + 1;
            
            for (i = 0; i < l; i++) //il +1 è per il punto

                rig = appendtxt (rig, i);
            
            scanf("%c", &b);
            scanf("%c", &b);

            contot = contop;
            
            ope = append(ope, rig, s, e, c, tracke);
                //da sistemare con append in mezzo dopo undo e redo
            
            checkp = 0;
            contu = contop;
            seizero = 0;
        }
        
        else if (c == 'p' && b == ','){
            i = s-1;
            
            if (i < 0)
                i = 0;
            
            if (s == 0 && e == 0)
                
                fputs(".\n", stdout);
            
            else if (v == 0)
                
                while (i != e){

                        fputs(".\n", stdout);
                        i++;

                    } 
            
            else{

                if (e <= v)       //p senza punti in fondo

                    while (i != e){                               

                        fputs(*(&res[i]), stdout);

                        fputs("\n", stdout);
                        
                        i++;

                    }

                else {                      //p con punti in fondo

                    while (i != v){
                        
                        fputs(*(&res[i]), stdout);

                        fputs("\n", stdout);

                        i++;
                    }

                    while (i != e){

                        fputs(".\n", stdout);
                        i++;

                    } 
                } 
            }
        }
        
        else if (c == 'd' && b == ','){
            
            if(e > v && s <= v )
                    e = v;
            
            int kl = e-s+1;
            
            if (e > 0 && s >= 0){
            
                if (e != 0 && s <= tracke){

                    if (s == 0)

                        s = 1;

                    v = v - kl;

                    if (v < 0)

                        v = 0;

                    else{

                        for (i = s-1; i < v; i++)

                            *(&res[i]) = *(&res[i+kl]);

                    }
                }
                
                
            }

            contot = contop;
            
            ope = append(ope, rig, s, e, c, tracke);
            
            if(ultimo->valid == 1)
                
                tracke = tracke - kl;

            if (tracke < 0)
                tracke = 0;

            checkp = 0;
            contu = contop;
            seizero = 0;

        }
        
        else if (b == 'u' || b == 'r'){
            
            int contg = 0;
            
            if(s > 0){
                
                ctrlr = 0;
                
                if(b == 'r'){
                    
                    int contr = 0;

                    if (checkp == 1){
                    
                        while (b == 'r'){  
                        
                            contr = contr + s;

                            gets(inp);
                            if (inp[0] != (int)'q')
                                sscanf(inp, "%d %c %d %c %*c", &s, &b, &e, &c);
                            else
                                return 0;
                        }
                        
                        if(b != 'u'){
                        
                            if (contop != contot){

                                if(contr > contot)

                                    contr = contot;

                                redo(contr, c);
                            }
                            
                        }
                        
                        else{
                            
                            contu = contu + contr;
                            
                            ctrlr = 1;
                         
                            if (contu > contot)
                                
                                contu = contot;
                            
                        }
                    }
                    
                    else{
                        
                        while (b == 'r'){
                            gets(inp);
                            if (inp[0] != (int)'q')
                                sscanf(inp, "%d %c %d %c %*c", &s, &b, &e, &c);
                            else
                                return 0;
                       } 
                    }
                }
                
                else{
                    
                    while (b == 'u' || b == 'r'){
                        
                        if(b == 'u'){
                            
                            contu = contu - s;
                            
                            if (contu < 0)
                                
                                contu = 0;
                            
                        }
                        
                        else{
                            
                            contu = contu + s;
                            
                            if (contu > contot)
                                
                                contu = contot;
                            
                        }
                        
                        gets(inp);
                        if (inp[0] != (int)'q')
                            sscanf(inp, "%d %c %d %c %*c", &s, &b, &e, &c);
                        else
                            return 0;
                    }
                    
                    if (b == ',')
                        checkp = 1;
                    
                    if (contu == 0){
                        
                        ptru = NULL;
                        ultimo = NULL;
                        v = 0;
                        contop = 0;
                        //tracke = 0;
                        
                        if(c == 'd' || c == 'c'){
                            
                            freelista();
                        
                        }
                        
                        seizero = 1;
                    }
                    
                    else{
                        
                        contg = -(contu - contop);
                        
                        if (contop < contu){
                        
                            if(contu > contot)
                                contu = contot;

                            redo(-contg, c);
                        }
                            
                        else
                            
                            if (contu != contop)
                                
                                undo(c);
                    
                    }                  
                }
            } 
            
            if(ctrlr == 0)
                
                contu = contop;
            
            ctrl = 1;
        }
        
        
        /*else if (c == 't'){

            for (i = 0;i < v;i++){
                
                fputs(*(&res[i]), stdout);
            
            }
            
            printf("%d, %d, %d", ultimo->s, ultimo->e, ultimo->v);
        }*/
        
        //gli undo vanno ma i redo no F

        if (ctrl == 0){

            gets(inp);
            if (inp[0] != (int)'q')
                sscanf(inp, "%d %c %d %c %*c", &s, &b, &e, &c);
            else
                return 0;
            
            if((c == 'd' || c == 'c') && seizero == 1){
                
                freelista();
                
            }
        }
        
        else
            
            ctrl = 0;

    }
    
    return (0);
}