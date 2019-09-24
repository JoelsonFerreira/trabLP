#include <fstream>
#include <string>
#include <iostream>
#include <map>

struct Ocupados
{
    int comeco, quant;
};

enum Modos {FIRST, NEXT, BEST, WORST};
Modos modo = FIRST;

map<string, struct Ocupados> vOc;
map<int, int> vDes;
map<int, int>::iterator atual;

using namespace std;

#define SIZE_KEYWORD0 1
#define SIZE_KEYWORD1 2
#define SIZE_KEYWORD2 1

// Palavras chaves do codigo
string keyWord0[1] =
{
    "exibe"
};
string keyWord1[SIZE_KEYWORD1] =
{
    "del",
    "heap"
};
string keyWord2[SIZE_KEYWORD2] =
{
    "new"
};
string heap[4]=
{
    "first",
    "best",
    "worst",
    "next"
};


// recebe 2 numeros a e b, e retorna o maior deles
int max(int a, int b)
{
    if(a > b)   return a;
    return b;
}

// recebe uma keyWord e retorna a quantidade de argumentos esperadas pra aquela key
int sizeKeyWord(string str)
{
    for(int i = 0; i < max(SIZE_KEYWORD1, SIZE_KEYWORD2); i++)
    {
        if(str == keyWord0[i] && i < SIZE_KEYWORD0)
        {
            return 0;
        }
        if(str == keyWord1[i] && i < SIZE_KEYWORD1)
        {
            return 1;
        }
        else if(str == keyWord2[i] && i < SIZE_KEYWORD2)
        {
            return 2;
        }
    }
    return 2;
}

map<int,int>::iterator ocupa(map<int, int>::iterator it, int beginPos, int amount, int argInt, string id)
{
    // Ocupa
    vDes.erase(it);
    if(amount - argInt > 0)
    {
        vDes[beginPos + argInt] = amount - argInt;
    }

    struct Ocupados aux;
    aux.comeco = beginPos;
    aux.quant  = argInt;

    vOc[id] = aux;

    return vDes.find(beginPos + argInt);
}

void newFirst(string args[2])
{
    int argInt = atoi(args[1].c_str());

    // pegando primeira posicao de memoria disponivel (first fit)
    map<int, int>::iterator it = vDes.begin();
    int beginPos, amount;

    beginPos = it->first;
    amount = it->second;

    for(; it != vDes.end() && it->second <= argInt; it++)
    {
        beginPos = it->first;
        amount = it->second;
    }

    // caso exista uma posicao disponivel...
    if(it != vDes.end())
    {
        // // Desocupa
        // vDes.erase(it);
        // vDes[beginPos + argInt] = amount - argInt;

        // // Ocupa
        // struct Ocupados aux;
        // aux.comeco = beginPos;
        // aux.quant  = argInt;

        // vOc[args[0]] = aux;
        ocupa(it, beginPos, amount, argInt, args[0]);
    }
    else
    {
        cout << "Espaco insuficiente para alocar " << args[0] << "!" << endl;
    }
}

void newNext (string args[2])
{
    cout << atual->first << " -> " << atual->second << endl;
    int argInt = atoi(args[1].c_str());
    auto aux = atual;
    for(;atual != vDes.end() && atual->second < argInt; atual++)
    {
        cout << atual->first << endl;
    }
    if(atual == vDes.end())
    {
        for(atual=vDes.begin();atual!=aux && atual->second < argInt;atual++)
        {
            cout << atual->first << endl;
        }
        if(atual->second < argInt)
        {
            cout << "Espaco insuficiente para alocar "<< args[0] << "!" << endl;
            return;
        }
    }
    aux = atual;
    atual = ocupa(aux,aux->first,aux->second,argInt,args[0]);
}

