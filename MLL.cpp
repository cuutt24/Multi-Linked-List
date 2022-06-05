//nama:afriza tri rizki
//kelas:informatika-b
//SDA MLL
#include <iostream>
using namespace std;
//Multi linkedlist dengan menggunakan double linkedlist

//mendefinisikan tipe dari Child
struct Child{
    int number;

    Child (int num){
        this->number = num;
    }
};
struct NodeChild{
    Child* info;
    NodeChild* next;
    NodeChild* prev;
};
//akhir dari definisi child
struct ListChild{
    NodeChild* first;
};
//mendefiniskan tipe dari Parent
struct Parent{
    int number;
    
    Parent(int num){
        this->number = num;
    }
};

struct NodeParent{
    Parent* info;
    NodeParent* next;
    NodeParent* prev;
    ListChild* childNumb;
};
//akhir dari definisi parent
struct ListParent{
    NodeParent* first;
};

//menambah node/data kedalam list parent
void addDataParent(ListParent* list, int num){
    NodeParent* node = new NodeParent();
    Parent* add = new Parent(num);
    node->info = add;
    if (list->first == NULL){
        list->first = node;
    }else{
        node->next = list->first;
        node->prev = NULL;
        list->first->prev = node;
        list->first = node;
    }
}

//menambah node/data kedalam list child 
void addDataChild(ListChild* list, int numb, NodeChild* addnode = NULL){
    if (numb != 0){
        NodeChild* node = new NodeChild();
        Child* add = new Child(numb);
        node->info = add;
        if (list->first == NULL){
            list->first = node;
        }else{
            node->next = list->first;
            node->prev = NULL;
            list->first->prev = node;
            list->first = node;
        }
    } 
    else if(addnode!= NULL){
        if(list->first == NULL){
            list->first = addnode;
        }
        else{
            addnode->next = list->first;
            addnode->prev = NULL;
            list->first->prev = addnode;
            list->first = addnode; 
        }
    }   
}

//menghapus node/data yang ada didalam suatu list child
void delParent(ListParent* list, int dataParent){
    NodeParent* key = NULL, *prev = NULL , *curP = list->first;
    bool found = false;
    if(curP->info->number == dataParent){
        list->first = curP->next;
        curP->next = NULL;
        return;
    }else{
        while (curP != NULL){
            if (!found){
                dataParent = curP->next->info->number;
            }
            if (!found){
                prev = curP;
                found = true;
            }
            if(dataParent == curP->info->number){
                key = curP;
            }
            curP = curP->next;            
        }
        if (key != NULL && prev != NULL){
            prev->next = key->next;
            key->next = NULL;
        }
    }
}

//menghapus node/data yang ada didalam suatu list child
void delChild(ListChild* list, int dataChild){
    NodeChild* key = NULL, *prev = NULL, *curC = list->first;
    bool found = false;
    if(curC->info->number == dataChild){
        list->first = curC->next;
        curC->next = NULL;
        return;
    }else{
        while (curC != NULL){
            if(!found){
                dataChild = curC->info->number;
            }
            if(!found){
                prev = curC;
                found = true; 
            }
            if(dataChild == curC->info->number){
                key = curC;
            }
            curC = curC->next;
        }
        if(key != NULL && prev != NULL){
            prev->next = key->next;
            key->next = NULL;
        }       
    }
}

//mencari node data dalam list Parent
NodeParent* searchDataParent(ListParent* list, int data){
    NodeParent* curP = list->first;
    while (curP != NULL){
        if(data == curP->info->number){
            return curP;
        }
        curP = curP->next;
    }
    return NULL;       
}
//mencari node data dalam list child
NodeChild* searchDataChild(ListChild* list, int data){
    NodeChild* curC = list->first;
    while (curC != NULL){
        if(data == curC->info->number){
            return curC;
        }
        curC = curC->next;
    }
    return NULL;
}

//menambahkan relasi pada data parent dan dijadikan list child
//data list child didapat dari list child yg sudah diinput sebelumnya
void addRelationData(ListParent* listP, ListChild* listC, int dataParent, int dataChild){
    NodeParent* p;
    NodeChild* c,*r;
    ListChild* newlistRelation;

    p = searchDataParent(listP,dataParent);
    c = searchDataChild(listC, dataChild);

    if (p != NULL  && c != NULL){
        r = new NodeChild();
        r->info = c->info;
        if(p->childNumb == NULL){
            newlistRelation = new ListChild();
        }else{
            newlistRelation = p->childNumb;
        }
        p->childNumb = newlistRelation;
        addDataChild(newlistRelation, 0 , r);
    }
}

//menghapus relasi pada data parent, yang telah diinput sebelumnya
void delReationData(ListParent* listP, ListChild* listC, int dataParent, int dataChild){
    NodeParent* p;
    ListChild* lChild;

    p = searchDataParent(listP, dataParent);
    if(p != NULL && p->childNumb != NULL){
        lChild = p->childNumb;
        delChild(lChild,dataChild);
    }
}

//menampilkan data yg telah dimasukan
void printList(ListParent* p = NULL, ListChild* c = NULL){
    if (p != NULL){
        NodeParent* curP = p->first;
        cout<< "Parent Data : \n";
        while(curP != NULL){
           cout<< curP->info->number;
           if (curP->childNumb != NULL){
               NodeChild* curP_child = curP->childNumb->first;
               cout<< " ---- Child Data : ";
               while (curP_child != NULL){
                   cout<<curP_child->info->number;
                   curP_child = curP_child->next;
               }
                cout<<endl;                   
           }
           curP = curP->next;
           cout<<endl;
        } 
    }
    if(c != NULL){
        NodeChild* curC = c->first;
        cout<<"Data Child : " <<endl;
        while (curC != NULL) {
            cout << curC->info->number << "\t" << endl;
            curC = curC->next;
        }
        cout << endl;
    }
}

int main(){
    ListParent* dataP = new ListParent();
    ListChild* dataC = new ListChild();
    addDataParent(dataP,11);
    printList(dataP,dataC);
    
    addDataParent(dataP,13);
    printList(dataP,dataC);
    
    addDataParent(dataP,20);
    printList(dataP,dataC);
    
    addDataChild(dataC,12);
    printList(dataP,dataC);
    
    addDataChild(dataC,14);
    printList(dataP,dataC);

    addDataChild(dataC,18);
    printList(dataP,dataC);
    
    addRelationData(dataP,dataC,20,12);
    printList(dataP,dataC);

    addRelationData(dataP,dataC,13,12);
    printList(dataP,dataC);
   
    delReationData(dataP,dataC,11,18);
    printList(dataP,dataC);

    delChild(dataC,14);
    printList(dataP,dataC);

    delParent(dataP, 13);
    printList(dataP,dataC);
}