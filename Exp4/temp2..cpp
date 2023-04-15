
#include <iostream>
#include <cstring>

using namespace std;

void sender(int data[],int gen[],int m,int k)  //Sender function
 {
    int temp[m+k-1]; // create temporary array to store message and CRC bits
    memset(temp,0,sizeof(temp)); // initialize temp array with 0

    for(int i=0;i<m;i++)  //Copy data into temp
    {
      temp[i]=data[i];
    }

    for(int i=0;i<m;i++)  //Perform modulo-2 division
    {
        if(temp[i]==1)
        {
            for(int j=0;j<k;j++)
            {
                temp[i+j]=temp[i+j]^gen[j];
            }
        }
    }

    for(int i=m;i<m+k-1;i++)  //Copy the CRC code from temp into the data
    {
        data[i]=temp[i];
    }

    cout << "\nThe CRC code is: "; //Display the CRC code
    for(int i=m;i<m+k-1;i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;

    cout<<"The codeword is: ";  //Display resulting codeword
    for(int i=0;i<m+k-1;i++)
    {
        cout<<data[i]<<" ";
    }
    cout<<endl;
}

int main()
{
    int m,k;  //Declaration

    cout<<"Enter the size of data: ";
    cin>>m;
    cout<<"Enter the size of g(x): ";
    cin>>k;

    int data[m+k-1],gen[k];

    cout<<"\nEnter the data: ";  //Accepting data
    for(int i=0;i<m;i++)
    {
        cin>>data[i];
    }

    cout<<"Enter g(x): ";  //Accepting generator polynomial
    for(int i=0;i<k;i++)
    {
        cin>>gen[i];
    }

    sender(data,gen,m,k);  //Performs CRC at the sender side and displays the CRC code and the codeword

    return 0;
}
