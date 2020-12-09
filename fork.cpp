#include <iostream>
#include <bits/stdc++.h>
#include <sys/types.h> 
#include <unistd.h>

using namespace std;

int arr[100];
int even_sum = 0, odd_sum = 0;

void fill_arr()
{
    for(int i=0; i<100; ++i)
        arr[i] = 100 - i;   
}

void calculate_odd()
{
    for(int i=0; i<100; ++i)
        if(arr[i]%2 == 1)
            odd_sum +=  arr[i];
}

void calculate_even()
{
    for(int i=0; i<100; ++i)
        if(arr[i]%2 == 0)
            even_sum +=  arr[i];
}

void sort_arr()
{
    sort(arr, arr+100);
}

void solve()
{
    fill_arr();
    for(int i=0; i<100; ++i)
        cout << arr[i] << " ";
    cout << "\n";    
    
    //fork call
    int p1 = fork();
    int p2 = fork();
   
    if(p1 > 0 && p2 > 0){
        calculate_odd();
        cout << "paremt process\n";
        cout << "Sum of odd number: " << odd_sum << "\n";
    }
    
    else if(p1 == 0 && p2 > 0){
        calculate_even();
        cout << "child process 1\n";
        cout << "Sum of even number: " << even_sum << "\n";
    }

    else if(p1 > 0 && p2 == 0){
        sort_arr();
        cout << "child process 2\n";
        cout << "sorted arr: \n";
        
        for(int i=0; i<100; ++i)
            cout << arr[i] << " ";
    }
    
}


int main()
{
    
    solve();

    return 0;
}
