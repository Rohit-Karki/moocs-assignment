#include <iostream>

void matrixinput(int M[][10], int row, int col)
{
    for (i = 0; i < row; i++)
    {
        for (i = 0; i < col; i++)
        {
            scanf(“% d”, &M[i][j]);
        }
    }
}
void matrixdisplay(int M[][10], int row, int col)
{
    for (i = 0; i < row; i++)
    {
        for (i = 0; i < col; i++)
        {
            printf(“% d\t”, &M[i][j]);
        }
        printf(“\n”)
    }
}

void calculateNeed(need, maxm, allot)
{
    for (i = 0; i < m; i++)
    {
        for (i = 0; i < n; i++)
        {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes[], int avail[], int maxm[][R],
            int allot[][R])
{
    int need[P][R];

    // Function to calculate need matrix
    calculateNeed(need, maxm, allot);

    // Mark all processes as infinish
    bool finish[P] = {0};

    // To store safe sequence
    int safeSeq[P];

    // Make a copy of available resources
    int work[R];
    for (int i = 0; i < R; i++)
        work[i] = avail[i];

    // While all processes are not finished
    // or system is not in safe state.
    int count = 0;
    while (count < P)
    {
        // Find a process which is not finish and
        // whose needs can be satisfied with current
        // work[] resources.
        bool found = false;
        for (int p = 0; p < P; p++)
        {
            // First check if a process is finished,
            // if no, go for next condition
            if (finish[p] == 0)
            {
                // Check if for all resources of
                // current P need is less
                // than work
                int j;
                for (j = 0; j < R; j++)
                    if (need[p][j] > work[j])
                        break;

                // If all needs of p were satisfied.
                if (j == R)
                {
                    // Add the allocated resources of
                    // current P to the available/work
                    // resources i.e.free the resources
                    for (int k = 0; k < R; k++)
                        work[k] += allot[p][k];

                    // Add this process to safe sequence.
                    safeSeq[count++] = p;

                    // Mark this p as finished
                    finish[p] = 1;

                    found = true;
                }
            }
        }

        // If we could not find a next process in safe
        // sequence.
        if (found == false)
        {
            cout << "System is not in safe state";
            return false;
        }
    }

    // If system is in safe state then
    // safe sequence will be as below
    cout << "System is in safe state.\nSafe"
            " sequence is: ";
    for (int i = 0; i < P; i++)
        cout << safeSeq[i] << " ";

    return true;
}

int main()
{
    int available[10];

    int max[10][10], allocation[10][10];
    cout
        << "Enter the no of process" << endl;
    cin >> m;
    cout << "Enter the no of resouce instances" << endl;
    cin >> n;
    int need[P][R];
    for (i = 0; i < m; i++)
    {
        cin >> available[i];
    }

    matrixinput(max, m, n);
    matrixinput(allocation, m, n);


    if(isSafe(max,allocation))
}