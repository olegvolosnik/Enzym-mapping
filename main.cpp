#include <iostream>
#include <cstdlib>
#include <time.h>
#include <vector>
#include <string>
#include <bits/stdc++.h>

using namespace std;

int seq_size, data_set_nr, map_elements = 0;
vector<int> seq;
char instances;
long recursive_depth = 0;

void instance_of_problem_generator(){
    vector<int>instances_vec;
    int k = 20;//sum of elements in Multiset (k+2)*(k+1)/2;

    int arr[k];
    for(int i = 0; i < k; i++) {
        arr[i] = (rand() % 700) + 100;
        cout<<arr[i]<<" ";
    }
    cout<<endl<<endl;
    for(int index = 0; index < k; index++){
        for(int window = 1; window <= k; window ++){
            if(index + window <= k){
                int counter = 0;
                int local_sum = 0;
                while(counter < window){
                    local_sum +=arr[index + counter];
                    counter++;
                }
                instances_vec.push_back(local_sum);
                cout<<local_sum<<" ";
            }
        }
        cout<<endl;
    }
    cout<<endl;

    sort(instances_vec.begin(), instances_vec.end());
    cout<<endl;
    for(auto i : instances_vec){
        cout<<i<<" ";
    }
    sort(instances_vec.begin(), instances_vec.end(), greater <>());
    cout<<endl;
    for(auto i : instances_vec) {
        cout << i << " ";
    }
}


void seq_reader(){
    string line, data_set;
    int number;
    fstream file;
    int counter = 0;

    if (instances == 'm') {
        cout<<"\nInstances form Ph.D., Dr. Habil., Professor Marta Kasprzak"<<endl;
        data_set = "inst_" + to_string(data_set_nr) + ".txt";
    } else if (instances == 'o') {
        cout<<"\nInstances form Oleh"<<endl;
        data_set = "my_inst_" + to_string(data_set_nr) + ".txt";
    }
    file.open(R"(D:\3 semestr\AKwB\Zadanie 4.1\cmake-build-debug\)" + data_set, ios::in);
    if(file.is_open())
        cout<<data_set<<endl;
    if(!file.good()){
        cout<<endl<<"Can not open the file."<<endl;
    }

    while (!file.eof()){
        getline(file, line);
        stringstream ss(line);
        while (ss >> number) {
            seq.push_back(number);
        }
    }
    seq_size = seq.size();
    file.close();
}


bool proper_elem_amount(){
    int s_size = seq_size;
    int cut_amount, tmp;
    bool amount_good = false;
    for(int i = 1; i <  25; i++){
        tmp = (i+2)*(i+1)/2; // calculating proper possible amounts of cutting
        if(seq_size == tmp) {
            amount_good = true;
            cut_amount = i;
            map_elements = cut_amount+1;
            break;
        }
    }
    if(not amount_good){
        cout<<"Set has wrong amount of sub-seq. Error."<<endl;
    }else{
        cout<<"Set has proper amount of sub-seq."<<" Cut amount: "<<cut_amount<<endl<<endl;
    }
    return amount_good;
}


void recursive_tree_algorithm( int cur_elem, int *result, int max_index, int ind, int *solution_exist)
{
    recursive_depth++;
    int tmp=0;
    bool check=true;//check if numbers are nonsense for solution
    bool *compare;//arr for visited elements
    compare = new bool [seq_size];
    //all flags on False
    for(int a=0; a<seq_size; a++){      
        compare[a]=false;
    }
    result[ind]=seq[cur_elem]; //result arr on current pos eq current elem
    // mark elements from solution as visited
    for(int i=0; i<=ind; i++){
        if(check){
            for(int j=0; j<seq_size; j++){
                if(result[i]==seq[j] and not compare[j]){
                    compare[j]=true;
                    break;
                }
                else if(j==seq_size-1){
                    check=false;
                    break;
                }
            }
        }
    }
    //check all possible numbers in new multiset and marked as visited
    for(int a=0; a<ind; a++){
        tmp=result[a];
        if(check){
            for(int b=a+1; b<=ind; b++){
                if(check){
                    tmp=tmp+result[b];
                    for(int j=0; j<seq_size; j++){
                        if(tmp==seq[j] and not compare[j]){
                            compare[j]=true;
                            break;
                        }
                        if(j==seq_size-1){
                            check=false;
                            break;
                        }
                    }
                }
            }
        }
    }
//    compare seq_size and new multiset size
    if(ind==max_index and check){
        cout<<"Find solution: "<<endl;
        for(int i=0; i<=max_index; i++){
            cout<<result[i]<<" ";
        }
        cout<<" ###" <<endl;
        cout<<"recursive_depth = "<<recursive_depth<<endl;
        *solution_exist=1;
    }else{
//        going one step depth for non-visited elements
        for(int i=0; i<seq_size; i++){
            if(*solution_exist==1) break;
            if(check and not compare[i]){
                recursive_tree_algorithm( i, result, max_index, ind+1, solution_exist);
            }
        }
    }
    delete [] compare;
}


int main()
{


    clock_t tStart = clock();

    instances = 'm';
    data_set_nr = 5;

    seq_reader();
    bool proper_size = proper_elem_amount();

    int solution_exist=0;
    int *result;
    float check = 0;
    int cut = 0;






    if(proper_size){
        result = new int [map_elements];

        for(int i=0; i<seq_size; i++)
        {
            if (not solution_exist){        //until no solution iteration through elements in seq
                for(int k=0; k<map_elements; k++){      //arr for possible result
                    result[k]=0;
                }
                recursive_tree_algorithm(i, result, map_elements-1, 0, &solution_exist);
            }
        }
        if(solution_exist==0){
            cout<<"No proper solution in set. ###"<<endl;
        }
        printf("Time : %.4fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);

    }

    seq.clear();
    delete [] result;

    return 0;
}
