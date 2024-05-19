#include<iostream>
#include<algorithm>
using namespace std;

typedef struct Item
{
    int value;
    int weight;

}item;

bool myCmp(item a, item b)
{
    double r1 = (double)a.value/(double)a.weight;
    double r2 = (double)b.value/(double)b.weight;

    return r1 > r2;
}

// Using Fractional Knapsack Approach
// Time Complextiy -> O(n*logn)
double fractionalKnapsack(int cap, item arr[], int n)
{
    sort(arr, arr+n, myCmp);

    double result = 0.0;

    for(int i=0; i<n; i++)
    {
        if(arr[i].weight <= cap)
        {
            cap -= arr[i].weight;
            result += arr[i].value;
        }
        else
        {
            result += arr[i].value*(double(cap)/double(arr[i].weight));
            break;
        }
    }
    return result;
}

//Using DP Approach
//Time Complexity -> O(cap*n)
int knapsackDP(int cap, item arr[], int n)
{
    int dp[n+1][cap+1];

    for(int i=0; i<=cap; i++)
        dp[0][i] = 0;
    for(int i=0; i<=n; i++)
        dp[i][0] = 0;

    for(int i=1; i<=n; i++)
    {
        for(int j=1; j<=cap; j++)
        {
            if(arr[i-1].weight > j) 
                dp[i][j] = dp[i-1][j];
            else
                dp[i][j] = max((arr[i-1].value+dp[i-1][j-arr[i-1].weight]), (dp[i-1][j]));
        }
    }
    return dp[n][cap];
}

int main()
{
    int n;
    cout<<"Enter the number of items : ";
    cin>>n;

    item items[n];

    for(int i=0; i<n; i++)
    {
        cout<<"\nEnter value of item "<<i+1<<" : ";
        cin>>items[i].value;
        cout<<"Enter weight of item "<<i+1<<" : ";
        cin>>items[i].weight;
    }

    int cap;
    cout<<"\nEnter capacity of knapsack : ";
    cin>>cap;

    // Calculating result using Fractional Knapsack
    double resultFK = fractionalKnapsack(cap, items, n);
    printf("\nThe maximum profit of knapsack using 'Fractional Knapsack' approach can be : %.2f", resultFK);

    // Calculating result using Dynamic Programming
    int resultFDP = knapsackDP(cap, items, n);
    cout<<"\nThe maximum profit of knapsack using 'Dynamic Programming' approach can be : "<<resultFDP;

    return 0;
}