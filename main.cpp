#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;
void parser(const string & equation, string & output, unsigned int var_num, char* variables,const vector<string> & var_name);
int main() {
    unsigned int num_var;
    char variables[6] = {'A','B','C','D','E','F'};
    vector<string> var_names;
    string equation;
    bool error_flag = false;
    cout<<"insert number of variables (1 to 6):";
    cin>>num_var;
    if (!(num_var > 0 && num_var < 7)){
        cout<<"invalid selection"<<endl;
        return 0;
    }
    var_names.resize(num_var);
    for (unsigned int i = 0; i < num_var; ++i) {
        cout<<"specify variable name of variable "<< variables[i]<<" :";
        cin>>var_names[i];
    }
    char temp;
    cout<<"continue?(y/n)";
    cin>>temp;

    bool cont = true;
    while (cont){
        cout<<"enter equation:";
        cin.clear();
        cin.sync();
        getline(cin,equation);

        string output;
        parser(equation,output,num_var,variables,var_names);
        cout<<output<<endl;
        cout<<"continue?(y/n)";
        cin>>temp;
        if (temp == 'n') {
            cont = false;
        }
    }
    return 0;
}

void parser(const string & equation, string & output, unsigned int var_num, char* variables,const vector<string> & var_name){
    bool var,new_var;
    unsigned int pos;
    size_t count = 0;
    vector<string> products;
    size_t i = 0;
    new_var = false;
    while(i < equation.size()){
        var = false;
        pos = 0;
        for (unsigned int j = 0; j < var_num && !var; ++j) {
            if (equation[i] == variables[j]){
                pos = j;
                var = true;
                count++;
                if (!new_var){
                    products.emplace_back();
                    new_var = true;
                }
            }
        }
        if (var) {
            i++;

            if (count != 1) {
                products.back().append(" AND ");
            }

            if (i < equation.size() && equation[i] == '\''){
                i++;
                products.back().append("NOT(");
                products.back().append(var_name[pos]);
                products.back().append(")");
            }
            else {
                products.back().append(var_name[pos]);
            }
        }
        else {
            i++;
            new_var = false;
            count = 0;
        }
    }

    for (const auto & item : products) {
        output.append("(");
        output.append(item);
        output.append(")");
        if (item != products.back()){
            output.append(" OR ");
        }
    }
}
