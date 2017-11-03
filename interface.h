#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include "Orientado.h"
#include "Ponderado.h"
#include <windows.h>

using namespace std;

void interface_Simples();
void interface_Ponderado();

void sistema() {
    int opc;

    while (true) {
        system("CLS");

        cout<<"Escolha o tipo do Grafo para criar: \n1- Simples \n2- Ponderado \n";
        cin>>opc;
        if (opc == 1) {
            interface_Simples();
        }
        else if (opc == 2) {
            interface_Ponderado();
        }
    }
}

Grafo_Simples retorna_tipo () {
    system ("cls");
    int opc2;
    cout<<"1- Orientado \n2- Nao Orientado\n";
    cin>>opc2;
    if (opc2 == 1) {
        Grafo_Simples g("orientado");
        return g;
    }
    if (opc2 == 2) {
        Grafo_Simples g("nao orientado");
        return g;
    }
}


Grafo_Ponderado retorna_tipo2 () {
    system ("cls");
    int opc2;
    cout<<"1- Orientado \n2- Não Orientado\n";
    cin>>opc2;
    if (opc2 == 1) {
        Grafo_Ponderado g("orientado");
        return g;
    }
    if (opc2 == 2) {
        Grafo_Ponderado g("nao orientado");
        return g;
    }
}

void interface_Simples() {

    string nome = "";
    string origem = "";
    string destino = "";
    vector<string> vec;
    Grafo_Simples g = retorna_tipo();

    g.inserir_vertice("A");
    g.inserir_vertice("B");
    g.inserir_vertice("C");
    g.inserir_vertice("D");
    g.inserir_vertice("E");
    g.inserir_vertice("F");

    g.inserir_ligacao("B", "A");
    g.inserir_ligacao("B", "C");
    g.inserir_ligacao("A", "C");
    g.inserir_ligacao("A", "B");
    g.inserir_ligacao("C", "F");
    g.inserir_ligacao("D", "C");
    g.inserir_ligacao("F", "A");
    g.inserir_ligacao("F", "D");
    g.inserir_ligacao("F", "E");
    g.inserir_ligacao("E", "D");

    while (true) {
        system("CLS");
        cout<<"#### ESTE É UM GRAFO: "<<g.type<<"\n";
        cout<<"\n";

        cout<<"1- Adicionar Vertice \n";
        cout<<"2- Remover Vertice \n";
        cout<<"3- Adicionar Ligacao \n";
        cout<<"4- Remover Ligacao \n";
        cout<<"5- Retornar Vertice \n";
        cout<<"6- Procurar por ligacao \n";
        cout<<"7- Retornar ligacao \n";
        cout<<"8- Busca por Profundidade \n";
        cout<<"9- Busca por Profundidade com destino \n";
        cout<<"10- Busca por Largura \n";
        cout<<"11- Busca por Largura com destino \n";
        cout<<"12- Print Grafo \n";
        cout<<"13- Retonar Grau de um Vertice\n";

        g.print_grafo();
        int opc;
        cin>>opc;

        switch (opc) {
            case 01:
                system("CLS");
                cout<<"Digite o nome do vertice a ser adicionado\n";
                cin>>nome;
                g.inserir_vertice(nome);

                break;
            case 02:
                system("CLS");
                cout<<"Digite o nome do vertice a ser removido\n";
                cin>>nome;
                g.remover_vertice(nome);
                break;
            case 03:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;
                g.inserir_ligacao(origem, destino);
                break;
            case 04:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;
                g.remove_ligacao(origem, destino);
                break;
            case 05:
                cout<<"Escolha o nome de um vertice: \n:";
                cin>>origem;
                cout<<g.retorna_vertice(origem);
                break;
            case 06:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;

                if (g.existe_ligacao(origem, destino)) { cout<<"\nExiste Ligação entre: "<<origem<<" e "<<destino; }
                else { cout<<"Não Existe Ligação entre: "<<origem<<" e "<<destino<<"\n"; }
                system ("PAUSE");

                break;
            case 07:
                system("CLS");

                cout<<"Digite o nome do vertice: \n";
                cin>>nome;
                vec = g.retorna_arcos(nome);
                cout<<"\nArcos relacionados: ";
                for (int i = 0; i < vec.size(); i++) {
                    cout<<vec.at(i)<<" ";
                }
                cout<<"\n";
                system("PAUSE");
                break;
            case 8:
                cout<<"Escolha um vertice pra começar: \n";
                cin>>nome;
                g.busca_Profundidade(nome);
                system("PAUSE");
                break;
            case 9:
                cout<<"Escolha um vertice pra começar: \n";
                cin>>nome;
                cout<<"Escolha um destino: \n";
                cin>>destino;
                g.busca_Profundidade_com_destino(nome, destino);
                g.seAchou = false;
                system("PAUSE");
                break;
            case 10:
                cout<<"Escolha um vertice origem para a busca: ";
                cin>>origem;
                g.busca_largura(origem);
                system("PAUSE");
                break;
            case 11:
                cout<<"Escolha um vertice pra começar: \n";
                cin>>nome;
                cout<<"Escolha um destino: \n";
                cin>>destino;
                g.busca_largura_com_destino(nome, destino);
                g.seAchou = false;
                system("PAUSE");
                break;
            case 12:
                system("CLS");
                g.print_grafo();
                system("PAUSE");
                break;
            case 13:
                system ("CLS");
                cout<<"Escolha o nome do vertice: ";
                cin>>origem;
                g.retorna_grau(origem);
                system("PAUSE");
        }
    }
}


