#include<iostream>
#include<bits/stdc++.h>
using namespace std;
class DataStream
{
public:
    int n; ///Number of bits in data
    int k; ///Number of bits in g(x)
    vector<int> data;
    vector<int> gx;
    DataStream(int n,int k,vector<int> data,vector<int> gx)
    {
        this->n=n;
        this->k=k;
        this->data=data;
        this->gx=gx;
        cout<<"\n____Data Received [Code Word] is___"<<endl;
        cout<<"Data: ";
        for(int i=0; i<n; i++) {cout<<data[i]<<" ";}
        cout<<endl;
        cout<<"G(X): ";
        for(int i=0; i<k; i++){ cout<<gx[i]<<" ";}
        cout<<endl;
    }
};
class CodeWord:public DataStream
{
public:
    vector<int> quot;
    vector<int> curr_divident;
    CodeWord(int n,int k,vector<int> data,vector<int> gx):DataStream(n,k,data,gx)
    {
        vector<int> temp(data.begin(),data.begin()+k);
        curr_divident=temp;
    }
    void Verify()
    {
        bool no_error=true;
        cout<<"\n_____C O N C L U S I O N_____\nRemainder obntained after division is: "<<endl;

        for(int i=0;i<curr_divident.size();i++){
        cout<<curr_divident[i]<<" ";
            }
            cout<<endl;
        for(int i=0;i<curr_divident.size();i++){
                int bit=curr_divident[i];

            if(bit!=0){
                no_error=false;
                cout<<"Remainder Obtained is NOT zero || Hence ask sender to resend the data"<<endl;
            }
        }
        if(no_error){
            cout<<"\nData received without any ERROR"<<endl;
            cout<<"\nActual Data is: ";

          for(int i=0;i<data.size()-curr_divident.size();i++){
            cout<<data[i]<<" ";
        }
        }

    }
    void Divide()
    {
        int special_break=0;
        int nextbit=k;
        /// => Iterate till no bits are left in data to be appended
        while(nextbit<data.size())
        {
            /// => If data[0] i.e first bit is NOT 1 it's not divisible
            /// => Append 0 to quototient and update the divident before xoring
            if(curr_divident[0]==0)
            {
                quot.push_back(0);
                ///Remove first bit
                curr_divident.erase(curr_divident.begin(),curr_divident.begin()+1);
                ///Push the next bit into divident
                curr_divident.push_back(data[nextbit++]);
                ///Continue xoring AS WE HAVE UPDATED the divident already
            }
            /// => Xor each element of divident
            for(int i=0; i<k; i++)curr_divident[i]=(curr_divident[i]^gx[i]);
            quot.push_back(1);
            ///Remove first bit
            curr_divident.erase(curr_divident.begin(),curr_divident.begin()+1);
            /// =>  Applied only when next bit has reach size at which there is no further bit to append
            if(nextbit==data.size())
            {
                special_break=1;
                break;
            }
            ///Push the next bit into divident
            curr_divident.push_back(data[nextbit++]);
        }
        /// => ELIMINATE the first bit, remainig bits is remainder as we need [K-1] bits only
        if(!special_break) curr_divident.erase(curr_divident.begin(),curr_divident.begin()+1);
        ///_________________VERIFY FROM REMAINDER___________________
        Verify();
    }
};

int main()
{
    int n,k,bit;
    vector<int> data,gx;
    cout<<"Enter the number of bits in received code word: ";
    cin>>n;
    cout<<"Enter the number of bits in g(x): ";
    cin>>k;
    cout<<"Enter the code word received: ";
    for(int i=0; i<n; i++)
    {   cin>>bit;
        data.push_back(bit);
    }
    cout<<"Enter the g(x) stream: ";
    for(int i=0; i<k; i++)
    {   cin>>bit;
        gx.push_back(bit);
    }
    CodeWord *c1=new CodeWord(n,k,data,gx);
    c1->Divide();
    return 0;
}
