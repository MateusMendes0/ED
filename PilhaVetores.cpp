/* Classe pilha estatica
 *
 * by Renato Ramos da Silva, 2023, Estruturas de Dados
 *
 */
#include <iostream>

using namespace std;

const int PILHAVAZIA = -1;
const int TAMANHOPILHA = 6;

struct Dado {
    string nome;
    char tipo;
    int valor;
};

// Imprime informações de um dado qualquer.
void imprimir_dado(const Dado& umDado){
    cout<< "Nome: " << umDado.nome << " ";
    cout<< "Tipo: " << umDado.tipo << " ";
    cout<< "Valor: " << umDado.valor << endl;
}

class Pilha {
    private:
        Dado* mPilha;
        int posTopo;
    public:
        // Constrói pilha vazia.
        Pilha();
        // Destrutor que desaloca memória.
        ~Pilha();
        // Retira e retorna o valor que estiver no topo da pilha.
        Dado Desempilhar(); 
        // Insere um elemento na pilha.
        void Empilhar(const Dado& d);
        // Apagar todos os dados da pilha.
        void LimparTudo();
        // Imprime o valor que está no topo sem desempilhar.
        inline void Topo();
        // Informa se a pilha está Vazia.
        inline bool Vazia();
        // Informa se a pilha está Cheia.
        inline bool Cheia();
        
        int Soma(char tipoSoma);
};

Pilha::Pilha(){
    mPilha = new Dado[TAMANHOPILHA];
    posTopo = -1;
}

Pilha::~Pilha() {
    delete[] mPilha;
}

Dado Pilha::Desempilhar() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");
    // completar com código necessário caso pilha não esteja vazia
    Dado aux = mPilha[posTopo];
    posTopo--;

    return aux;
}

void Pilha::Empilhar(const Dado& d) {
    if (this->Cheia()) throw runtime_error("Erro: pilha cheia!");

    posTopo++;

    mPilha[posTopo] = d;

}

void Pilha::LimparTudo() {
    while (!Vazia()) {
        Desempilhar();
    }


}

void Pilha::Topo() {
    if (this->Vazia()) throw runtime_error("Erro: pilha vazia!");

    imprimir_dado(this->mPilha[posTopo]);


}

bool Pilha::Vazia() {

    if(posTopo == PILHAVAZIA){
        return true;
    }
    return false;
}

bool Pilha::Cheia() {
    if(posTopo == 5){
        return true;
    }
    return false;
}

int Pilha::Soma(char tipoSoma){
	Pilha auxiliar;
	Dado teste;
	int soma = 0;
	
	while(!Vazia()){
		teste = Desempilhar();
		if(teste.tipo == tipoSoma){
			soma += teste.valor;
			}
		auxiliar.Empilhar(teste);
		}
	while(!auxiliar.Vazia()){
		teste = auxiliar.Desempilhar();
		Empilhar(teste);
		}
	return soma;
	}


int main() {
    Pilha pilha;
    Dado info;
    char comando;
    do {
        try {
            cin >> comando;
            switch (comando) {
                case 'i': // inserir
                    cin >> info.nome >> info.tipo >> info.valor;
                    pilha.Empilhar(info);
                    break;
                case 'r': // remover
                    imprimir_dado(pilha.Desempilhar());
                    break;
                case 'l': // limpar tudo
                    pilha.LimparTudo();
                    break;
                case 's': // limpar tudo
					char tipoSoma;
					cin >> tipoSoma;
                    cout << pilha.Soma(tipoSoma);
                    break;
                case 'e': // espiar 
                    if(!pilha.Vazia())               
                        pilha.Topo();
                    else
                        cout << " Pilha vazia!"<< endl;
                    break;
                case 'f': // finalizar
                    // checado no do-while
                    break;
                default:
                    cerr << "comando inválido\n";
            }
        } catch (runtime_error& e) {
            cout << e.what() << endl;
        }
    } while (comando != 'f'); // finalizar execução
    while (not pilha.Vazia()) {
        imprimir_dado(pilha.Desempilhar());
    }
    cout << endl;
    return 0;
}
