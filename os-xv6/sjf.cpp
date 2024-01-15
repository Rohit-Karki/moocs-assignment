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

bool compare_burst_time(process p1, process p2)
{
    return p1.burst_time < p2.burst_time;
}

void findavgTime(process p[], int n)
{
    int total_wt = 0, total_tat = 0;

    // Calculate total waiting time and total turn
    // around time
    for (int i = 0; i < n; i++)
    {
        total_wt = total_wt + p[i].waiting_time;
        // total_tat = total_tat + tat[i];
    }

    cout << "Average waiting time = "
         << (float)total_wt / (float)n;
    // cout << "\nAverage turn around time = "
    //      << (float)total_tat / (float)n;
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
    sort(p, p + n, compare_burst_time);
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

    findavgTime(p, n);

    return 0;
}