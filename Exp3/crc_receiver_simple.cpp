

#include <iostream>
#include <cstring>

using namespace std;

void receiver(int data[],int gen[],int m,int k)  //Receiver function
 {
    int temp[m+k-1];
    memset(temp,0,sizeof(temp));

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

    bool valid=true;  //Checks if the remainder is zero
    cout<<"\nRemainder is: ";
    for(int i=0;i<m+k-1;i++)
    {
        cout<<temp[i]<<" ";
        if (temp[i]!=0)
        {
            valid=false;
            break;
        }
    }

    if (valid)
    {
        cout<<"\n\nSince Remainder is zero,No Error Detected!!"<< endl;
        cout<<"\nActual Data received is: ";
        for(int i=0;i<m-(k-1);i++){
            cout<<data[i]<<" ";
        }
    }
    else
    {
       cout<<"\n\nSince Remainder is not equal to zero,Error Detected!!"<< endl;
    }
}

int main()
{
    int m,k;  //Declaration

    cout<<"Enter the size of received codeword: ";
    cin>>m;
    cout<<"Enter the size of g(x): ";
    cin>>k;

    int data[m+k-1],gen[k];

    cout<<"\nEnter the received codeword: ";  //Accepting received codeword
    for(int i=0;i<m;i++)
    {
        cin>>data[i];
    }

    cout<<"Enter g(x): ";  //Accepting generator polynomial
    for(int i=0;i<k;i++)
    {
        cin>>gen[i];
    }

    receiver(data,gen,m,k);  //Performs CRC at the receiver side and checks whether the received codeword contains an error or not

    return 0;
}
