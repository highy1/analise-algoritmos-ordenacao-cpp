#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

struct jogo{
    string titulo;
    double preco;
    string genero;
};

long long insertSort(jogo vetor[], int N, long long &comp){

    long long mov = 0;
    for(int i = 2; i <= N; i++){

        int j = i;
        while(j > 1 && vetor[j].preco < vetor[j-1].preco){
            comp++;
            jogo temp = vetor[j];
            vetor[j] = vetor[j-1];
            vetor[j-1] = temp;
            mov += 2;
            j--;
        }
        if(j > 1) comp++;

    }
    return mov;

}

long long binaryInsertSort(jogo vetor[], int N, long long& comp){
    long long mov = 0;
    for(int i = 2; i <= N; i++){

        int L = 1;
        int R = i;
        while(L < R){
            int m = (L+R)/2;
            comp++;
            if(vetor[m].preco > vetor[i].preco){
                R = m;
            }
            else{
                L = m+1;
            }
        }
        if(R != i){
            jogo temp = vetor[i];

            for(int j = i; j > R; j--){
                vetor[j] = vetor[j-1];
                mov++;
            }

            vetor[R] = temp;
            mov++;
        }

    }
    return mov;

}

long long selectionSort(jogo vetor[], int N, long long& comp){

    long long mov = 0;
    for(int i = 1; i < N; i++){

        int imenor = i;
        for(int j = i+1; j <= N; j++){
            comp++;
            if(vetor[j].preco < vetor[imenor].preco){
                imenor = j;
            }
        }

        if(imenor != i){
            jogo temp = vetor[imenor];
            vetor[imenor] = vetor[i];
            vetor[i] = temp;
            mov += 2;
        }

    }
    return mov;
}

long long bubbleSort(jogo vetor[], int N, long long& comp){

    long long mov = 0;
    for(int i = 1; i <= N; i++){

        for(int j = N; j > i; j--){
            comp++;
            if(vetor[j].preco < vetor[j-1].preco){
                jogo temp = vetor[j];
                vetor[j] = vetor[j-1];
                vetor[j-1] = temp;
                mov += 2;
            }

        }

    }
    return mov;
}

long long heapfy(jogo vetor[], int i, int N, long long& comp){

    int maior = i;
    int esq = 2*i;
    int dir = 2*i + 1;

    if(esq <= N && (comp++, vetor[esq].preco > vetor[maior].preco))
        maior = esq;
    if(dir <= N && (comp++, vetor[dir].preco > vetor[maior].preco))
        maior = dir;

    if(maior != i){
        jogo temp = vetor[i];
        vetor[i] = vetor[maior];
        vetor[maior] = temp;
        return 2 + heapfy(vetor, maior, N, comp);
    }
    return 0;

}

long long heapsort(jogo vetor[], int N, long long& comp){

    long long q = 0;
    for(int j = N/2; j > 0; j--){
            q += heapfy(vetor, j, N, comp);
        }
    
    for(int i = 1; i < N; i++){

        jogo temp = vetor[1];
        vetor[1] = vetor[N+1 - i];
        vetor[N+1 - i] = temp;
        q += 2;

        q += heapfy(vetor, 1, N - i, comp);
        
    }

    return q;

}

long long merge(jogo vetor[], jogo aux[], int ini, int meio, int fim, long long& comp){

    long long q = 0;
    int k = meio+1;
    int j = ini;
    for(int i = ini; i <= fim; i++){

        if(j <= meio && (k > fim || (comp++, vetor[j].preco <= vetor[k].preco))){
            aux[i] = vetor[j];
            q++;
            j++;
        }
        else{
            aux[i] = vetor[k];
            q++;
            k++;
        }

    }

    for(int i = ini; i <= fim; i++){
        vetor[i] = aux[i];
        q++;
    }
    return q;

}

long long mergesort(jogo vetor[], jogo aux[], int ini, int fim, long long& comp){

    long long q = 0;
    if(ini < fim){
        int meio = (ini+fim)/2;

        q += mergesort(vetor, aux, ini, meio, comp);
        q += mergesort(vetor, aux, meio+1, fim, comp);
        q += merge(vetor, aux , ini, meio, fim, comp);

    }

    return q;

}

long long particionar(jogo vetor[], int& i, int& j, long long& comp){

    jogo pivo = vetor[(i+j)/2];
    long long q = 0;

    while(i <= j){

        while(vetor[i].preco < pivo.preco){
            comp++;
            i++;
        }
        comp++;
        while(vetor[j].preco > pivo.preco){
            j--;
            comp++;
        }
        comp++;

        if(i <= j){
            if(i != j){
                jogo temp = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = temp;
                q += 2;
            }
            i++;
            j--;
        }

    }

    return q;

}