void newBest(string args[2])
{
    int argInt = atoi(args[1].c_str());

    // pegando primeira posicao de memoria disponivel (first fit)
    map<int, int>::iterator it = vDes.begin();
    int beginPos, amount;

    beginPos = it->first;
    amount = it->second;

    for(map<int, int>::iterator aux = vDes.begin(); aux != vDes.end(); aux++)
    {
        if(aux->second >= argInt && aux->second < amount)
        {
            it = aux;
            beginPos = aux->first;
            amount = aux->second;
        }
    }
    // caso exista uma posicao disponivel...
    if(amount >= argInt)
    {
        // // Ocupa
        // vDes.erase(it);
        // vDes[beginPos + argInt] = amount - argInt;

        // struct Ocupados aux;
        // aux.comeco = beginPos;
        // aux.quant  = argInt;

        // vOc[args[0]] = aux;
        ocupa(it, beginPos, amount, argInt, args[0]);
    }
    else
    {
        cout << "Espaco insuficiente para alocar " << args[0] << "!" << endl;
    }
}
void newWorst(string[2])
{
    int argInt = atoi(args[1].c_str());
    // pegando primeira posicao de memoria disponivel (first fit)
    map<int, int>::iterator it = vDes.begin();
    int beginPos, amount;

    beginPos = it->first;
    amount = it->second;
    for(map<int,int>::iterator aux = vDes.begin();aux !=vDes.end();aux++)
    {
        if(aux->second >= argInt && aux->second = amount)//se o tamanho de aux é igual amount quer dizer q é o maior espaço possivel
        {
            it = aux;
            beginPos = aux->first;
            amount = aux->second;
        }
        if(amount >= argInt)
        {
            ocupa(it, beginPos, amount, argInt, args[0]);
        }
        else
        {
            cout << "Espaco insuficiente para alocar " << args[0] << "!" << endl;
        }
    }
}
void delElem(string args[2])
{
    // buscando o id
    map<string, struct Ocupados>::iterator it = vOc.find(args[0]);
    struct Ocupados aux = it->second;

    // se o id existe nos ocupados...
    if(it != vOc.end())
    {
        // apaga
        vOc.erase(it);

        // mescla com espaco de memoria que ja estava livre caso seja conticua
        int endPos = aux.comeco + aux.quant;
        if(vDes.find(endPos) != vDes.end())
        {
            int d = vDes[vDes.find(endPos)->first];
            vDes.erase(vDes.find(endPos));
            vDes[aux.comeco] = aux.quant + d;
        }
        // caso nao seja continua
        else
        {
            vDes[aux.comeco] = aux.quant;
        }
        for(map<string,struct Ocupados>::iterator da =vOc.begin();da !=vOc.end();da++){
            if(it->second.comeco==da->second.comeco && it->second.quant==da->second.quant){
                da->second.comeco=da->second.quant=-1;
            }
        }
    }
}

void exibe()
{
    cout << "============== DESOCUPADOS ================" << endl;
    for(map<int,int>::iterator it = vDes.begin(); it != vDes.end(); it++)
    {
        cout << "POS: " << it->first << "\tQUANT: " << it->second << endl;
    }
    cout << endl << "==============   OCUPADOS   ================" << endl;
    for(map<string, struct Ocupados>::iterator it = vOc.begin(); it != vOc.end(); it++)
    {
        cout << "ID: " << it->first << "\tPOS: " << it->second.comeco << "\tQUANT: " << it->second.quant << endl;
    }
    cout << endl << endl;
}

void atrib(string tokenKey, string args[2])
{
    map<string, struct Ocupados>::iterator re = vOc.find(args[1]);
    if (re != vOc.end()){
        vOc[tokenKey]= re->second;
    }else{
        cout << args[1] << " nao existe." << endl;
    }
}

/*
 *
 * receebe uma palavra chave e seus argumentos...
 * realiza a simulacao feita em vOc(ED que representea a memoria desocupada)
 * e vDes(ED que representa a memoria desocupada)
 *
*/
void simulando(string tokenKey, string args[2])
{
    // palavra chave new, aloca um pedaço de memoria do tamanho args[1] chamado pelo id args[0]
    if(tokenKey == "new")
    {
        switch(modo)
        {
            case FIRST:
                newFirst(args);
                break;
            case NEXT:
                newNext(args);
                break;
            case BEST:
                newBest(args);
                break;
            // case WORST:
            //     newWorst();
            //     break;
            default:
                cout << "Modo do heap não conhecido!!!" << endl;
        }
    }
    // palavra chave "del", apaga o espaco de memoria com o id = args[0]
    else if(tokenKey == "del")
    {
        delElem(args);
    }
    else if(tokenKey == "heap")
    {
        if(args[0] == "first")
        {
            modo = FIRST;
        }
        else if(args[0] == "next")
        {
            modo = NEXT;
        }
        else if(args[0] == "best")
        {
            modo = BEST;
        }
        else if(args[0] == "worst")
        {
            modo = WORST;
        }
        else
        {
            cout << "\"modo " << args[0] << "\" nao reconhecido!" << endl;
        }
    }
    else if(tokenKey == "exibe")
    {
        exibe();
    }
    else if(args[0]=="=") // atribui
    {
        atrib(tokenKey, args);
    }

}

/*
 * separa as palavras chaves dos argumentos e chama a funcao simulando
 */
int iTokens(string fname)
{
    /*  tokens  */
    ifstream file(fname);

    if(file.is_open())
    {
        while(!file.eof())
        {
            string tokenKey;

            file >> tokenKey;

            string tokenArg[2];

            //cout << tokenKey << " ";

            for(int i = 0; i < sizeKeyWord(tokenKey); i++)
            {
                file >> tokenArg[i];
                //cout << tokenArg[i] << " ";
            }

            //cout << endl;

            simulando(tokenKey, tokenArg);
        }

        file.close();
        return 1;
    }
    else
    {
        return 0;
    }
    /*          */
}
