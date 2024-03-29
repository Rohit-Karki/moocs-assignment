#include <iostream>
#include <algorithm>
#include <queue>

const int quantum_size = 2;
struct process
{
    int pid;
    int arrival_time;
    int burst_time;
    int remaining_burst_time;
    int start_time;
    int waiting_time;
    int service_time;
    int turn_around_time;
    int response_time;
    int completion_time;
};
using namespace std;

bool Compare(process &a, process &b)
{
    return a.arrival_time > b.arrival_time;
}

std::priority_queue<process, std::vector<process>, decltype(&Compare)> processes(Compare);

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
        p[i].remaining_burst_time = p[i].burst_time;
        cout << endl;
    }
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
        process pp = p[i];
        processes.push(pp);
    }
    int t = 0;
    while (1)
    {
        bool done = true;
        for (int i = 0; i < n; i++)
        {
            process current_process = processes.top();
            processes.pop();
            if (current_process.remaining_burst_time > 0)
            {
                done = false;
                if (current_process.remaining_burst_time > quantum_size)
                {
                    t += quantum_size;
                    current_process.remaining_burst_time -= quantum_size;
                    processes.push(current_process);
                }
                else
                {
                    t += p[i].remaining_burst_time;
                    current_process.waiting_time = t - p[i].burst_time - p[i].arrival_time;
                    current_process.completion_time = t;
                    done = true;
                    cout << "The waiting time is " << current_process.waiting_time << endl;
                }
            }
        }

        if (done)
            break;
    }

    // findavgTime(p, n);

    return 0;
}