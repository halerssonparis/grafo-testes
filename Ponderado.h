#ifndef PONDERADO_H_INCLUDED
#define PONDERADO_H_INCLUDED
#include <vector>
#include <queue>

using namespace std;

struct Path {
    int anterior;
    int distancia;
    int aberto;

    Path(){
        anterior = -1;
        distancia = -1;
        aberto = false;
    }

};

struct ComparePair {
    bool operator()(pair<int, int> p1, pair<int, int> p2){
        return p1.first > p1.first;
    }
};


struct soluction {
    int a;
    int b;
    int peso;
};
struct spanning_tree_prim{
    vector<soluction> soluctions;
    vector<int> control;
};
struct arvore {
    int index;
    int floresta_pertencente;
};
struct spanning_tree_kruskal {
    vector<soluction> soluctions;
    vector<soluction> control;
    vector<arvore> floresta;
};

struct vertice {
    string nome;
    int cor = -1;
    int saturacao = 0;
    int grau = 0;

    string anterior = "nao atribuido";
    int distancia = 99999;
    bool checked = false;
};

struct lista_adj_peso {
    int peso = 0;
    string nome;
};

class Grafo_Ponderado {
public:
    string type;
    vector<vector<int> > matriz_adj;
    vector<vertice> nomes;
    vector<vector<lista_adj_peso> > lista_adj;
    vector<soluction> ligacao;

    Grafo_Ponderado (string type) {
        this->type = type;
    }

