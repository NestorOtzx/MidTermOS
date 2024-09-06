#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#define RRCODE 1
#define FCFSCODE 2

using namespace std;

void ejemplo(); void menu();
int arrSum(int n, int * arr);
string processToString(int process);
void printTable(int n, int * btArr, int * queuesArr, int * arriveTimes);
//MLQ CON Q1(RR(Quantum)) y Q2(FCFS)
void mlq(int n, int * btArr, int * queuesArr, int * arriveTimes, int quantum)
{
    int lt = arrSum(n, btArr);
    int t = 0;
    vector<int> rrQueue;
    vector<int> fcfsQueue;
    int currRR = 0;
    int quantC = quantum;
    string timeline = "";
    

    while (t < lt){
        //add
        for (int i = 0; i<n; i++)
        {
            if (arriveTimes[i] == t) { if (queuesArr[i] == RRCODE) { rrQueue.push_back(i); } else{ fcfsQueue.push_back(i); } } 
        }
        
        if (!rrQueue.empty())
        {
            timeline += processToString(rrQueue[currRR]);

            btArr[rrQueue[currRR]]-=1;
            quantC -= 1;
            
            if (btArr[rrQueue[currRR]] == 0)
            {
                //cout<<"T "<<t+1<<" process "<<rrQueue[currRR]<<" ended"<<endl;
                rrQueue.erase(rrQueue.begin()+currRR);

                quantC = quantum;
                if (currRR >= rrQueue.size())
                {
                    currRR = 0;
                }
            }else if (quantC == 0)
            {
                currRR += 1; 
                quantC = quantum;
                if (currRR >= rrQueue.size())
                {
                    currRR = 0;
                }
            }
        }else{
            timeline += processToString(fcfsQueue[0]);
            btArr[fcfsQueue[0]]-=1;
            if (btArr[fcfsQueue[0]] == 0)
            {
                //cout<<"T "<<t+1<<" process "<<fcfsQueue[0]<<" ended"<<endl;
                fcfsQueue.erase(fcfsQueue.begin());
            }
        }
        t++;
    }
    
    cout<<"Diagrama de Gantt (cada letra indica el proceso que se ejecuto en ese segundo): \n"<<timeline<<endl;
}


int main()
{
    menu();

    //menu();
    
    return 0;
}

string read(std::ifstream * file)
{
    string line;
    getline(*file, line);
    std::stringstream ss(line);
    string val;
    vector<string> splitvals;
    while (ss>>val);
        splitvals.push_back(val);
    return splitvals[splitvals.size()-1];
}


void menu()
{
    std::ifstream file("procesos_mlq.txt");
  
    // String to store each line of the file. 
    string line; 

    if (file.is_open()) { 
        int n = stoi(read(&file));
        int * b_arr = (int*)malloc(sizeof(int)*n);
        int * a_arr = (int*)malloc(sizeof(int)*n);
        int * q_arr = (int*)malloc(sizeof(int)*n);  
        int quantum = 3;

        read(&file); //linea de formato
        for (int i = 0; i<n; i++) { a_arr[i]= stoi(read(&file)); }
        read(&file); //linea de formato
        for (int i = 0; i<n; i++) { b_arr[i]= stoi(read(&file)); }
        read(&file); //linea de formato
        for (int i = 0; i<n; i++) { q_arr[i]= stoi(read(&file)); }
        read(&file); //linea de formato
        quantum = stoi(read(&file));

        printTable(n, b_arr, q_arr, a_arr);
        mlq(n, b_arr,  q_arr, a_arr, quantum);
    } 
    else { 
        cerr << "ERROR OPENING PROGRAM FILE" << endl; 
    } 
    cout<<"Adios."<<endl;
}

int arrSum(int n, int * arr)
{
    int ans = 0;
    for (int i = 0; i<n; i++)
    {
        ans += arr[i];
    }
    return ans;
}

string processToString(int process)
{
    return string(1, (char)(process+65));
}

void printTable(int n, int * btArr, int * queuesArr, int * arriveTimes){
    cout<<"---Table---"<<endl;
    cout<<" P |\tAt\t|\tBt\t|\tQ\t|"<<endl;
    for (int i = 0; i<n; i++)
    {  
        cout<<" "<<processToString(i)<<" |\t"<<arriveTimes[i]<<"\t|\t"<<btArr[i]<<"\t|\t"<< queuesArr[i]<<"\t|"<<endl;
    }
}