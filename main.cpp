#include <bits/stdc++.h>

using namespace std;

#define DEBUG 0

string::iterator isInclude(string::iterator first, string::iterator end)
{
    string::iterator not_found = end;
    if (DEBUG)
        cout << "teste" << endl;

    //1 ver se comeca com menor que ('<')
    if (*first != '<')
        return not_found;
    first++;

    //2 pular espacos em branco em excesso e busca include

    if (first == end)
        return not_found;
    while (first != end && isblank(*first))
        first++;
    string init = "include";
    if (first + init.length() >= end)
        return not_found;
    if (!equal(init.begin(), init.end(), first, [&](char c, char c2) { return tolower(c) == tolower(c2); }))
        return not_found;
    first += init.length();
    if (DEBUG)
        cout << "1 ok" << endl;

    //3 um espaco em branco
    if (first == end)
        return not_found;
    if (!isblank(*first))
        return not_found;
    first++;
    if (DEBUG)
        cout << "2 ok" << endl;

    //4 pular espacos em branco em excesso e busca parentese abrindo
    if (first == end)
        return not_found;
    while (first != end && isblank(*first))
        first++;
    if (first == end)
        return not_found;
    if (*first != '\"' && *first != '\'')
        return not_found;
    first++;
    if (DEBUG)
        cout << "3 ok" << endl;

    //5 busca fechamento do parentese
    if (first == end)
        return not_found;
    first = find(first, end, *(first - 1));
    if (first != end)
        first++;
    if (DEBUG)
        cout << "4 ok" << endl;

    //6 pular espacos em branco em excesso e busca um maior que ('>' para retornar 1) ou barra ('/' para passo 6)
    if (first == end)
        return not_found;
    while (first != end && isblank(*first))
        first++;
    if (first == end)
        return not_found;
    if (*first == '>')
        return first + 1;
    if (*first == '/')
        first++;
    else
        return not_found;
    if (DEBUG)
        cout << "5 ok" << endl;

    //7 confere maior que '>' encerrando
    if (first == end)
        return not_found;
    if (*first != '>')
        return not_found;
    if (DEBUG)
        cout << "6 ok" << endl;
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

void printStringRange(string::iterator first, string::iterator last)
{
    for_each(first, last, [](char c) { cout << c; });
}

int main()
{
    int inicio, n;
    pair<string::iterator, string::iterator> tag_include, path;
    vector<pair<string::iterator, string::iterator>> vet_pair_it;
    map<string, string> contente_arquivos{{"div.html", "<div>1</div>"}, {"diggjkk57655$#%#%v.html", "<div>doidera</div>"}, {"div2.html", "<div>2</div>"}};

    string html = "<html>\n<  include     \'diggjkk57655$#%#%v.html\'  >\n<    include   \'div2.html\'  /> <iiii>\n<  include     \'div2.html\'/>\n<include     \'div.html\'  >\n<include   \'div2.html\'  />\n<include     \'div2.html\'/>\n<include    \'div.html\'>\n<include \'div.html\'  >\n<include \'div2.html\'  />\n<include \'div2.html\'/>\n<include \'div.html\'>\n</html>";
    string::iterator begin = html.begin(), end = html.end();

    tag_include = findInclude(begin, end);
    vet_pair_it.push_back(make_pair(begin, tag_include.first));

    while (tag_include.second != html.end())
    {
        path = findPath(tag_include.first, tag_include.second);

        inicio = path.first - begin;
        n = path.second - path.first;

        string s = html.substr(inicio, n);
        //cout << "ENCONTRADO: " << s << endl;

        auto p_pair_content=contente_arquivos.find(s);
        
        if(p_pair_content==contente_arquivos.end()){
            contente_arquivos.insert({s,"novo arquivo"});
            p_pair_content=contente_arquivos.find(s);
        }

        string* content = &(p_pair_content->second);
        vet_pair_it.push_back(make_pair(content->begin(), content->end()));

        auto aux = tag_include.second;
        tag_include = findInclude(tag_include.second, end);

        vet_pair_it.push_back(make_pair(aux, tag_include.first));
    }

    vet_pair_it.push_back(make_pair(tag_include.second, end));
    for_each(vet_pair_it.begin(), vet_pair_it.end(), [](pair<string::iterator, string::iterator> p) { printStringRange(p.first, p.second); });
    cout << endl;

    return 0;
}