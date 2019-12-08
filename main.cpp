#include <bits/stdc++.h>

using namespace std;

#define DEBUG 0

class StateOfMachine
{
public:
    virtual bool sucess() { return false; }
    virtual bool notFound() { return false; }
    virtual StateOfMachine *exec(string::iterator &first, string::iterator &end)
    {
        if (DEBUG)
            cout << "state" << endl;
        return new StateOfMachine();
    }
};

class StateNull : public StateOfMachine
{
public:
    bool notFound() { return true; }

    StateOfMachine *exec(string::iterator &first, string::iterator &end)
    {
        if (DEBUG)
            cout << "state Null" << endl;
        return new StateNull();
    }
};

class StateSucess : public StateOfMachine
{
public:
    bool sucess() { return true; }

    StateOfMachine *exec(string::iterator &first, string::iterator &end)
    {
        if (DEBUG)
            cout << "state Success" << endl;
        return new StateSucess();
    }
};

class State1 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State2 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State3 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State4 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State5 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State6 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

class State7 : public StateOfMachine
{
public:
    StateOfMachine *exec(string::iterator &first, string::iterator &end);
};

StateOfMachine *State1::exec(string::iterator &first, string::iterator &end)
{
    if (DEBUG)
        cout << "state 1" << endl;
    if (*first != '<')
        return new StateNull();
    first++;
    return new State2();
}

StateOfMachine *State2::exec(string::iterator &first, string::iterator &end)
{
    //2 pular espacos em branco em excesso e busca include
    if (DEBUG)
        cout << "state 2" << endl;
    if (first == end)
        return new StateNull();
    while (first != end && isblank(*first))
        first++;
    string init = "include";
    if (first + init.length() >= end)
        return new StateNull();
    if (!equal(init.begin(), init.end(), first, [&](char c, char c2) { return tolower(c) == tolower(c2); }))
        return new StateNull();
    first += init.length();
    if (DEBUG)
        cout << "2 ok" << endl;
    return new State3();
}

StateOfMachine *State3::exec(string::iterator &first, string::iterator &end)
{
    //3 um espaco em branco
    if (DEBUG)
        cout << "state 3" << endl;
    if (first == end)
        return new StateNull();
    if (!isblank(*first))
        return new StateNull();
    first++;
    if (DEBUG)
        cout << "3 ok" << endl;
    return new State4();
}

StateOfMachine *State4::exec(string::iterator &first, string::iterator &end)
{
    //4 pular espacos em branco em excesso e busca parentese abrindo
    if (DEBUG)
        cout << "state 4" << endl;
    if (first == end)
        return new StateNull();
    while (first != end && isblank(*first))
        first++;
    if (first == end)
        return new StateNull();
    if (*first != '\"' && *first != '\'')
        return new StateNull();
    first++;
    if (DEBUG)
        cout << "4 ok" << endl;
    return new State5();
}

StateOfMachine *State5::exec(string::iterator &first, string::iterator &end)
{
    //5 busca fechamento do parentese
    if (DEBUG)
        cout << "state 5" << endl;
    if (first == end)
        return new StateNull();
    first = find(first, end, *(first - 1));
    if (first != end)
        first++;
    if (DEBUG)
        cout << "5 ok" << endl;
    return new State6();
}

StateOfMachine *State6::exec(string::iterator &first, string::iterator &end)
{
    //6 pular espacos em branco em excesso e busca um maior que ('>' para retornar 1) ou barra ('/' para passo 7)
    if (DEBUG)
        cout << "state 6" << endl;
    if (first == end)
        return new StateNull();
    while (first != end && isblank(*first))
        first++;
    if (first == end)
        return new StateNull();
    if (*first == '>')
        return new StateSucess();
    if (*first == '/')
        first++;
    else
        return new StateNull();
    if (DEBUG)
        cout << "5 ok" << endl;
    return new State7();
}

StateOfMachine *State7::exec(string::iterator &first, string::iterator &end)
{
    //7 confere maior que '>' encerrando
    if (DEBUG)
        cout << "state 7" << endl;
    if (first == end)
        return new StateNull();
    if (*first != '>')
        return new StateNull();
    if (DEBUG)
        cout << "7 ok" << endl;
    return new StateSucess();
}