long long quicksort(jogo vetor[], int ini, int fim, long long& comp){

    int i = ini;
    int j = fim;
    long long q = particionar(vetor, i, j, comp);

    if(ini < j) q += quicksort(vetor, ini, j, comp);
    if(fim > i) q += quicksort(vetor, i, fim, comp);

    return q;

}

void printVetor(jogo vetor[], int N){

    for(int i = 1; i <= N; i++){

        cout << "[Jogo: " << vetor[i].titulo << "/ Preco: " << vetor[i].preco << "] ";

    }

    cout << endl;

}

//copia vetor1 em vetor2
void copiarVetor(jogo vetor1[], jogo vetor2[], int N){

    for(int i = 1; i <= N; i++){
        vetor2[i] = vetor1[i];
    }

}

void itemC(){

    jogo lixo;
    jogo jogo1 = {"Zelda", 149.90, "Aventura"};
    jogo jogo2 = {"Counter-Strike", 60, "FPS"};
    jogo jogo3 = {"GTA VI", 349.90, "Mundo Aberto"};
    jogo jogo4 = {"Resident Evil 4", 129.90, "Terror"};
    jogo jogo5 = {"Silent Hill 2", 60, "Terror"};
    jogo vetor[6] = {lixo, jogo1, jogo2, jogo3, jogo4, jogo5};
    jogo vetorCopia[6];
    long long comp = 0;

    cout << "Vetor original: " << endl;
    printVetor(vetor, 5);

    copiarVetor(vetor, vetorCopia, 5);
    insertSort(vetorCopia, 5, comp);
    cout << "==== Insert Sort ====" << endl;
    printVetor(vetorCopia, 5);

    copiarVetor(vetor, vetorCopia, 5);
    binaryInsertSort(vetorCopia, 5, comp);
    cout << "==== Binary Insert Sort ====" << endl;
    printVetor(vetorCopia, 5);

    copiarVetor(vetor, vetorCopia, 5);
    selectionSort(vetorCopia, 5, comp);
    cout << "==== Selection Sort ====" << endl;
    printVetor(vetorCopia, 5);

    copiarVetor(vetor, vetorCopia, 5);
    bubbleSort(vetorCopia, 5, comp);
    cout << "==== Bubble Sort ====" << endl;
    printVetor(vetorCopia, 5);

    jogo aux[6];
    copiarVetor(vetor, vetorCopia, 5);
    heapsort(vetorCopia, 5, comp);
    cout << "==== Heap Sort ====" << endl;
    printVetor(vetorCopia, 5);

    copiarVetor(vetor, vetorCopia, 5);
    mergesort(vetorCopia, aux, 1, 5, comp);
    cout << "==== Merge Sort ====" << endl;
    printVetor(vetorCopia, 5);

    copiarVetor(vetor, vetorCopia, 5);
    quicksort(vetorCopia, 1, 5, comp);
    cout << "==== Quick Sort ====" << endl;
    printVetor(vetorCopia, 5);

}

jogo* criarVetorCrescente(int N){

    jogo* vetor = new jogo[N+1];

    for(int i = 1; i <= N; i++){
        vetor[i].titulo = "t";
        vetor[i].preco = i;
        vetor[i].genero = "g";
    }

    return vetor;

}

jogo* criarVetorDecrescente(int N){

    jogo* vetor = new jogo[N+1];

    for(int i = N; i > 0; i--){

        vetor[i].titulo = "t";
        vetor[i].preco = N-i;
        vetor[i].genero = "g";

    }

    return vetor;

}

jogo* criarVetorAleatorio(int N){

    jogo* vetor = new jogo[N+1];

    for(int i = 1; i <= N; i++){
        vetor[i].titulo = "t";
        vetor[i].preco = (double) rand() + 1000000;
        vetor[i].genero = "g";
    }

    return vetor;

}

