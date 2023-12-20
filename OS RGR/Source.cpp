#include <iostream>
#include <vector>

// �������� ������� ��� ������ ���� �������� ��� ��������� ����������������

using namespace std;

const int MAX_PROCESSES = 3;              
const int MAX_RESOURCES = 3;               

vector<int> availableResources(MAX_RESOURCES, 0);  // ��������� �������
vector<vector<int>> maximum(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0)); // ������������ ����������� ������� ��������
vector<vector<int>> allocationResources(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0)); // �������, ���������� ������� ��������
vector<vector<int>> missingResources(MAX_PROCESSES, vector<int>(MAX_RESOURCES, 0)); // ����������� ������� ��� ������� ��������

bool isSafe(int process, vector<int>& request) 
{
    for (int i = 0; i < MAX_RESOURCES; i++)
    {
        if (request[i] > maximum[process][i])
        {
            return false;
        }
    }
   
    for (int i = 0; i < MAX_RESOURCES; i++) 
    {
        if (request[i] > availableResources[i]) 
            return false; 
    }

    // ��������� �������� � �������� ����������� ��������� �������
    for (int i = 0; i < MAX_RESOURCES; i++) 
    {
        availableResources[i] -= request[i];
        allocationResources[process][i] += request[i];
        missingResources[process][i] -= request[i];
    }

   
    vector<bool> finish(MAX_PROCESSES, false);
    vector<int> work = availableResources;

    while (true) 
    {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) 
        {
            if (!finish[i]) 
            {
                int j;
                for (j = 0; j < MAX_RESOURCES; j++) 
                {
                    if (missingResources[i][j] > work[j]) 
                        break;
                }

                if (j == MAX_RESOURCES) 
                {
                    for (int k = 0; k < MAX_RESOURCES; k++)
                        work[k] += allocationResources[i][k];
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found)  // �� ������� ����� �������, ������� �� � ���������� ���������
        {
            // ����� ��������� ��������
            for (int i = 0; i < MAX_RESOURCES; i++)
            {
                availableResources[i] += request[i];
                allocationResources[process][i] -= request[i];
                missingResources[process][i] += request[i];
            }

            return false;
        }

        
        bool allFinished = true;

        for (int i = 0; i < MAX_PROCESSES; i++) 
        {
            if (!finish[i])
            {
                allFinished = false;
                break;
            }
        }

        if (allFinished)
            return true;
    }
}

void releaseResources(int process, vector<int>& release) 
{
   
    for (int i = 0; i < MAX_RESOURCES; i++) 
    {
        availableResources[i] += release[i];
        allocationResources[process][i] -= release[i];
        missingResources[process][i] += release[i];
    }
}

int main() 
{
    system("chcp 1251");

    cout << "������� ���������� ��������� ��������:" << endl;
    for (int i = 0; i < MAX_RESOURCES; i++) 
        cin >> availableResources[i];

    cout << "������� ������������ ����������� ������� ��������:" << endl;
    for (int i = 0; i < MAX_PROCESSES; i++) 
    {
        cout << "������� " << i << ": ";
        for (int j = 0; j < MAX_RESOURCES; j++) 
        {
            cin >> maximum[i][j];
            missingResources[i][j] = maximum[i][j];
        }
    }

   
    int process;

    while (true) 
    {
        cout << "������� ����� �������� (-1 ��� ������): ";
        cin >> process;

        if (process == -1)
            break;

        vector<int> request(MAX_RESOURCES, 0);
        cout << "������� ������ �������� ��� �������� " << process << ": ";
        for (int i = 0; i < MAX_RESOURCES; i++)
            cin >> request[i];

        if (isSafe(process, request)) 
            cout << "������� �������� �������." << endl;
        else
            cout << "������ �� ��������� �������� ��������. ������� � ������������ ���������." << endl;


        vector<int> release(MAX_RESOURCES, 0);
        cout << "������� ������������ �������� ��� �������� " << process << ": ";
        for (int i = 0; i < MAX_RESOURCES; i++) 
            cin >> release[i];

        releaseResources(process, release);
    }

    return 0;
}