string::iterator isInclude(string::iterator first, string::iterator end)
{
    if (DEBUG)
        cout << "teste" << endl;

    StateOfMachine *state = new State1();

    while (first<end && !state->notFound() && !state->sucess())
    {
        StateOfMachine *novoState = state->exec(first, end);
        delete state;
        state = novoState;
    }

    if (state->notFound())
        return end;

    return first + 1;
}

pair<string::iterator, string::iterator> findInclude(string::iterator first, string::iterator last)
{
    string::iterator last2;

    while (first < last)
    {
        last2 = isInclude(first, last);
        if (last2 != last)
            break;
        first++;
    }

    if (DEBUG)
        cout << *first << ' ' << *(last2 - 1) << endl;
    return make_pair(first, last2);
}

pair<string::iterator, string::iterator> findPath(string::iterator first, string::iterator last)
{
    string::iterator aux;
    aux = find(first, last, '\'');
    if (aux != last)
    {
        first = aux + 1;
        aux = find(first, last, '\'');
        return make_pair(first, aux);
    }
    aux = find(first, last, '\"');
    if (aux != last)
    {
        first = aux + 1;
        aux = find(first, last, '\"');
        return make_pair(first, aux);
    }
    return make_pair(last, last);
}

string lerArquivo(string path)
{
    string rtn;
    string line;

    FILE *fo = fopen(path.c_str(), "r");
    if (!fo)
    {
        cout << "(!) FILE NOT FOUND: " << path << endl;
        return "";
    }
    fclose(fo);

    ifstream myfile(path); // ifstream = padrão ios:in
    if (myfile.is_open())
    {
        while (!myfile.eof())
        {
            getline(myfile, line);
            rtn += line + "\n";
        }
        myfile.close();
    }
    return rtn;
}

string compiler(map<string, string> &contente_arquivos, set<string> &arquivos_indexados, string nome_aquivo)
{
    int inicio, n;
    pair<string::iterator, string::iterator> tag_include, path;
    vector<pair<string::iterator, string::iterator>> vet_pair_it;

    string html = lerArquivo(nome_aquivo);
    string::iterator begin = html.begin(), end = html.end();
    
    if(html.length()==0) return "";

    tag_include = findInclude(begin, end);
    vet_pair_it.push_back(make_pair(begin, tag_include.first));

    while (tag_include.second < end)
    {
        path = findPath(tag_include.first, tag_include.second);
        if (path.first < path.second)
        {
            inicio = path.first - begin;
            n = path.second - path.first;

            string s = html.substr(inicio, n);
            //cout << "ENCONTRADO: " << s << endl;

            auto p_pair_content = contente_arquivos.find(s);

            if (p_pair_content == contente_arquivos.end())
            {
                if (arquivos_indexados.find(s) != arquivos_indexados.end())
                {
                    cout << "(!) LOOP DETECTED INTO: " << s << endl;
                    contente_arquivos.insert({s, ""});
                }
                else{
                    arquivos_indexados.insert(s);
                    contente_arquivos.insert({s, compiler(contente_arquivos, arquivos_indexados, s)});
                }
                //contente_arquivos.insert({s, ""});
                p_pair_content = contente_arquivos.find(s);
            }

            string *content = &(p_pair_content->second);
            vet_pair_it.push_back(make_pair(content->begin(), content->end()));
        }
        auto aux = tag_include.second;
    
        tag_include = findInclude(tag_include.second, end);

        vet_pair_it.push_back(make_pair(aux, tag_include.first));
    }
    if (tag_include.second < end)
        vet_pair_it.push_back(make_pair(tag_include.second, end));

    string rtn;
    for_each(vet_pair_it.begin(), vet_pair_it.end(), [&](pair<string::iterator, string::iterator> p) { for_each(p.first, p.second, [&](char c) { rtn += c; }); });
    return rtn;
}

int main(int t,char *args[])
{
    string html(args[1]);
    string destino(args[2]);

    map<string, string> contente_arquivos{{"div.html", "<div>1</div>"}, {"diggjkk57655$#%#%v.html", "<div>doidera</div>"}, {"div2.html", "<div>2</div>"}};
    set<string> arquivos_indexados{html};

    string result=compiler(contente_arquivos, arquivos_indexados, html);

    ofstream out; // out é uma variavel.
    out.open(destino); // o arquivo que será criado;
    out<<result;
    out.close();

    return 0;
}