void testeD(){
    int N1 = 2000;

    long long mov;
    long long comp;

    srand(13);

    for(int i = N1; i <= 80000; i = i*2){
        jogo* vetorCrescente = criarVetorCrescente(i);
        jogo* vetorCopia = new jogo[i+1];

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        auto inicio = high_resolution_clock::now();
        mov = insertSort(vetorCopia, i, comp);
        auto fim = high_resolution_clock::now();
        duration<double> duracao = fim - inicio;
        cout << "crescente,insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = selectionSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,selection sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = binaryInsertSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,binary insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = bubbleSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,bubble sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = heapsort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,heap sort," << i << ","<< mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        jogo* aux = new jogo[i+1];
        inicio = high_resolution_clock::now();
        mov = mergesort(vetorCopia, aux, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,merge sort," << i << ","<< mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorCrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = quicksort(vetorCopia, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "crescente,quick sort," << i << ","<< mov << "," << comp << "," << duracao.count() << endl;

        delete[] aux;
        delete[] vetorCrescente;
        delete[] vetorCopia;
    }

    for(int i = N1; i <= 80000; i = i*2){

        jogo* vetorDescrescente = criarVetorDecrescente(i);
        jogo* vetorCopia = new jogo[i+1];

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        auto inicio = high_resolution_clock::now();
        mov = insertSort(vetorCopia, i, comp);
        auto fim = high_resolution_clock::now();
        duration<double> duracao = fim - inicio;
        cout << "decrescente,insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = binaryInsertSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "decrescente,binary insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = selectionSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "decrescente,selection sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = bubbleSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "decrescente,bubble sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = heapsort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "decrescente,heap sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        jogo* aux = new jogo[i+1];
        inicio = high_resolution_clock::now();
        mov = mergesort(vetorCopia, aux, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "decrescente,merge sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorDescrescente, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = quicksort(vetorCopia, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        std::cout << "decrescente,quick sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        delete[] vetorDescrescente;
        delete[] vetorCopia;
        delete[] aux;

    }

    for(int i = N1; i <= 80000; i = i*2){

        jogo* vetorAleatorio = criarVetorAleatorio(i);
        jogo* vetorCopia = new jogo[i+1];

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        auto inicio = high_resolution_clock::now();
        mov = insertSort(vetorCopia, i, comp);
        auto fim = high_resolution_clock::now();
        duration<double> duracao = fim - inicio;
        cout << "aleatorio,insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = binaryInsertSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,binary insert sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = selectionSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,selection sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = bubbleSort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,bubble sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = heapsort(vetorCopia, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,heap sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        jogo* aux = new jogo[i+1];
        inicio = high_resolution_clock::now();
        mov = mergesort(vetorCopia, aux, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,merge sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        copiarVetor(vetorAleatorio, vetorCopia, i);
        comp = 0;
        inicio = high_resolution_clock::now();
        mov = quicksort(vetorCopia, 1, i, comp);
        fim = high_resolution_clock::now();
        duracao = fim - inicio;
        cout << "aleatorio,quick sort," << i << "," << mov << "," << comp << "," << duracao.count() << endl;

        delete[] vetorAleatorio;
        delete[] vetorCopia;
        delete[] aux;

    }


}

int main(){

    //item b)

    cout << "Insira o tamanho do vetor: ";
    int n;
    cin >> n;
    cin.ignore();

    jogo* vetorOriginal = new jogo[n+1];

    for(int i = 1; i <= n; i++){

        cout << "Insira o titulo do jogo: ";
        string titulo;
        getline(cin, titulo);
        vetorOriginal[i].titulo = titulo;

        cout << "Insira o preco do jogo (O vetor sera ordenado pelo preco): ";
        double preco;
        cin >> preco;
        cin.ignore();
        vetorOriginal[i].preco = preco;

        cout << "Insira o genero do jogo: ";
        string genero;
        getline(cin, genero);
        vetorOriginal[i].genero = genero;

    }

    jogo* vetorCopia = new jogo[n+1];

    // ordenando o vetor digitado pelo usuario usando os 7 algoritmos
    long long comp = 0;
    copiarVetor(vetorOriginal, vetorCopia, n);
    insertSort(vetorCopia, n, comp);

    copiarVetor(vetorOriginal, vetorCopia, n);
    binaryInsertSort(vetorCopia, n, comp);

    copiarVetor(vetorOriginal, vetorCopia, n);
    selectionSort(vetorCopia, n, comp);

    copiarVetor(vetorOriginal, vetorCopia, n);
    bubbleSort(vetorCopia, n, comp);

    copiarVetor(vetorOriginal, vetorCopia, n);
    heapsort(vetorCopia, n, comp);

    jogo* aux = new jogo[n+1];
    copiarVetor(vetorOriginal, vetorCopia, n);
    mergesort(vetorCopia, aux, 1, n, comp);

    copiarVetor(vetorOriginal, vetorCopia, n);
    quicksort(vetorCopia, 1, n, comp);

    delete[] vetorOriginal;
    delete[] vetorCopia;
    delete[] aux;

    cout << "\nItem C)" << "\n\n";

    //item c)
    itemC();

    testeD();

}



