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
    nodo* find2(int posicion, int version, int campo);
    void add(int v);
    void add2(nodo* temp, int campo, int valor, int version);
    void add_def(int opcion);
    void del(int v);
    ~LE();
};

void LE::print()
{
    int i;
    cout << "Head->";
    for (nodo* p = head; p; p = p->next) {
        if (p->vect.size() > 0)
            i = p->vect.size() - 1;
        cout << p->vect[i].first << "->";
    }
        
    cout << "NULL" << endl;
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


nodo* LE::find2(int posicion, int version, int campo)
{
    bool encontrado = false;
    nodo* pos = nullptr;
    nodo* p;
    int i;
    for (p = head, i = 0; p && i < posicion; p = p->next,i++)
    {
        pos = p;
        
    }
    
    return p;
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

void LE::add2(nodo* temp, int campo, int valor, int version) {
    ///=valor, 2=puntero
    int opcion_;
    if (campo == 1) {
        cout << "1. Conservar la verion y cambiar el valor" << endl;
        cout << "2. Crear una nueva version" << endl;
        cin >> opcion_;
        if (opcion_ == 1) {
            cout << "Valor a cambiar: " << temp->vect[version].first << endl;
            temp->vect[version].first = valor;
        }
        
        if (opcion_ == 2) {
            nodo* temp_ = temp->next;
            nodo* nuevo = new nodo(valor, temp_);
            
            temp->vect.push_back(make_pair(valor, nuevo));
            nuevo->next = temp_;
        }
    }

    if (campo == 2) {
        cout << "Se creara una nueva version del nodo" << endl;
        if (temp->next != nullptr) {
            nodo* temp2 = temp->next;
            int temp__ = temp->vect[version].first;
            nodo* nuevo = new nodo(valor, temp2);
            temp->next = nuevo;
            temp->vect.push_back(make_pair(temp__, nuevo));
            nuevo->next = temp2;
        }
    }
}

void LE::add_def(int opcion) {
    if (opcion == 1) {
        int valor1;
        cout << "Digite un numero" << endl;
        cin >> valor1;
        add(valor1);
    }

    if (opcion == 2) {
        int posi, campo, num, version;
        cout << "Ingrese la posicion del nodo a modificar" << endl;
        cin >> posi;
        cout << endl << "Ingrese la version a modificar" << endl;
        cin >> version;
        cout << endl << "Ingrese el campo del nodo a modificar (1=valor, 2=puntero)" << endl;
        cin >> campo;
        cout << endl << "Digite el numero" << endl;
        cin >> num;

        nodo* temp = find2(posi,version, campo);
        cout << "NOdo en que estamos: " << temp->vect[version].first << endl;
        add2(temp, campo, num, version);
       
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
    int dato, opcion_insertar, datoaeliminar;
    do {
        cout << "\t         MENU" << endl;
        cout << "1. Insertar elemento en la lista" << endl;
        cout << "2. Eliminar un elemento de la lista" << endl;
        cout << "3. Mostrar elementos en la lista" << endl;
        cout << "4. Salir" << endl;
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1: cout << "1. Desea poner el elemento al final de la lista"<<endl;
            cout << "2. Desea modificar un nodo en la lista" << endl;
            cin >> dato;
            lista.add_def(dato);
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
