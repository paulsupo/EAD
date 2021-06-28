#include <iostream>
#include <vector>
using namespace std;

class nodo
{
public:
    int valor;
    nodo* next;
    vector<pair<int, nodo* > >vect;
    nodo(int v, nodo* n = nullptr)
    {
        valor = v;
        next = n;
        vect.push_back(make_pair(valor,next));
    }
};

class LE
{
    nodo* head = nullptr;

public:
    void print();
    bool find(int v, nodo*& pos);
    bool find2(int posicion, int version, int campo);
    void add(nodo *temp, int campo, int v);
    void del(int v);
    ~LE();
};

void LE::print()
{
    cout << "Head->";
    for (nodo* p = head; p; p = p->next)
        cout << p->valor << "->";
    cout << "NULL" << endl;
}

bool LE::find2(int posicion, int version, int campo)
{
    bool encontrado = false;
    nodo* pos = nullptr;
    for (nodo* p = head, int i=0; p && i< posicion; p = p->next)
    {
        if (p->valor == valor)
        {
            encontrado = true;
            break;
        }
        pos = p;
        //cout<<pos->valor<<endl;
    }

}


bool LE::find(int v, nodo*& pos)
{
    bool encontrado = false;
    pos = nullptr;

    for (nodo* p = head; p ; p = p->next)
    {
        if (p->valor == v)
        {
            encontrado = true;
            break;
        }
        pos = p;
        //cout<<pos->valor<<endl;
    }
    return encontrado;
}

void LE::add(int v)
{
    nodo* pos_ant;
    if (!find(v, pos_ant))
    {
        if (pos_ant)
        {
            pos_ant->next = new nodo(v, pos_ant->next);
        }
        else
        {
            head = new nodo(v, head);
        }
    }
}

void LE::del(int v)
{
    nodo* pos_ant, * pos_del;
    if (find(v, pos_ant))
    {
        if (pos_ant)
        {
            pos_del = pos_ant->next;
            pos_ant->next = pos_del->next; //pos_ant->next = pos_ant->next->next;
            delete pos_del;
        }
        else
        {
            pos_del = head;
            head = pos_del->next; //head = head->next;
            delete pos_del;
        }
    }
}

LE::~LE()
{
    while (head)
        del(head->valor);
}


LE lista;

void menu() {
    int opcion;
    int dato, datoaeliminar;
    do {
        cout << "\t         MENU" << endl;
        cout << "1. Insertar elemento en la lista" << endl;
        cout << "2. Eliminar un elemento de la lista" << endl;
        cout << "3. Mostrar elementos en la lista" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: cout << "\nDigite un numero: ";
            cin >> dato;
            lista.add(dato);
            system("pause");
            break;
        case 2: cout << "\nEscriba el dato a eliminar: ";
            cin >> datoaeliminar;
            lista.del(datoaeliminar);
            system("pause");
            break;
        case 3: lista.print();
            system("pause");
            break;
        }
        system("cls");

    } while (opcion != 4);
}



int main() {
    menu();
    return 0;

}