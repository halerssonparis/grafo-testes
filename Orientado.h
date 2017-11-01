#ifndef ORIENTADO_H_INCLUDED
#define ORIENTADO_H_INCLUDED
#include <vector>
#include <windows.h>

using namespace std;

class Grafo_Simples {
public:

    string type;
    vector<vector<int> > matriz_adj;
    vector<vector<string> > lista_adj;
    //ATUALIZAÇÃO || TROCAR <STRING> NOMES (CRIAR UMA STRUCT {NOMES E GRAU}
    vector<int> grau_vertice;
    vector<string> nomes;
    bool seAchou = false;

    Grafo_Simples (string type) {
        this->type = type;
    }

    int retorna_grau(string origem)
    {
        int _origem = -1;

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i] == origem) {
                _origem = i;
            }
        }

        if (_origem != -1 ) {
            cout<<grau_vertice.at(_origem);
        }
    }

    void inserir_vertice(string nome) {

        if (retorna_vertice(nome)) { return; }

        nomes.push_back(nome);

        for (int i = 0; i < matriz_adj.size(); i++) {
            matriz_adj.at(i).push_back(0);
        }
        matriz_adj.push_back(vector<int>(matriz_adj.size() + 1));

        vector<string> add;
        add.push_back(nome);
        lista_adj.push_back(add);
        grau_vertice.push_back(0);
    }

    void remover_vertice (string nome) {
        int posicao;

        for(int i = 0; i < nomes.size(); i++) {
            if (this->nomes.at(i) == nome) {
                posicao = i;
                break;
            }
        }
        matriz_adj.erase(matriz_adj.begin()+posicao);
        nomes.erase(nomes.begin() + posicao);

        for(int i = 0; i < matriz_adj.size()-1; i++) {
            matriz_adj.at(i).erase(matriz_adj.at(i).begin()+posicao);
        }

        lista_adj.erase(lista_adj.begin()+posicao);
        grau_vertice.erase(grau_vertice.begin()+posicao);

        for(int i = 0; i < lista_adj.size(); i++){
            for(int j = 0; j < lista_adj.at(i).size(); j++){
                if (lista_adj.at(i).at(j) == nome) {
                    lista_adj.at(i).erase(lista_adj.at(i).begin() + j);
                    grau_vertice.at(i) -= 1;
                }
            }
        }
    }

    void inserir_ligacao(string origem, string destino) {
        if (nomes.empty()){ return; }

        int _origem = -1, _destino = -1;
        bool seExisteArcoLista = false;

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i] == origem) {
                _origem = i;
            }
            if (nomes[i] == destino) {
                _destino = i;
            }
        }

        if (_origem == -1 || _destino == -1) {
            return;
        }

        for (int i = 1; i < lista_adj.at(_origem).size(); i++){
            if (lista_adj.at(_origem).at(i) == destino) {
                seExisteArcoLista = true;
                break;
            }
        }

        //AQUI VERIFICAR QUAL DOS DOIS TIPO DO GRAFO É:
        if (type == "orientado")
        {
            //Verifica se foi inserido na o _destino List_adj
            //COMEÇA EM 1 PORQUE O 1º REPESENTA A LETRA E NÃO A LIGAÇÃO
            matriz_adj.at(_origem).at(_destino)= 1;
            if (!seExisteArcoLista)
            {
                grau_vertice.at(_origem) += 1;
                grau_vertice.at(_destino) += 1;
                lista_adj.at(_origem).push_back(destino);
            }
        }

        else if (type == "nao orientado"){

            matriz_adj.at(_origem).at(_destino)= 1;
            matriz_adj.at(_destino).at(_origem)= 1;
            if (!seExisteArcoLista) {
                grau_vertice.at(_origem) += 1;
                grau_vertice.at(_destino) += 1;
                lista_adj.at(_origem).push_back(destino);
                lista_adj.at(_destino).push_back(origem);
            }
        }
    }

    void remove_ligacao(string origem, string destino) {
        int _origem = -1, _destino = -1;
        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i] == origem) {
                _origem = i;
            }
            if (nomes[i] == destino) {
                _destino = i;
            }
        }
        if (_origem != -1 && _destino != -1)
        {
            if (type == "orientado") {
                if( matriz_adj.at(_origem).at(_destino) != 0) {
                    grau_vertice.at(_origem) -= 1;
                    grau_vertice.at(_destino) -= 1;
                }
                matriz_adj.at(_origem).at(_destino) = 0;
            }
            else if (type == "nao orientado") {
                if( matriz_adj.at(_origem).at(_destino) != 0) {
                    grau_vertice.at(_origem) -= 1;
                    grau_vertice.at(_destino) -= 1;
                }
                matriz_adj.at(_origem).at(_destino) = 0;
                matriz_adj.at(_destino).at(_origem) = 0;
            }

            //ESSE FOR É SÓ PRA TIRAR DA LISTA (POR ISSO NÃO PRECISA DIMINUIR O GRAU)
            for (int i = 0; i < lista_adj.at(_origem).size(); i++){
                if (lista_adj.at(_origem).at(i) == destino) {
                    lista_adj.at(_origem).erase(lista_adj.at(_origem).begin() + i);
                }
            }
        }
    }

    //RETORNO NAO É BOOLEAN
    bool retorna_vertice (string nome) {
        for (int i = 0; i < nomes.size(); i++) {
            if (nome == nomes.at(i)) { return true; }
        }
        return false;
    }

    bool existe_ligacao(string origem, string destino) {
        int _origem = -1, _destino = -1;
        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i] == origem) {
                _origem = i;
            }
            if (nomes[i] == destino) {
                _destino = i;
            }
        }
        if (_origem != -1 && _destino != -1) {
            if (matriz_adj.at(_origem).at(_destino) != 0){ return true; }
            else { return false;}
        }
        else { return false; }
    }

    //ARRRUMAR, FAZER ELE RETORNAR APARTIR DA LISTA_ADJ
    vector<string> retorna_arcos(string nome) {
        vector<string> lista_vertice_adj;
        for ( int i = 0; i < nomes.size(); i++) {
            if (nome == nomes.at(i)) {
                for (int j = 0; j < matriz_adj.size(); j++){
                    if (matriz_adj.at(i).at(j) != 0) {
                        lista_vertice_adj.push_back(nomes.at(j));
                    }
                }
                break;
            }
        }
        return lista_vertice_adj;
    }

     vector<int> retorna_arcos_inteiro(string nome) {
        vector<int> lista_vertice_adj;
        for ( int i = 0; i < nomes.size(); i++) {
            if (nome == nomes.at(i)) {
                for (int j = 0; j < matriz_adj.size(); j++){
                    if (matriz_adj.at(i).at(j) != 0) {
                        lista_vertice_adj.push_back(j);
                    }
                }
                break;
            }
        }
        return lista_vertice_adj;
    }


    void busca_Profundidade_recursiva(string origem, int vertice, vector<bool> &visitados) {
        vector<int> adj = retorna_arcos_inteiro(origem);

        for (int i = 0; i < adj.size(); i++) {
            if (visitados.at(adj.at(i)) == false) {
                cout << nomes[adj[i]] <<"\n";
                visitados[adj[i]] = true;
                busca_Profundidade_recursiva(nomes.at(adj[i]), adj[i], visitados);
            }
        }
    }

    //def sem destino.
    void busca_Profundidade(string origem) {
        system("CLS");
        if (!retorna_vertice(origem))
            return;

        int _origem = 0;

        vector<bool> visitados;
        for (int i = 0; i < nomes.size(); i++) {
            visitados.push_back(false);
        }

        for (int i = 0; i < nomes.size(); i++) {
            if ( nomes.at(i) == origem) {
                _origem = i;
                break;
            }
        }

        visitados.at(_origem) = true;
        cout << nomes.at(_origem) << "\n";

        busca_Profundidade_recursiva(origem, _origem, visitados);
    }




    void busca_Profundidade_recursiva_com_destino(string origem, int vertice, vector<bool> &visitados, string destino, int _destino) {
        vector<int> adj = retorna_arcos_inteiro(origem);

        for (int i = 0; i < adj.size(); i++) {
            if (visitados.at(adj.at(i)) == false && seAchou == false) {
                if (nomes.at(adj.at(i)) == destino) {
                    visitados[adj[i]] = true;
                    seAchou = true;
                    return;
                }
                else {
                    cout << nomes[adj[i]] <<"\n";
                    visitados[adj[i]] = true;
                    busca_Profundidade_recursiva_com_destino(nomes.at(adj[i]), adj[i], visitados, destino, _destino);
                }
            }
        }
    }

    //def com destino
    void busca_Profundidade_com_destino(string origem, string destino) {
        system("CLS");
        if (!retorna_vertice(origem) || !retorna_vertice(destino))
            return;

        int _origem = 0, _destino;

        vector<bool> visitados(nomes.size(), false);

        for (int i = 0; i < nomes.size(); i++) {
            if ( nomes.at(i) == origem) {
                _origem = i;
                break;
            }
            if ( nomes.at(i) == origem) {
                _destino = i;
                break;
            }
        }

        visitados.at(_origem) = true;
        cout << nomes.at(_origem) << "\n";

        busca_Profundidade_recursiva_com_destino(origem, _origem, visitados, destino, _destino);
    }


    void busca_largura_recursiva(string origem, int vertice, vector<bool> &visitados) {
        vector<int> adj = retorna_arcos_inteiro(origem);
        vector<int> guarda_adjs;

        for (int i = 0; i < adj.size(); i++) {
            if (visitados.at(adj.at(i)) == false) {
                cout << nomes[adj[i]] <<"\n";
                visitados[adj[i]] = true;
                guarda_adjs.push_back(adj[i]);
            }
        }

        for (int i = 0; i < guarda_adjs.size(); i++ ){
             busca_largura_recursiva(nomes.at(guarda_adjs.at(i)), guarda_adjs.at(i), visitados);
        }
    }

    void busca_largura (string origem) {
        system("CLS");
        if (!retorna_vertice(origem))
            return;

        int _origem = 0;

        vector<bool> visitados(nomes.size(), false);

        for (int i = 0; i < nomes.size(); i++) {
            if ( nomes.at(i) == origem) {
                _origem = i;
                break;
            }
        }

        visitados.at(_origem) = true;
        cout << nomes.at(_origem) << "\n";

        busca_largura_recursiva(origem, _origem, visitados);
    }



    void busca_largura_recursiva_com_destino (string origem, int vertice, vector<bool> &visitados, string destino) {
        vector<int> adj = retorna_arcos_inteiro(origem);
        vector<int> guarda_adjs;

        for (int i = 0; i < adj.size(); i++) {
            if (visitados.at(adj.at(i)) == false) {
                if (nomes.at(adj.at(i)) == destino) {
                    cout << nomes[adj[i]] <<"\n";
                    visitados[adj[i]] = true;
                    seAchou = true;
                    return;
                }
                else {
                    cout << nomes[adj[i]] <<"\n";
                    visitados[adj[i]] = true;
                    guarda_adjs.push_back(adj[i]);
                }
            }
        }

        for (int i = 0; i < guarda_adjs.size(); i++ ){
            if (!seAchou)
                busca_largura_recursiva(nomes.at(guarda_adjs.at(i)), guarda_adjs.at(i), visitados);
        }
    }

    void busca_largura_com_destino (string origem, string destino) {
        system("CLS");
        if (!retorna_vertice(origem))
            return;

        int _origem = 0, _destino;

        vector<bool> visitados(nomes.size(), false);

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes.at(i) == origem) {
                _origem = i;
            }
            if (nomes.at(i) == destino) {
                _destino = i;
            }
        }

        visitados.at(_origem) = true;
        cout << nomes.at(_origem) << "\n";

        busca_largura_recursiva_com_destino(origem, _origem, visitados, destino);
    }



    void print_grafo() {
        for (int i = 0; i < matriz_adj.size(); i++) {
            cout<<"\n";
            for (int j = 0; j < matriz_adj.size(); j++) {
                cout<<matriz_adj.at(i).at(j)<<" ";
            }
        }
        cout<<"\n"; cout<<"\n";cout<<"\n";

        for (int i = 0; i < lista_adj.size(); i++) {
            cout<<"\n";
            for (int j = 0; j < lista_adj.at(i).size(); j++) {
                if (j == 0 ) { cout<<lista_adj.at(i).at(j)<<": "; }
                else { cout<<lista_adj.at(i).at(j)<<" "; }
            }
        }
    }
};

#endif // ORIENTADO_H_INCLUDED