void interface_Ponderado () {
    int opc = 0, peso = 0;
    string nome = "";
    string origem = "";
    string destino = "";
    vector<string> vec;
    Grafo_Ponderado g = retorna_tipo2();

   /* g.inserir_vertice("A");
    g.inserir_vertice("B");
    g.inserir_vertice("C");
    g.inserir_vertice("D");
    g.inserir_vertice("E");

    g.inserir_ligacao("B", "A", 2);
    g.inserir_ligacao("B", "C", 2);
   // g.inserir_ligacao("B", "D", 2);
    g.inserir_ligacao("B", "E", 2);
    g.inserir_ligacao("A", "D", 2);
    g.inserir_ligacao("D", "E", 2);
    g.inserir_ligacao("E", "C", 2);*/


    /*g.inserir_vertice("A"); //0
    g.inserir_vertice("B"); //1
    g.inserir_vertice("C"); //2
    g.inserir_vertice("D"); //3
    g.inserir_vertice("E"); //4
    g.inserir_vertice("F"); //5

    g.inserir_ligacao("A", "E", 10);
    g.inserir_ligacao("A", "D", 2);
    g.inserir_ligacao("A", "C", 7);
    g.inserir_ligacao("D", "E", 7);
    g.inserir_ligacao("D", "F", 4);
    g.inserir_ligacao("E", "F", 8);
    g.inserir_ligacao("E", "C", 9);
    g.inserir_ligacao("C", "B", 3);
    g.inserir_ligacao("F", "B", 2);
    g.inserir_ligacao("F", "C", 3);*/

    g.inserir_vertice("A");
    g.inserir_vertice("B");

    g.inserir_ligacao("A", "B", 3);

    while (true) {
        system("CLS");
        cout<<"#### ESTE É UM GRAFO: "<<g.type<<"\n";

        cout<<"1- Adicionar Vertice \n";
        cout<<"2- Remover Vertice \n";
        cout<<"3- Adicionar Ligacao \n";
        cout<<"4- Remover Ligacao \n";
        cout<<"5- Retornar Vertice \n";
        cout<<"6- Procurar por Ligações \n";
        cout<<"7- Retornar Ligação \n";
        cout<<"8- Print Grafo \n";
        cout<<"9- Retorna Grau de um Vertice\n";
        cout<<"10- welsh\n";
        cout<<"11- Dsatur\n";
        cout<<"12- Dijkstra\n";
        cout<<"13- prim\n";
        cout<<"14- Kruskal\n";
        cout<<"15- verificar planaridade\n";
        g.print_grafo();

        cin>>opc;

        switch (opc) {
            case 01:
                system("CLS");
                cout<<"Digite o nome do vertice a ser adicionado\n";
                cin>>nome;
                g.inserir_vertice(nome);

                break;
            case 02:
                system("CLS");
                cout<<"Digite o nome do vertice a ser removido\n";
                cin>>nome;
                g.remover_vertice(nome);
                break;
            case 03:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;
                cout<<"Digite o peso do vertice\n";
                cin>>peso;
                g.inserir_ligacao(origem, destino, peso);
                break;
            case 04:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;
                g.remover_ligacao(origem, destino);
                break;
            case 05:
                cout<<"Digite o nome: \n";
                cin>>origem;
                //g.retonar_vertice(origem);
                break;
            case 06:
                system("CLS");
                cout<<"Digite o vertice de origem \n";
                cin>>origem;
                cout<<"Digite o vertice de destino\n";
                cin>>destino;

                if (g.existe_ligacao(origem, destino)) { cout<<"\nExiste Ligação entre: "<<origem<<" e "<<destino; }
                else { cout<<"Não Existe Ligação entre: "<<origem<<" e "<<destino<<"\n"; }
                system ("PAUSE");

                break;
            case 07:
                system("CLS");

                cout<<"Digite o nome do vertice: \n";
                cin>>nome;
                vec = g.retorna_aresta(nome);
                cout<<"\nArcos relacionados: ";
                for (int i = 0; i < vec.size(); i++) {
                    cout<<vec.at(i)<<" ";
                }
                cout<<"\n";
                system("PAUSE");
                break;
            case 8:
                system("CLS");
                g.print_grafo();
                system("PAUSE");
                break;
            case 9:
                system("CLS");
                cout<<"Escolha o nome do Vertice:";
                cin>>origem;
                g.retonar_grau(origem);
                system("PAUSE");
                break;
            case 10:
                system("CLS");
                g.welsh_powell();
                system("PAUSE");
                break;
            case 11:
                system("CLS");
                g.dsatur();
                system("PAUSE");
                break;
            case 12:
                system("CLS");

                g.dijkstra2(5,3);
                system("PAUSE");
                break;
            case 13:
                system("CLS");
                g.prim(2);
                system("PAUSE");
                break;
            case 14:
                system("CLS");
                g.kruskal();
                system("PAUSE");
                break;
            case 15:
                system("CLS");
                g.verifica_planaridade();
                system("PAUSE");
                break;
        }
    }
}

#endif // INTERFACE_H_INCLUDED
