
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 10

void print(int x[][MAX], int n, int m, char *name)
{
    printf("\n%s:\n", name);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%-4d", x[i][j]);
        printf("\n");
    }
}

int safety(int A[][MAX], int N[][MAX], int AV[], int n, int m, int seq[])
{
    int work[MAX], finish[MAX] = {0}, count = 0;
    for (int i = 0; i < m; i++)
        work[i] = AV[i];

    while (count < n)
    {
        bool found = false;
        for (int i = 0; i < n; i++)
        {
            if (!finish[i])
            {
                bool can = true;
                for (int j = 0; j < m; j++)
                    if (N[i][j] > work[j])
                    {
                        can = false;
                        break;
                    }

                if (can)
                {
                    for (int j = 0; j < m; j++)
                        work[j] += A[i][j];
                    finish[i] = 1;
                    seq[count++] = i;
                    found = true;
                }
            }
        }
        if (!found)
            return 0;
    }
    return 1;
}

void input(int A[][MAX], int M[][MAX], int N[][MAX], int AV[], int *n, int *m)
{
    printf("Processes (max %d): ", MAX);
    scanf("%d", n);
    printf("Resource types (max %d): ", MAX);
    scanf("%d", m);

    for (int i = 0; i < *n; i++)
    {
        printf("\nProcess P%d:\n", i + 1);
        for (int j = 0; j < *m; j++)
        {
            printf("  Alloc R%d: ", j + 1);
            scanf("%d", &A[i][j]);
            printf("  Max R%d: ", j + 1);
            scanf("%d", &M[i][j]);
            while (A[i][j] > M[i][j])
            {
                printf("  Error: Alloc > Max! Enter Alloc again: ");
                scanf("%d", &A[i][j]);
            }
            N[i][j] = M[i][j] - A[i][j];
        }
    }

    printf("\nAvailable resources:\n");
    for (int j = 0; j < *m; j++)
    {
        printf("  R%d: ", j + 1);
        scanf("%d", &AV[j]);
    }
}

int request(int A[][MAX], int N[][MAX], int AV[], int pid, int n, int m)
{
    int req[MAX];
    printf("\nRequest for P%d:\n", pid + 1);
    for (int j = 0; j < m; j++)
    {
        printf("  R%d: ", j + 1);
        scanf("%d", &req[j]);
        if (req[j] > N[pid][j])
        {
            printf("Error: Exceeds need (%d > %d)\n", req[j], N[pid][j]);
            return 0;
        }
        if (req[j] > AV[j])
        {
            printf("Error: Not available (%d > %d)\n", req[j], AV[j]);
            return 0;
        }
    }

    for (int j = 0; j < m; j++)
    {
        AV[j] -= req[j];
        A[pid][j] += req[j];
        N[pid][j] -= req[j];
    }

    int seq[MAX];
    if (safety(A, N, AV, n, m, seq))
    {
        printf("Request granted. Safe seq: ");
        for (int i = 0; i < n; i++)
            printf("P%d ", seq[i] + 1);
        return 1;
    }
    else
    {

        for (int j = 0; j < m; j++)
        {
            AV[j] += req[j];
            A[pid][j] -= req[j];
            N[pid][j] += req[j];
        }
        printf("Request denied (unsafe)\n");
        return 0;
    }
}

void menu()
{
    printf("\n=== BANKER'S ALGORITHM ===\n");
    printf("1. Check safety\n");
    printf("2. Request resources\n");
    printf("3. Show matrices\n");
    printf("4. Exit\n");
    printf("Choice: ");
}

int main()
{
    int A[MAX][MAX], M[MAX][MAX], N[MAX][MAX], AV[MAX];
    int n, m, seq[MAX], choice, pid;

    input(A, M, N, AV, &n, &m);

    do
    {
        menu();
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            if (safety(A, N, AV, n, m, seq))
            {
                printf("System is SAFE\nSequence: ");
                for (int i = 0; i < n; i++)
                    printf("P%d ", seq[i] + 1);
            }
            else
                printf("System is UNSAFE\n");
            break;

        case 2:
            printf("Process ID (1-%d): ", n);
            scanf("%d", &pid);

            if (pid < 1 || pid > n)
            {
                printf("Invalid PID\n");
                break;
            }
            request(A, N, AV, pid - 1, n, m);
            break;

        case 3:
            print(A, n, m, "Allocation");
            print(M, n, m, "Maximum");
            print(N, n, m, "Need");
            printf("\nAvailable: ");
            for (int j = 0; j < m; j++)
                printf("R%d=%d ", j + 1, AV[j]);
            break;

        case 4:
            printf("Exiting\n");
            break;

        default:
            printf("Invalid choice\n");
        }
    } while (choice != 4);

    return 0;
}