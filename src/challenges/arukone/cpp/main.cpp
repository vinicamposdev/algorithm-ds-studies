#include <iostream>
#include <algorithm>
#include <array>
#include <vector>
#include <queue>

//Tamanho máximo do tabuleiro
#define tamanho_max 10000

using namespace std;

//Dimensão do tabuleiro
int tamanho;

//Estrutura para traduzir letras em numeros (cores)
typedef struct estrutura_cor {
  char caracter; //caracter para cor
  int  codigo; //valor inteiro para cor
} cores;

const cores traduzir_cores[16] = {
  {'0',0}, // ZEROW
  {'A',1}, // AMEIXA
  {'B',2}, // BLUE
  {'C',3}, // CYAN
  {'D',4}, // DARK
  {'E',5}, // ESMERALDA
  {'F',6}, // FERRUGEM
  {'G',7}, // GREEN
  {'H',8}, // HORTELÃ
  {'I',9}, // INDIGO
  {'J',10}, // JALEEBEEN
  {'K',11}, // KUSKUIS
  {'L',12}, // LIGHT
  {'M',13}, // MAROON
  {'N',14}, // NIGHT
  {'O',15}, // ORANGE
};

//Tradutor para cor
int tradutor_cor(char c) {
  for (int i=0; i<16; ++i) {
    if (traduzir_cores[i].caracter == c) {
      return i;
    }
  }
  return -1;
}

//Estrutura do tabuleiro
struct Node{
    array<int, tamanho_max> flow = {0};
    vector<Node*> proximo;
    array<bool, tamanho_max> sucesso = {false};

    vector<int>::iterator aux_marcar;
    int profundidade = 0;
    int id = 0;
};

//Funções
Node* entrada_arquivo();
void saida(Node* node);
void vizinho(Node* root);
void criar_resultado(Node* root);

Node* newNode(Node*, int, int, int, int);

queue<Node*> fqueue;
vector<int> priority;
int node_id;

Node* entrada_arquivo() {
    Node* node = new Node;
    string aux;
    char aux_char;

	scanf("%d",&tamanho);//Lê o tamanho do tabuleiro
    int contador = 0;
    for (int i=1; i<tamanho+1; i++) {
        for(int j= 0; j < tamanho; j++) {
            scanf(" %c", &aux_char);//lê os componentes do tabuleiro
            node->flow[contador] = tradutor_cor(aux_char);//faz a conversão para cor com o tradutor
            contador++;
        }
    }
    return node;
}

//Saida (print) do programa
void saida(Node* node) {
    for (int i=0; i<tamanho*tamanho; i++) {
        cout << traduzir_cores[node->flow[i]].caracter;
        if (i%tamanho==tamanho-1)
            cout << endl;
    } 
}
 
void aux(Node* no_atual,vector<vector<int>>::iterator possivel, array<int, tamanho_max> caminho) {
        for (int i=0; i<tamanho_max; i++) {
        if (no_atual->flow[i]) {
            (*possivel) = {i, no_atual->flow[i], 0};

            if (i%tamanho !=0 && no_atual->flow[i-1] == 0)
                (*possivel)[2]++;

            if (i%tamanho !=tamanho-1 && no_atual->flow[i+1] == 0)
                (*possivel)[2]++;

            if (i/tamanho !=0 && no_atual->flow[i-tamanho] == 0)
                (*possivel)[2]++;

            if (i/tamanho !=tamanho-1 && no_atual->flow[i+tamanho] == 0)
                (*possivel)[2]++;

            caminho[(*possivel)[1] -1] += (*possivel)[2];
            advance(possivel, 1);
        }
    }
}

void vizinho(Node* root) {
    vector<vector<int>> caminho_possivel(2*tamanho, vector<int>(3, 0));
    vector<vector<int>>::iterator possivel = caminho_possivel.begin();
    array<int, tamanho_max> caminho = {0};
    Node* no_atual = root;

    aux(no_atual, possivel, caminho);

    sort(caminho_possivel.begin(), caminho_possivel.end(), [caminho](const vector<int>& v1, const vector<int>& v2){
        if (v1[2] == v2[2])
            return caminho[v1[1] -1] < caminho[v2[1] -1];

        return v1[2] < v2[2];
    });

    for (const auto& possivel: caminho_possivel) {
        if (find(priority.begin(), priority.end(), possivel[1])  == priority.end()) {
            priority.push_back(possivel[1]);
            no_atual->flow[possivel[0]] = possivel[1] + tamanho;
        }
    }
    no_atual->aux_marcar = priority.begin();
}

