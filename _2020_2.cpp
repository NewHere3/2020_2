#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct zuvis
{
    string name = "";
    int points = 0;
    int mass = 0;
};

struct zmogus
{
    string name = "";
    int points = 0;
    zuvis zuvys[5];
};

struct basic
{
    string name = "Error";
    int number = 0;
};

void read(vector<zuvis>& laimikis, vector<zmogus>& dalyviai);
void my_sort(vector<basic>& vec);
void write(ofstream& rez, vector<basic>& vec);

int main()
{
    vector<zuvis> laimikis;
    vector<zmogus> dalyviai;
    read(laimikis, dalyviai);
    for (int i = 0; i < dalyviai.size(); i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (dalyviai[i].zuvys[j].name!="")
            {
                if (dalyviai[i].zuvys[j].mass >= 200) { dalyviai[i].points += 30; }
                else { dalyviai[i].points += 10; }
                for (int k = 0; k < laimikis.size(); k++)
                {
                    if (dalyviai[i].zuvys[j].name == laimikis[k].name)
                    {
                        dalyviai[i].points += laimikis[k].points;
                    }
                }
            }
        }
    }

    for (int i = 0; i < laimikis.size(); i++)
    {
        for (int j = 0; j < dalyviai.size(); j++)
        {
            for (int k = 0; k < 5; k++)
            {
                if (laimikis[i].name == dalyviai[j].zuvys[k].name)
                {
                    laimikis[i].mass += dalyviai[j].zuvys[k].mass;
                }
            }
        }
    }
    // perasome i masyvus kuriu duomenys sutampa
    vector<basic> dalyviai_basic;
    vector<basic> laimikis_basic;
    for (int i = 0; i < dalyviai.size(); i++)
    {
        basic temp;
        temp.name = dalyviai[i].name;
        temp.number = dalyviai[i].points;
        dalyviai_basic.push_back(temp);
    }
    for (int i = 0; i < laimikis.size(); i++)
    {
        basic temp;
        temp.name = laimikis[i].name;
        temp.number = laimikis[i].mass;
        laimikis_basic.push_back(temp);
    }
    my_sort(laimikis_basic);
    my_sort(dalyviai_basic);
    ofstream rez("Rezultatai.txt");
    rez << "Dalyviai" << '\n';
    write(rez, dalyviai_basic);
    rez << "Laimikis" << '\n';
    write(rez, laimikis_basic);
    rez.close();
    return 0;
}

void my_sort(vector<basic>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = i; j < vec.size(); j++)
        {
            if (vec[i].number == vec[j].number)
            {
                if (vec[i].name > vec[j].name)
                {
                    swap(vec[i], vec[j]);
                }
            }
            else if (vec[i].number < vec[j].number)
            {
                swap(vec[i], vec[j]);
            }
        }
    }
}

void read(vector<zuvis>& laimikis, vector<zmogus>& dalyviai)
{
    ifstream duom("Duomenys.txt");
    int n;
    duom >> n;
    for (int i = 0; i < n; i++)
    {
        zmogus temp;
        duom.ignore(numeric_limits<streamsize>::max(), '\n');
        // read zmogaus varda
        for (int j = 0; j < 20; j++)
        {
            temp.name += duom.get();
        }
        dalyviai.push_back(temp);
        int N;
        duom >> N;
        // read jo laimiki
        for (int j = 0; j < N; j++)
        {
            duom.ignore(numeric_limits<streamsize>::max(), '\n');
            //read laimikio varda
            for (int k = 0; k < 20; k++)
            {
                dalyviai[i].zuvys[j].name += duom.get();
            }
            duom >> dalyviai[i].zuvys[j].mass;
        }
    }
    duom >> n;
    for (int i = 0; i < n; i++)
    {
        zuvis temp;
        duom.ignore(numeric_limits<streamsize>::max(), '\n');
        // read zuvies varda
        for (int j = 0; j < 20; j++)
        {
            temp.name += duom.get();
        }
        laimikis.push_back(temp);
        duom >> laimikis[i].points;
    }
    duom.close();
}

void write(ofstream& rez, vector<basic>& vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        rez << vec[i].name << vec[i].number << '\n';
    }
}