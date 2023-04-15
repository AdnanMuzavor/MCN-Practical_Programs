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

class checksumReceiver: public binary_utilities
{
    vector<int> data;
    vector<int> codeword;
    int b_size;
    int no_of_bits;
    bool e=false; ///error
public:
    checksumReceiver(int n,int b_size,vector<int> data,bool e)
    {
        this->b_size=b_size;
        this->no_of_bits=n;
        this->data=data;
        this->e=e;
        receiver();
    }
///Messaeg displayer
    void display(bool error)
    {
        if(error)
        {
            cout<<"\n- - - - - - - - - - - - - - - - -";
            cout<<"\nE R R O R __ D E T E C T E D\nA C K __ T Y P E: negative\nM E S S A G E : Please retransmit the data";
            error=true;
            cout<<"\n- - - - - - - - - - - - - - - - -";
        }
        else
        {
            cout<<"\n- - - - - - - - - - - - - - - - -";
            cout<<"\nNO __ E R R O R __ D E T E C T E D\nA C K __ T Y P E: positive\nM E S S A G E : Data receivd successfully";
            cout<<"\n- - - - - - - - - - - - - - - - -";
            cout<<"\nActual data extracted from code word is: ";
            int last=data.size()/b_size;
            for(int i=0; i<data.size()-b_size; i++)
            {

                cout<<data[i]<<" ";
            }
        }

    }
    /// Sender
    void receiver()
    {
        ///Phase where error is introduce
        if(e)
        {
            data[1]=data[1]==1?0:1;
        }
        cout<<endl;
        cout<<"Data Received from sender is: ";
        for(int i=0; i<data.size(); i++)
        {
            cout<<data[i]<<" ";
        }
        cout<<endl;

        ///Get addition's complement from current data,data has checksum so it too will be added along
        vector<int> comp_check=process(no_of_bits,b_size,data);

        cout<<"the sum obtained after adding blocks is: ";
        for(int i=0; i<comp_check.size(); i++)
        {
            cout<<comp_check[i]<<" ";
        }
        cout<<endl;
        comp_check=complementor(comp_check);
        cout<<"Complement of sum is: ";
        for(int i=0; i<comp_check.size(); i++)
        {
            cout<<comp_check[i]<<" ";
        }
        cout<<endl;
        bool error=false;
        for(int i=0; i<comp_check.size(); i++)
        {

            if(comp_check[i]==1)
            {
                error=true;
                display(error);
                break;
            }

        }
        if(!error)
        {
            display(error);
        }

    }
};
int main()
{
    int n,b_size,bit;
    vector<int> data;
    cout<<"Enter the number of bits in code word received: ";
    cin>>n;
    cout<<"Enter the block size:  ";
    cin>>b_size;
    cout<<"Enter the data stream received: ";
    for(int i=0; i<n; i++)
    {
        cin>>bit;
        data.push_back(bit);
    }
    checksumReceiver c1=checksumReceiver(n,b_size,data,false);
    cout<<endl;
    checksumReceiver c2=checksumReceiver(n,b_size,data,true);
    return 0;
}