Node* newNode(Node* no_atual, int no_atual_index, int new_index, int success_mask, int node_id) {
    Node* node = new Node;
    node->flow = no_atual->flow;
    node->flow[new_index] = no_atual->flow[no_atual_index];

    node->sucesso = no_atual->sucesso;
    if (success_mask)
        node->sucesso[success_mask -1] = true;

    node->aux_marcar = no_atual->aux_marcar;
    node->profundidade = no_atual->profundidade +1;
    node->id = node_id;

    return node;
}

void criar_resultado(Node* root) {
    Node* no_atual = root;
    fqueue.push(root);
    
    // enquanto a pilha estiver cheia e todos os elementos de sucesso do no atual forem verdadeiros
    while ( !fqueue.empty() && !all_of(no_atual->sucesso.begin(), no_atual->sucesso.end(), [](bool i){ return i; }) ) {
        // no atual é atribuido ao primeiro elemento da fila
        no_atual = fqueue.front();
        // é removido esse elemento da vila
        fqueue.pop();

        // e o iterador auxiliar for falso
        if (!*(no_atual->aux_marcar))
            break;  

        // para cada elemento da matriz faça
        for (int i=0; i<tamanho_max; i++) {
            // se o no atual ter o mesmo valor que o auxiliar faça
            if (no_atual->flow[i] == *(no_atual->aux_marcar)) {
                // se o valor da iteração estiver na primeira coluna
                // e se o vizinho anterior do no atual for igual ao no analizado somado ao tamanho
                if (i%tamanho !=0 && no_atual->flow[i-1] == no_atual->flow[i] + tamanho) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i-1, no_atual->flow[i], node_id);
                    advance(node->aux_marcar, 1);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                    break;
                }
                // se o valor da iteração não for da primeira coluna mas ser o imediatamente anterior a n
                // e se o vizinho próximo do no atual for igual ao no analizado somado ao tamanho
                if (i%tamanho !=tamanho-1 && no_atual->flow[i+1] == no_atual->flow[i] + tamanho) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i+1, no_atual->flow[i], node_id);
                    advance(node->aux_marcar, 1);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                    break;
                }
                // se o valor da iteração estiver na ultima coluna
                // e se o vizinho próximo do no atual for igual ao no analizado somado ao tamanho
                if (i/tamanho !=0 && no_atual->flow[i-tamanho] == no_atual->flow[i] + tamanho) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i-tamanho, no_atual->flow[i], node_id);
                    advance(node->aux_marcar, 1);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                    break;
                }

                if (i/tamanho !=tamanho-1 && no_atual->flow[i+tamanho] == no_atual->flow[i] + tamanho) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i+tamanho, no_atual->flow[i], node_id);
                    advance(node->aux_marcar, 1);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                    break;
                }
								
                if (i%tamanho !=0 && no_atual->flow[i-1] == 0) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i-1, 0, node_id);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                }
								
                if (i%tamanho !=tamanho-1 && no_atual->flow[i+1] == 0) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i+1, 0, node_id);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                }
								
                if (i/tamanho !=0 && no_atual->flow[i-tamanho] == 0) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i-tamanho, 0, node_id);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                }
								
                if (i/tamanho !=tamanho-1 && no_atual->flow[i+tamanho] == 0) {
                    node_id++;
                    Node* node = newNode(no_atual, i, i+tamanho, 0, node_id);
                    no_atual->proximo.push_back(node);
                    fqueue.push(node);
                }
            }
        }
    }
    saida(no_atual);
}

int main() {
    Node* root = entrada_arquivo();
    vizinho(root);
    printf("%d\n", tamanho);
    criar_resultado(root);
    return 0;
}