
#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

//1,2,3,4,5
//1,3,6,10,15

int main()
{
    int ROWS = 8;
    int COLS = 8;
    
    vector<vector<int>> image = {
     {  0,  0,  0,  0,  0,  0,  0,  0,},
     {  0, 50, 50, 50, 50, 50, 50,  0,},
     {  0, 50,100,100,100,100, 50,  0,},
     {  0, 50,100,255,255,100, 50,  0,},
     {  0, 50,100,255,255,100, 50,  0,},
     {  0, 50,100,100,100,100, 50,  0,},
     {  0, 50, 50, 50, 50, 50, 50,  0,},
     {  0,  0,  0,  0,  0,  0,  0,  0,}
    };
    
    vector<vector<int>> kernel = {
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}
    };

    vector<vector<int>> output(ROWS-2, vector<int>(COLS-2));
    
    for(int i=1; i<ROWS-1; i++){
        for(int j=1; j<COLS-1; j++){
            int sum = 0;
            
            for(int ki = -1; ki <=1; ki++){
                for(int kj = -1; kj<=1; kj++){
                    sum+= image[i+ki][j+kj]* kernel[ki+1][kj+1];
                    // cout<<sum<<endl;
                }
            }
            output[i-1][j-1] = sum/9;
            // cout<<output[i][j]<<" ";
        }
        // cout<<endl;
    }
    // cout<<ROWS<<COLS;
    for(int i=0; i< output.size(); i++){
        // cout<<i;
        for(int j=0; j<output[0].size(); j++){
            // cout<<j;
            cout<<output[i][j]<<" ";
        }
        cout<<endl;
    }
    
    // for(auto& row: output){
    //     for(int val: row){
    //         cout<<val<<" ";
    //     }
    //     cout<<endl;
    // }
    
    return 0;
}