    void retonar_grau(string origem) {

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i].nome == origem) {
                cout<<"Total: "<<nomes.at(i).grau<<"\n";
                return;
            }
        }
    }

   void inserir_vertice(string nome) {
        vertice v;
        v.nome = nome;
        nomes.push_back(v);

        for (int i = 0; i < matriz_adj.size(); i++) {
            matriz_adj.at(i).push_back(0);
        }
        matriz_adj.push_back(vector<int>(matriz_adj.size() + 1));

        vector<lista_adj_peso> add;
        lista_adj_peso add2;
        add2.nome = nome;
        add.push_back(add2);
        lista_adj.push_back(add);
    }

    void remover_vertice (string nome) {
        int posicao;

        for(int i = 0; i < matriz_adj.size(); i++) {
            if (this->nomes.at(i).nome == nome) {
                posicao = i;
                break;
            }
        }

        for(int i = 0; i < matriz_adj.size(); i++) {
            matriz_adj.at(i).erase(matriz_adj.at(i).begin()+posicao);
        }

        matriz_adj.erase(matriz_adj.begin()+posicao);
        lista_adj.erase(lista_adj.begin() + posicao);
        nomes.erase(nomes.begin() + posicao);

        for(int i = 0; i < lista_adj.size(); i++){
            for(int j = 1; j < lista_adj.at(i).size(); j++){
                if (lista_adj.at(i).at(j).nome == nome) {
                    lista_adj.at(i).erase(lista_adj.at(i).begin() + j);
                    nomes.at(i).grau -= 1;
                }
            }
        }
    }

    void inserir_ligacao(string origem, string destino, int peso) {
        if (nomes.empty()) { return; }

        int _origem = -1, _destino = -1;
        bool existe_aresta;

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i].nome == origem) {
                _origem = i;
            }
            if (nomes[i].nome == destino) {
                _destino = i;
            }
        }
        if (_origem == -1 || _destino == -1) { return; }

        for (int i = 0; i < lista_adj.at(_origem).size(); i++) {
            if (lista_adj.at(_origem).at(i).nome == destino) {
                existe_aresta = true;
                break;
            }
        }

        if (type == "nao orientado")
        {
            matriz_adj.at(_origem).at(_destino) = peso;
            matriz_adj.at(_destino).at(_origem) = peso;

            if(!existe_aresta) {
                nomes.at(_origem).grau += 1;
                nomes.at(_destino).grau += 1;

                lista_adj_peso add2;
                add2.nome = destino;
                add2.peso = peso;
                lista_adj.at(_origem).push_back(add2);
                add2.nome = origem;
                lista_adj.at(_destino).push_back(add2);

                soluction l;
                l.a = _origem;
                l.b = _destino;
                l.peso = peso;
                ligacao.push_back(l);
            }
        }
        else if (type == "orientado") {
            matriz_adj.at(_origem).at(_destino) = peso;

            if(!existe_aresta) {
                nomes.at(_origem).grau += 1;
                nomes.at(_destino).grau += 1;

                lista_adj_peso add2;
                add2.nome = destino;
                add2.peso = peso;
                lista_adj.at(_origem).push_back(add2);
                add2.nome = origem;
                lista_adj.at(_destino).push_back(add2);
            }
        }
    }

    void remover_ligacao(string origem, string destino) {
        int _origem = -1, _destino = -1;

        for (int i = 0; i < nomes.size(); i++) {
            if (nomes[i].nome == origem) {
                _origem = i;
            }
            if (nomes[i].nome == destino) {
                _destino = i;
            }
        }
        if (_origem != -1 && _destino != -1) {
            if (type == "nao orientado") {
                matriz_adj.at(_origem).at(_destino)= 0;
                matriz_adj.at(_destino).at(_origem)= 0;
                nomes.at(_origem).grau -= 1;
                nomes.at(_destino).grau -= 1;

                //ESSE FOR É SÓ PRA TIRAR DA LISTA (POR ISSO NÃO PRECISA DIMINUIR O GRAU)
                for (int i = 0; i < lista_adj.at(_origem).size(); i++){
                    if (lista_adj.at(_origem).at(i).nome == destino) {
                        lista_adj.at(_origem).erase(lista_adj.at(_origem).begin() + i);
                        lista_adj.at(_destino).erase(lista_adj.at(_destino).begin() + i);
                    }
                }
            }
            else if (type == "orientado"){
                matriz_adj.at(_origem).at(_destino)= 0;
                nomes.at(_origem).grau -= 1;
                nomes.at(_destino).grau -= 1;

                //ESSE FOR É SÓ PRA TIRAR DA LISTA (POR ISSO NÃO PRECISA DIMINUIR O GRAU)
                for (int i = 0; i < lista_adj.at(_origem).size(); i++){
                    if (lista_adj.at(_origem).at(i).nome == destino) {
                        lista_adj.at(_origem).erase(lista_adj.at(_origem).begin() + i);
                    }
                }
            }
        }
    }

    //retorno nao é boolean
    int retornar_vertice(string nome) {
        for (int i = 0; i < nomes.size(); i++) {
            if(nome == nomes.at(i).nome) {
                return i;
            }
        }
    }
    /*bool retonar_vertice_bool(string nome) {
        for (int i = 0; i < nomes.size(); i++) {
            if(nome == nomes.at(i).nome) {
                return true;
            }
        }
    }*/

    vector<int> obterVerticesAdj(int origem){
        vector <int> lista;
        for(lista_adj_peso current: lista_adj[origem]){
            lista.push_back(retornar_vertice(current.nome));
        }
        return lista;
    }

    bool existe_ligacao(string origem, string destino) {
        int _origem = -1, _destino = -1;

        for (int i = 0; i < nomes.size(); i++){
            if (origem == nomes.at(i).nome){ _origem = i; }
            if (destino == nomes.at(i).nome) { _destino = i; }
        }

        if (_origem != -1 && _destino != -1) {
            if(matriz_adj.at(_origem).at(_destino) != 0) { return true; }
        }
        else { return false; }
    }

    vector<string> retorna_aresta(string nome) {
        vector<string> lista_adj_vertice;

        for (int i = 0; i < nomes.size(); i++){
            if (nome == nomes.at(i).nome) {
                for (int j = 0; j < matriz_adj.size(); j++) {
                    if (matriz_adj.at(i).at(j) != 0){
                        lista_adj_vertice.push_back(nomes.at(i).nome);
                    }
               }
               return lista_adj_vertice;
            }
        }
    }

     void print_grafo() {

        for (int i = 0; i < matriz_adj.size(); i++) {
                cout<<"\n";
            for (int j = 0; j < matriz_adj.size(); j++) {
                cout<<matriz_adj.at(i).at(j)<<" ";
            }
        }

        cout<<"\n";

        for (int i = 0; i < lista_adj.size(); i++){
                cout<<"\n";
            for (int j = 0; j < lista_adj.at(i).size(); j++){
                if(j == 0) { cout<<lista_adj.at(i).at(j).nome<<":"; }
                else { cout<<"| "<<lista_adj.at(i).at(j).nome<<" "<<this->lista_adj.at(i).at(j).peso <<" |"; }
            }
        }
    }


    bool vizinhos_cores_diferente(int cor, vector<lista_adj_peso> lista_aux, vector<vertice> nomes_aux ) {
        for (unsigned int i = 1; i < lista_aux.size(); i++) {
            for (unsigned int j = 0; j < nomes_aux.size(); j++) {
                if (lista_aux.at(i).nome == nomes_aux.at(j).nome){
                    if (nomes_aux.at(j).cor == cor) {
                        return false;
                    }
                }
            }
        }
        return true;
    }

    void welsh_powell() {
        vector<vector<lista_adj_peso> > lista_aux = lista_adj;
        vector<vertice> nomes_aux = nomes;
        int opc_cores[6] = {1,2,3,4,5,6};
        int controle_de_cor = 0;

        //BUBBLE SORT
        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            for (unsigned int j = 0; j < nomes_aux.size()-1; j++) {
                if (nomes_aux.at(j).grau < nomes_aux.at(j+1).grau) {
                    swap(nomes_aux.at(j), nomes_aux.at(j+1));
                    swap (lista_aux.at(j), lista_aux.at(j+1));
                }
            }
        }

        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            controle_de_cor++;
            for (unsigned int j = 0; j < nomes_aux.size(); j++) {
                if (nomes_aux.at(j).cor == -1) {
                    if (vizinhos_cores_diferente(controle_de_cor, lista_aux.at(j), nomes_aux)) {
                        nomes_aux.at(j).cor = controle_de_cor;
                    }
                }
            }
        }

        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            cout<<nomes_aux.at(i).cor<<nomes_aux.at(i).nome<<" :"<<nomes_aux.at(i).grau<<"\n";
        }
    }



     void aumenta_saturacao_vizinhos(int cor, vector<lista_adj_peso> lista_aux, vector<vertice> &nomes_aux ) {
        for (unsigned int i = 1; i < lista_aux.size(); i++) {
            for (unsigned int j = 0; j < nomes_aux.size(); j++) {
                if (lista_aux.at(i).nome == nomes_aux.at(j).nome && nomes_aux.at(j).saturacao != -1){
                    nomes_aux.at(j).saturacao++;
                }
            }
        }
    }
    void dsatur() {
        vector<vector<lista_adj_peso> > lista_aux = lista_adj;
        vector<vertice> nomes_aux = nomes;
        int opc_cores[6] = {1,2,3,4,5,6};
        int controle_de_cor = 0;

        //BUBBLE SORT
        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            for (unsigned int j = 0; j < nomes_aux.size()-1; j++) {
                if (nomes_aux.at(j).grau < nomes_aux.at(j+1).grau) {
                    swap(nomes_aux.at(j), nomes_aux.at(j+1));
                    swap (lista_aux.at(j), lista_aux.at(j+1));
                }
            }
        }
        int _ref_maior_saturacao = 0;
        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            //FOR J É PARA ACHAR O VERTICE COM MAIOR SATURAÇÃO;
            for (unsigned int j = 0; j < nomes_aux.size(); j++) {
                while (nomes_aux.at(_ref_maior_saturacao).cor != -1){
                    _ref_maior_saturacao++;
                }
                if (nomes_aux.at(j).saturacao > nomes_aux.at(_ref_maior_saturacao).saturacao &&
                    nomes_aux.at(j).cor == -1)
                {
                    _ref_maior_saturacao = j;
                }
            }

            do {
                if (vizinhos_cores_diferente(controle_de_cor, lista_aux.at(_ref_maior_saturacao), nomes_aux)) {
                    aumenta_saturacao_vizinhos(controle_de_cor, lista_aux.at(_ref_maior_saturacao), nomes_aux);
                    nomes_aux.at(_ref_maior_saturacao).cor = controle_de_cor;
                }
                else {
                    controle_de_cor++;
                }
            } while (nomes_aux.at(_ref_maior_saturacao).cor == -1);
            controle_de_cor = 0;
            _ref_maior_saturacao = 0;
        }

        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            cout<<nomes_aux.at(i).cor<<nomes_aux.at(i).nome<<" :"<<nomes_aux.at(i).grau<<" sat->"<<nomes_aux.at(i).saturacao<<"\n";
        }
    }

    void atribui_caminho (vector<vertice> &nomes_aux, vector<lista_adj_peso> lista_aux) {
        for (unsigned int i = 1; i < lista_aux.size();i++) {
            for (unsigned int j = 0; j < nomes_aux.size(); j++) {
                cout<<lista_aux.at(i).nome<<" == "<<nomes_aux.at(j).nome<<" "<<!nomes_aux.at(j).checked<<" "<<nomes_aux.at(j).distancia<<" > "<<lista_aux.at(i).peso<<"\n";
                int acu = 0;
                for (int t = 0; t < nomes_aux.size(); t++) {
                    if (nomes_aux.at(t).nome == lista_aux.at(0).nome){
                        acu = nomes_aux.at(t).distancia;
                    }
                }
                if (lista_aux.at(i).nome == nomes_aux.at(j).nome
                    && !(nomes_aux.at(j).checked)
                    && nomes_aux.at(j).distancia > lista_aux.at(i).peso + acu)
                {
                    //LISTA NA POSICAO 0 TEM O NOME DO VERTICE QUE ESTA SENDO VERIFICADO

                    nomes_aux.at(j).anterior = lista_aux.at(0).nome;
                    if (nomes_aux.at(j).distancia == 99999) {
                        nomes_aux.at(j).distancia = 0;
                    }
                    nomes_aux.at(j).distancia = lista_aux.at(i).peso + acu;
                    cout<<nomes_aux.at(j).nome<<" recebe :  ";
                    cout<<lista_aux.at(0).nome<<"-<kepo ";
                    cout<<nomes_aux.at(j).distancia<<"\n";
                }
            }
                cout<<"\n";
        }
    }

    void dijkstra (string origem) {
        vector<vertice> nomes_aux = nomes;
        vector<vector<lista_adj_peso> > lista_aux = lista_adj;
        int proximo_vertice = 0;
        int gambiarra = 0;

        for (unsigned int i = 0; i < nomes.size(); i++) {
            if (origem == nomes.at(i).nome && i != 0) {
                swap(nomes_aux.at(i), nomes_aux.at(0));
                swap(lista_aux.at(i), lista_aux.at(gambiarra));
                nomes_aux.at(0).distancia = 0;
            }
        }

        for (unsigned int i = 0; i < nomes_aux.size(); i++) {
            cout<<i<<" "<<lista_aux.at(proximo_vertice).at(0).nome<<"\n";
            atribui_caminho (nomes_aux, lista_aux.at(proximo_vertice));
            nomes_aux.at(proximo_vertice).checked = true;

            if (lista_aux.at(proximo_vertice).size() >= 3) {
                for (unsigned int j = 1; j < lista_aux.at(proximo_vertice).size() - 1; j++){
                    for (unsigned int k = j+1; k < lista_aux.at(proximo_vertice).size(); k++) {
                        if (lista_aux.at(proximo_vertice).at(j).peso > lista_aux.at(proximo_vertice).at(k).peso ) {
                            for (unsigned int l = 0; l < nomes_aux.size(); l++) {
                                if (nomes_aux.at(l).nome == lista_aux.at(proximo_vertice).at(k).nome && !(nomes_aux.at(l).checked)) {
                                    cout<<"L = "<<l<<"\n";
                                    proximo_vertice = l;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            else {
                for (unsigned int j = 0; j < nomes_aux.size(); j++){
                    if (lista_aux.at(i).at(1).nome == nomes_aux.at(j).nome) {
                        cout<<"segundo for: "<<lista_aux.at(i).at(1).nome<<" == "<<nomes_aux.at(j).nome<<"\n";
                        proximo_vertice = j;
                    }
                }
            }
        }
        for (unsigned int j = 0; j < nomes_aux.size(); j++){
            cout<<nomes_aux.at(j).nome<<" "<<nomes_aux.at(j).anterior<<" "<<nomes_aux.at(j).distancia<<"\n";
        }

    }

    int consultarPeso(int origem, int destino){
        for(lista_adj_peso atual: lista_adj[origem]){
            if(retornar_vertice(atual.nome) == destino){
                return atual.peso;
            }
        }

    }


    vector<Path> dijkstra2(int origem, int destino = -1){
        vector <Path> lista(nomes.size());

        priority_queue <pair<int, int>, vector<pair<int, int> >, ComparePair> pq;

        int backup = origem;

        lista[origem].distancia = 0;
        lista[origem].anterior = -1;

        pq.push(make_pair(lista[origem].distancia, origem));

        while(!pq.empty()){
            origem = pq.top().second;

            if(origem == destino){
                return lista;
            }

            pq.pop();
            lista[origem].aberto = false;

            for(int atual: obterVerticesAdj(origem)){
                if(lista[atual].distancia == -1 || (lista[atual].distancia > consultarPeso(origem, atual) + lista[origem].distancia)) {
                    lista[atual].distancia = consultarPeso(origem, atual) + lista[origem].distancia;
                    lista[atual].anterior = origem;
                }
                if (lista[atual].aberto == true) {
                    pq.push(make_pair(lista[atual].distancia, atual));
                }
            }
        }

        for (int i = 0; i < lista.size(); i++) {
            if (i == backup) { lista[i].anterior = backup; }
            cout<<lista.at(i).distancia<<"ant: "<<lista.at(i).anterior<<"\n";
        }
        return lista;
    }


    bool esta_conectado (int vertice, vector<unsigned int> out_control) {
        if(out_control.empty())
            return true;

        for (int vertice_out : out_control) {
            if (vertice_out == vertice) {
                return true;
            }
        }
        return false;
    }

    void prim (unsigned int origem) {
        spanning_tree_prim stp;
        vector<unsigned int> out_control;

        for (vertice _vertice : nomes) {
            if (origem == retornar_vertice(_vertice.nome))
                out_control.push_back(retornar_vertice(_vertice.nome));
            else
                stp.control.push_back(retornar_vertice(_vertice.nome));
        }

        while (!stp.control.empty()) {
            unsigned int vertice_a, ligacao_menor_peso;
            bool primeira_iteracao = true;

            for (unsigned int vertice_atual : out_control) {
                vector<int> vertices_adjacentes_atual = obterVerticesAdj(vertice_atual);

                for (unsigned int adjacente_atual : vertices_adjacentes_atual) {
                    if (!esta_conectado(adjacente_atual, out_control)) {
                        if (primeira_iteracao) {
                            vertice_a = vertice_atual;
                            ligacao_menor_peso = adjacente_atual;
                            primeira_iteracao = false;
                        }
                        else {
                            if (consultarPeso(vertice_atual, adjacente_atual) <
                            consultarPeso(vertice_a, ligacao_menor_peso))
                            {
                                vertice_a = vertice_atual;
                                ligacao_menor_peso = adjacente_atual;
                            }
                        }
                    }
                }
            }

            soluction add_soluction;
            add_soluction.a = vertice_a;
            add_soluction.b = ligacao_menor_peso;
            stp.soluctions.push_back(add_soluction);

            out_control.push_back(ligacao_menor_peso);

            for (unsigned int i = 0; i < stp.control.size(); i++) {
                if (stp.control.at(i) == ligacao_menor_peso)
                    stp.control.erase(stp.control.begin() + i);
            }
        }

        for (soluction solucao : stp.soluctions)
            cout<<solucao.a<<" "<<solucao.b<<"\n";
    }

    bool _sort(soluction i, soluction j) { return i.peso > j.peso; }

    spanning_tree_kruskal init_tree() {
        spanning_tree_kruskal stp;
        stp.control = ligacao;

        for (vertice vertice_atual : nomes){
            arvore add;
            add.index = retornar_vertice(vertice_atual.nome);
            add.floresta_pertencente = retornar_vertice(vertice_atual.nome);
            stp.floresta.push_back(add);
        }

        //sort(stp.control.begin(), stp.control.end(), _sort);

        for (int i = 0; i < stp.control.size(); i++) {
            for (int j = 0; j < stp.control.size()-1; j++) {
                if (stp.control.at(j).peso > stp.control.at(j+1).peso) {
                    swap(stp.control.at(j), stp.control.at(j+1));
                }
            }
        }
        return stp;
    }

    void kruskal () {
        spanning_tree_kruskal stp = init_tree();

        for (int i = 0; i < stp.control.size(); i++) {
            if (stp.floresta.at(stp.control.at(i).a).floresta_pertencente != stp.floresta.at(stp.control.at(i).b).floresta_pertencente) {
                stp.soluctions.push_back(stp.control.at(i));

                int floresta_b = stp.floresta.at(stp.control.at(i).b).floresta_pertencente;
                for(arvore &arvore : stp.floresta){
                    if (arvore.floresta_pertencente == floresta_b)
                        arvore.floresta_pertencente = stp.floresta.at(stp.control.at(i).a).floresta_pertencente;
                }
            }
        }

        for (soluction t : stp.soluctions) {
            cout<<"\n"<<t.a<<" "<<t.b<<":"<<t.peso;
        }
    }

    bool tem_ciclo () {
        for (int i = 0; i < lista_adj.size(); i++) {
            for (int j = 1; j < lista_adj.at(i).size(); j++) {
                int k = retornar_vertice(lista_adj.at(i).at(j).nome);
                for (int l = 1; l < lista_adj.at(k).size(); l++) {
                    int m = retornar_vertice(lista_adj.at(k).at(l).nome);
                    for (int n = 1; n < lista_adj.at(m).size(); m++) {
                        if (lista_adj.at(m).at(n).nome == lista_adj.at(i).at(0).nome)
                            return true;
                    }
                }
            }
        }
        return false;
    }

    bool verifica_planaridade() {
        if (nomes.size() <= 2) {
            cout<<"é planar";
            return true;
        }
        else if ((nomes.size() >= 3) &&
                 (ligacao.size() <= (3 * nomes.size())-6) &&
                 (tem_ciclo())) {
            cout<<"pode ser planar";
            return true;
        }
        else if ((nomes.size() >= 3) &&
                 (ligacao.size() <= (2 * nomes.size())-4) &&
                 (!tem_ciclo())) {
            cout<<"pode ser planar";
            return true;
        }
        cout<<"não é planar";
        return false;
    }
};

#endif // PONDERADO_H_INCLUDED
