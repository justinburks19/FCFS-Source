//Help from Citation sources!!
#include <iostream>
#include <algorithm> 
#include <iomanip> 
#include <fstream>
#include <sstream>
#include <assert.h>
using namespace std;

struct process {  //What will be needed in order to execute entire file and process FCFS
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
};

bool compareArrival(process p1, process p2) //Comparing arrival time
{
    return p1.arrival_time < p2.arrival_time;
}

bool compareID(process p1, process p2) //Compare ID's for FCFS
{
    return p1.pid < p2.pid;
}


int main() {
    ifstream inFile;        //Read Text File
    inFile.open("Text.txt");
    int start = 0;
    int x[50], y[50], z[50];
    while (!inFile.eof())
    {
        inFile >> x[start] >> y[start] >> z[start];
        start++;
    }

    int n;              
    struct process p[50];
    int total_turnaround_time = 0;  
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    float avg_turnaround_time; 
    float avg_waiting_time;
    float avg_response_time;
    float cpu_efficiency;
    float cpu_efficiencyv2;

    cout << setprecision(2) << fixed;
    n = 50;
    for (int i = 0; i < start; i++) {
        p[i].arrival_time=y[i];
        p[i].burst_time=z[i];
        p[i].pid = i + 1;
    }

    sort(p, p + n, compareArrival); //Sorting algo in order to list in arrival time.

    for (int i = 0; i < n; i++) {       //With Each processes being queued, calculations must be done!
        p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
        p[i].completion_time = p[i].start_time + p[i].burst_time;
        p[i].turnaround_time = p[i].completion_time - p[i].arrival_time;
        p[i].waiting_time = p[i].turnaround_time - p[i].burst_time;
        p[i].response_time = p[i].start_time - p[i].arrival_time;

        total_turnaround_time += p[i].turnaround_time;
        total_waiting_time += p[i].waiting_time;
        total_response_time += p[i].response_time;
        total_idle_time += (i == 0) ? (p[i].arrival_time) : (p[i].start_time - p[i - 1].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n; //Find averages for TAT, WT, RT, CPU Efficiency and Total Switch Time
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_efficiency = ((p[n - 1].completion_time - total_idle_time) / (float)p[n - 1].completion_time) * 100; //Efficiency = Total Execution Time/ (Total Execution time + Total Switching time) )
    sort(p, p + n, compareID);

    cout << endl;
    cout << "First Come First Serve (FCFS)" << endl;
    cout << endl;
    cout << "Total Time Requires " << p[49].completion_time << " time units" << endl;
    cout << endl;
    cout << "Average Waiting Time = " << avg_waiting_time << " time units" << endl;
    cout << endl;
    cout << "CPU efficiency = " << cpu_efficiency << "%" << endl;
    cout << endl;


    for (int i = 0; i < n; i++) {
       
        cout << "Process " << p[i].pid << ":" << endl;
        cout << "Service time = " << p[i].completion_time << endl;
        cout << "Turnaround time = " << p[i].turnaround_time << endl;
    }
    cout << "#P\t" << "AT\t" << "BT\t" << "ST\t" << "CT\t" << "TAT\t" << "WT\t" << "RT\t" << "\n" << endl;
    for (int i = 0; i < n; i++) {
        cout << p[i].pid << "\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << "\n" << endl;
    }
}