/* Classe Fila encadeada
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>
#include <stdexcept>

using namespace std;

struct Dado {
    string nome;
    string premio;
    char tipo;
    int tempo;
};

// Imprime as informações de um dado qualquer
void imprimir_dado(const Dado& umDado) {
    cout << "Nome: "<< umDado.nome << " Premio: " << umDado.premio << " Tipo: " << umDado.tipo << " tempo: "<< umDado.tempo << endl;
}

class Noh {
    friend class Fila;
    private:
        Dado mDado; // poderia ser outro tipo de variável
        Noh* mProx;
    public:
        Noh(Dado v) {
            mDado = v;
            mProx = NULL;
        }        
};

class Fila {
    public:
        // Constrói Fila vazia.
        Fila();
        // Destrutor que desaloca memória.
        ~Fila();
        // Retira e retorna o elemento que estiver na frente da Fila.
        // Escreve uma mensagem de erro se não for possível desenfileirar.
        Dado Desenfileirar(); 
        // Insere um elemento na Fila.
        void Enfileirar(const Dado& d);
        // Apagar todos os dados da Fila.
        void LimparTudo();
        // Retorna o elemento que está na frente da Fila, sem desenfileirar.
        inline void Primeiro();

        inline void Topo();
        
        int Contabilizar( char type );
        // Informa se a Fila está Vazia.
        inline bool Vazia();
    private:
        Noh* mPtPrimeiro;
        Noh* mPtrUltimo;
};

Fila::Fila() {
    mPtPrimeiro = NULL;
    mPtrUltimo = NULL;
}

Fila::~Fila() {
    LimparTudo();
}

Dado Fila::Desenfileirar() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    Noh* aux = mPtPrimeiro;
    Dado excluido = aux->mDado;

    mPtPrimeiro = aux->mProx;
    delete aux;
    if(Vazia()){
        mPtrUltimo = NULL;
    }
    return excluido;
}

void Fila::Enfileirar(const Dado& d) {
   Noh* novo = new Noh(d);
   if(Vazia()){
    mPtPrimeiro = novo;
   }
   else{
    mPtrUltimo->mProx= novo;
   }
   mPtrUltimo = novo;
}

void Fila::LimparTudo() {
    while(!Vazia()){
        Desenfileirar();
    }
}

void Fila::Primeiro() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    imprimir_dado(mPtPrimeiro->mDado);
}

void Fila::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: Fila vazia!");
    imprimir_dado(mPtrUltimo->mDado);
}

bool Fila::Vazia() {
    if(mPtPrimeiro == NULL){
        return true;
    }
    return false;
}

int Fila::Contabilizar(char type){
	
	Fila aux;
	Fila frente;
	Dado auxData;
	
	int cont=0;
	
	while(!Vazia()){
		auxData = Desenfileirar();
		if(auxData.tipo == type){
			cont += auxData.tempo;
			frente.Enfileirar(auxData);
			}
		else{
		aux.Enfileirar(auxData);
	}
		}
	
	while(!frente.Vazia()){
		auxData = frente.Desenfileirar();
		Enfileirar(auxData);
		}
	while(!aux.Vazia()){
		auxData = aux.Desenfileirar();
		Enfileirar(auxData);
		}
	return cont;
	}


int main() {
    Fila fila;
    Dado info;
    char comando;
    do {
        try{
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.premio >> info.tipo >> info.tempo;
                    fila.Enfileirar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(fila.Desenfileirar());
                    break;
                case 'l': // limpar tudo
                    fila.LimparTudo();
                    break;
                case 'e': // espiar                
                    fila.Primeiro();
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                case 'a':
					char type;
					cin >> type;
					cout << fila.Contabilizar(type) << endl;
					break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not fila.Vazia()) {
        imprimir_dado(fila.Desenfileirar());
    }
    cout << endl;
    return 0;
}
