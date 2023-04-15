#include<bits/stdc++.h>
using namespace std;

class binary_utilities
{
public:
    ///Add two binary numbers
    vector<int> add(vector<int> b1,vector<int> b2,int b_size)
    {
        int itr=b_size-1;
        vector<int> res(b_size,0);
        int c=0;
        while(itr>=0)
        {

            ///Get bits
            int b1_bit=b1[itr];
            int b2_bit=b2[itr];
            ///If both 1
            if(b1_bit==1 && b2_bit==1)
            {
                ///Carry wa 01
                if(c==1)
                {
                    c=1;
                    res[itr]=1;
                }
                ///Carry was not 01
                else
                {
                    c=1;
                    res[itr]=0;
                }
            }
            ///Any one bit is 01 case
            else if(b1_bit==1 || b2_bit==1)
            {
                ///Carry wa 01
                if(c==1)
                {
                    c=1;
                    res[itr]=0;
                }
                ///Carry was not 01
                else
                {
                    res[itr]=1;
                }
            }
            ///Both bits zero case
            else
            {
                ///Carry wa 01
                if(c==1)
                {
                    c=0;
                    res[itr]=1;
                }
                ///Carry was not 01
                else
                {
                    res[itr]=0;
                }
            }
            ///Update itr
            itr--;
        }
        ///iF CARRY = 1 => rEADD IT TO ANS OBTAINED
        if(c==1)
        {
            vector<int> temp(b_size,0);
            temp[b_size-1]=1;
            return add(res,temp,b_size);
        }
        return res;
    }
///Complement given binary number
    vector<int> complementor(vector<int> a)
    {
        vector<int> comp;
        for(int i=0; i<a.size(); i++)
        {
            comp.push_back(a[i]==1?0:1);
        }
        return comp;
    }
///Process transalte he gien daa stream into blocks
/// It transalted into blocks and added
    vector<int> process(int n,int b_size,vector<int> data)
    {

        vector<int> prev,curr,comp;
        ///Init prev and curr
        int itr1=0;
        int itr2=b_size;
        bool init=false;
           int additions=0;
        while(itr2<data.size())
        {
            ///If not initialsed
            if(!init)
            {
                while(itr2<(2*b_size))
                {
                    prev.push_back(data[itr1++]);
                    curr.push_back(data[itr2++]);
                    init=true;
                }
            }

            ///prev will be result of prev addition
            ///Curent will be the next block
            prev=add(prev,curr,b_size);
            int ele=0;
            ///Clean the curr
            curr.erase(curr.begin(),curr.end());
            ///Fill in the new curr
            while(itr2<data.size() && ele<b_size)
            {
                curr.push_back(data[itr2++]);
                ele++;
            }
              additions++;
        }


        if(additions!=(data.size()/b_size)-1) return add(prev,curr,b_size);
        return prev;

    }
};

class checksumSender: public binary_utilities
{
    vector<int> data;
    vector<int> codeword;
    int b_size;
    int no_of_bits;
public:
    checksumSender(int n,int b_size,vector<int> data)
    {
        this->b_size=b_size;
        this->no_of_bits=n;
        this->data=data;
        sender();
    }

/// Sender
    void sender()
    {
        ///Get addition's complement
        vector<int> checksum_word=process(no_of_bits,b_size,data);
        ///process will retun sum of blocks
        ///What wil be sent receiver is data and complement
        checksum_word=complementor(checksum_word);
        ///Checksum generated is:
        cout<<"Checksum is ";
          for(int i=0;i<checksum_word.size();i++){
            cout<<checksum_word[i]<<" ";
        }
        ///Append Complemented block to data to make code word
        for(int i=0;i<checksum_word.size();i++){
            data.push_back(checksum_word[i]);
        }
        cout<<endl;
        cout<<"Data sent to receiver [Data with checksum] is: ";
        for(int i=0;i<data.size();i++) cout<<data[i]<<" ";
        cout<<endl;

    }
};
int main()
{
    int n,b_size,bit;
    vector<int> data;
    cout<<"Enter the number of bits in data stream: ";
    cin>>n;
    cout<<"Enter the block size:  ";
    cin>>b_size;
    cout<<"Enter the data stream to be sent ";
    for(int i=0; i<n; i++)
    {
        cin>>bit;
        data.push_back(bit);
    }
    checksumSender c1=checksumSender(n,b_size,data);
    return 0;
}
