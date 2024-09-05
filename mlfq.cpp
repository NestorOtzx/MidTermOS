#include <iostream>
#include <vector>
#include <string>
#define RRCODE 1
#define FCFSCODE 2

using namespace std;

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
}


int main()
{
    menu();   
    return 0;
}



void menu()
{
    int n;
    cout<<"Ingrese el numero de procesos (0 para ejecutar el ejemplo)"<<endl;
    cin>>n;
    if (n > 0){
        int * b_arr = (int*)malloc(sizeof(int)*n);
        int * a_arr = (int*)malloc(sizeof(int)*n);
        int quantum = 3, quantum1 = 6;
        for (int i = 0; i<n; i++)
        {
            cout<<"Ingrese el At del proceso "<<processToString(i)<<": ";
            cin>>a_arr[i];
            cout<<"Ingrese el Bt del proceso "<<processToString(i)<<": ";
            cin>>b_arr[i];
        }
        cout<<"Ingrese el quantum de Q1: ";
        cin>>quantum;
        cout<<"Ingrese el quantum para Q2: ";
        cin>>quantum1;
        printTable(n, b_arr, a_arr);
        mlfq(n, b_arr, a_arr, quantum, quantum1);
    }else{
        ejemplo();
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
    cout<<" P |\tAt\t|\tBt\t"<<endl;
    for (int i = 0; i<n; i++)
    {  
        cout<<" "<<processToString(i)<<" |\t"<<arriveTimes[i]<<"\t|\t"<<btArr[i]<<"\t|"<<endl;
    }
}

void ejemplo()
{
    int n = 5;
    int * b_arr = (int*)malloc(sizeof(int)*n);
    b_arr[0] = 3;b_arr[1] = 6;b_arr[2] = 10;b_arr[3] = 3; b_arr[4] = 10;
    int * a_arr = (int*)malloc(sizeof(int)*n);
    a_arr[0] = 0;a_arr[1] = 0;a_arr[2] = 0;a_arr[3] = 0; a_arr[4] = 2;
    int quantum = 3;
    int quantum1 = 6;

    printTable(n, b_arr, a_arr);
    mlfq(n, b_arr, a_arr, quantum, quantum1);
}