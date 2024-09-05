#include <iostream>
#include <vector>
#include <string>
#define RRCODE 1
#define FCFSCODE 2

using namespace std;

void ejemplo(); void menu();
int arrSum(int n, int * arr);
string processToString(int process);
void printTable(int n, int * btArr, int * queuesArr, int * arriveTimes);
//MLQ CON Q1(RR(Quantum)) y Q2(FCFS)
void mlfq(int n, int * btArr, int * queuesArr, int * arriveTimes, int quantum)
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
        int * q_arr = (int*)malloc(sizeof(int)*n);
        int quantum = 3;
        for (int i = 0; i<n; i++)
        {
            cout<<"Ingrese el At del proceso "<<processToString(i)<<": ";
            cin>>a_arr[i];
            cout<<"Ingrese el Bt del proceso "<<processToString(i)<<": ";
            cin>>b_arr[i];
            cout<<"Ingrese la cola Q a la que perenece el proceso "<<processToString(i)<<": ";
            cin>>q_arr[i];
        }
        cout<<"Ingrese el quantum: ";
        cin>>quantum;
        printTable(n, b_arr, q_arr, a_arr);
        mlq(n, b_arr,  q_arr, a_arr, quantum);
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
    cout<<" P |\tAt\t|\tBt\t|\tQ\t|"<<endl;
    for (int i = 0; i<n; i++)
    {  
        cout<<" "<<processToString(i)<<" |\t"<<arriveTimes[i]<<"\t|\t"<<btArr[i]<<"\t|"<<endl;
    }
}

void ejemplo()
{
    int n = 5;
    int * b_arr = (int*)malloc(sizeof(int)*n);
    b_arr[0] = 3;b_arr[1] = 6;b_arr[2] = 8;b_arr[3] = 3; b_arr[4] = 5;
    int * a_arr = (int*)malloc(sizeof(int)*n);
    a_arr[0] = 0;a_arr[1] = 0;a_arr[2] = 0;a_arr[3] = 14; a_arr[4] = 14;
    int quantum = 3;

    printTable(n, b_arr, a_arr);
    mlq(n, b_arr, a_arr, quantum);
}