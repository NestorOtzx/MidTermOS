#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#define RRCODE 1
#define FCFSCODE 2

using namespace std;

int findLast(char letter, string s);
void printMeasures(string timeline, int n, int * arriveTimes);
int findWaitingTime(char letter, string s);
void ejemplo(); void menu();
int arrSum(int n, int * arr);
string processToString(int process);
void printTable(int n, int * btArr, int * arriveTimes);
//MLQ CON Q1(RR(Quantum)) y Q2(FCFS)
void mlfq(int n, int * btArr, int * arriveTimes, int quantum, int quantum1)
{
    int lt = arrSum(n, btArr);
    int t = 0;
    vector<int> rrQueue, rrQueue1;
    vector<int> fcfsQueue;
    int currRR = 0;
    int currRR1 = 0;
    int quantC = quantum;
    int quantC1 = quantum1;
    string timeline = "";
    

    while (t < lt){
        //add
        for (int i = 0; i<n; i++)
        {
            if (arriveTimes[i] == t) {  
                rrQueue.push_back(i);
            } 
            
            //else{  fcfsQueue.push_back(i); } 
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
                rrQueue1.push_back(rrQueue[currRR]);
                rrQueue.erase(rrQueue.begin()+currRR);
                quantC = quantum;
                if (currRR >= rrQueue.size())
                {
                    currRR = 0;
                }
            }
        }else if (!rrQueue1.empty())
        {
            timeline += processToString(rrQueue1[currRR1]);

            btArr[rrQueue1[currRR1]]-=1;
            quantC1 -= 1;
            
            if (btArr[rrQueue1[currRR1]] == 0)
            {
                //cout<<"T "<<t+1<<" process "<<rrQueue1[currRR1]<<" ended"<<endl;
                rrQueue1.erase(rrQueue1.begin()+currRR1);

                quantC1 = quantum1;
                if (currRR1 >= rrQueue1.size())
                {
                    currRR1 = 0;
                }
            }else if (quantC1 == 0)
            {
                fcfsQueue.push_back(rrQueue1[currRR1]);
                rrQueue1.erase(rrQueue1.begin()+currRR1);
                quantC1 = quantum1;
                if (currRR1 >= rrQueue1.size())
                {
                    currRR1 = 0;
                }
            }
        }
        else{
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
    
    printMeasures(timeline,n, arriveTimes);
}


int main()
{
    menu();   
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
    std::ifstream file("procesos_mlfq.txt");
  
    // String to store each line of the file. 
    string line; 

    if (file.is_open()) { 
        int n = stoi(read(&file));
        int * b_arr = (int*)malloc(sizeof(int)*n);
        int * a_arr = (int*)malloc(sizeof(int)*n);
        int quantum = 3;
        int quantum1 = 3;
        
        read(&file); //linea de formato
        for (int i = 0; i<n; i++) { a_arr[i]= stoi(read(&file)); }
        read(&file); //linea de formato
        for (int i = 0; i<n; i++) { b_arr[i]= stoi(read(&file)); }
        read(&file); //linea de formato
        quantum = stoi(read(&file));
        quantum1 = stoi(read(&file));

        printTable(n, b_arr, a_arr);
        mlfq(n, b_arr, a_arr, quantum, quantum1);
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

void printTable(int n, int * btArr, int * arriveTimes){
    cout<<"---Table---"<<endl;
    cout<<" P |\tAt\t|\tBt\t|"<<endl;
    for (int i = 0; i<n; i++)
    {  
        cout<<" "<<processToString(i)<<" |\t"<<arriveTimes[i]<<"\t|\t"<<btArr[i]<<"\t|"<<endl;
    }
}

void printMeasures(string timeline, int n, int * arriveTimes)
{
    cout<<"---Medidas---"<<endl;
    cout<<" P\t|\tCT\t|\tTAT\t|\tWT\t|"<<endl;
    float ctProm = 0.0f;
    float tatProm = 0.0f;
    float wtProm = 0.0f;
    for (int i = 0; i<n; i++)
    {  
        float ct = findLast(processToString(i)[0], timeline)+1;
        float wt = findWaitingTime(processToString(i)[0], timeline);
        cout<<" "<<processToString(i)<<"\t|\t"<<ct<<"\t|\t"<<ct-arriveTimes[i]<<"\t|\t"<<wt<<"\t|"<<endl;
        ctProm+=ct/n;
        wtProm+=wt/n;
        tatProm+=(ct-arriveTimes[i])/n;
    }
    cout<<" Medias: |\t"<<ctProm<<"\t|\t"<<tatProm<<"\t|\t"<<wtProm<<"\t|"<<endl;
}


int findLast(char letter, string s)
{
    int max = 0;
    for (int i = s.size()-1; i>=0; i--)
    {
        if (letter == s[i])
        {
            max = i;
            break;
        }
    }
    return max;
}

//encuentra el primer elemento del ultimo bloque de ejecucion de un proceso
int findWaitingTime(char letter, string s)
{
    int min = s.size()-1;
    bool finding = false;
    for (int i = s.size()-1; i>=0; i--)
    {
        if (letter == s[i])
        {
            finding = true;
            min = i;
        }else if (finding)
        {
            break;
        }
    }
    for (int i = 0; i<min; i++)
    {
        if (letter == s[i])
        {
            min-=1;
        }
    }
    return min;
}