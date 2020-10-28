#include <iostream>


struct Node  {
    char  ID;       //  Nodens id/key/data
    Node* naboer[10]; //  Nodens naboer (ligger i indeks nr. 0 - 9)
    int   antNaboer; //  Antall naboer (max. 10 stk)
    bool  besokt;   //  Om besøkt noden hittil eller ei

    Node(char id, int antNaboer) {
        ID = id;
        this->antNaboer = antNaboer;
    }
};

Node* kopier(Node* node);
void brettUt(Node* node);




void brettUt(Node* node) {
    /* For loop som går igjennom hver nabo til noden.
     * Jeg kunne lagt til en if setning som sjekket om noden finnes, men siden for loopen bare
     * kjøres når det finnes naboer trengs ikke det så lenge antNaboer er riktig.
     */
    for(int i = 0; i < node->antNaboer; i++) {
        //Sjekker om naboen er besøkt, Hvis naboen er besøkt vil den bli erstattet med en kopi.
        if(node->naboer[i]->besokt) {
            node->naboer[i] = kopier(node->naboer[i]);
        }
        //Deretter sier vi at naboen er besøkt.
        node->naboer[i]->besokt = true;
        //Går gjennom hele treet rekursivt.
        brettUt(node->naboer[i]);
    }
}

Node* kopier(Node* node)  {
    Node* kopi = new Node(node->ID, node->antNaboer);
    for (int i = 0;  i < node->antNaboer;  i++)
        kopi->naboer[i] = kopier(node->naboer[i]);
    return kopi;
}

void traverseTree(Node* node) {
    std::cout << "Barn til " << node->ID << ": ";
    for(int i = 0; i < node->antNaboer; i++) {
        std::cout << node->naboer[i]->ID << ": " << node->naboer[i] << " ";
    }
    std::cout << "\n";
    for(int i = 0; i < node->antNaboer; i++) {
        traverseTree(node->naboer[i]);
    }

}

int main() {
    Node* a = new Node('A', 2);
    Node* b = new Node('B', 1);
    Node* c = new Node('C', 2);
    Node* d = new Node('D', 1);
    Node* e = new Node('E', 0);
    a->naboer[0] = b;
    a->naboer[1] = c;
    b->naboer[0] = d;
    c->naboer[0] = d;
    c->naboer[1] = e;
    d->naboer[0] = e;

    brettUt(a);

    traverseTree(a);
    return 0;
}
