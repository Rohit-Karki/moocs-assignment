#include <iostream>
#include <algorithm>

struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int start_time;
    int waiting_time;
    int service_time;
    int turn_around_time;
    int response_time;
    int completion_time;
};

using namespace std;

bool compare_arrival_time(process p1, process p2)
{
    return p1.arrival_time < p2.arrival_time;
}

int main()
{
    int n;
    struct process p[100];

    cout << "Enter the no of process?";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter arrival time of process " << i + 1 << ": ";
        cin >> p[i].arrival_time;
        cout << "Enter burst time of process " << i + 1 << ": ";
        cin >> p[i].burst_time;
        p[i].pid = i + 1;
        cout << endl;
    }
    sort(p, p + n, compare_arrival_time);
    if (n > 0)
    {
        cout << "Process Id"
             << "\t"
             << "Arrival time"
             << "\t"
             << "Burst time"
             << "\t"
             << "Completion time"
             << "\t"
             << "Turn around time"
             << "\t"
             << "Waiting time"
             << "\t"
             << "\n"
             << endl;
    }
    for (int i = 0; i < n; i++)
    {
        if (i > 0)
        {
            p[i].completion_time = p[i - 1].completion_time + p[i].burst_time;
            p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
        }
        else
        {
            p[i].completion_time = p[i].burst_time;
            p[i].turn_around_time = p[i].completion_time - p[i].arrival_time;
            p[i].waiting_time = p[i].turn_around_time - p[i].burst_time;
        }
        cout << p[i].pid << "\t"
             << "\t" << p[i].arrival_time << "\t"
             << "\t" << p[i].burst_time << "\t"
             << "\t" << p[i].completion_time << "\t"
             << "\t"
             << "\t" << p[i].turn_around_time << "\t"
             << "\t"
             << "\t" << p[i].waiting_time << "\t"
             << "\n"
             << endl;
    }
    return 0;
}