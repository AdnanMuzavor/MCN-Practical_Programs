#include<bits/stdc++.h>
using namespace std;
vector<int> add(vector<int> b1,vector<int> b2,int b_size)
{
    int itr=b_size-1;
    vector<int> res(b_size,0);
    int c=0;
    cout<<"\n________________________\n";
    cout<<"Adding: "<<endl;
    for(int i=0; i<b_size; i++)
    {
        cout<<b1[i]<<" ";
    }
    cout<<endl;
    for(int i=0; i<b_size; i++)
    {
        cout<<b2[i]<<" ";
    }
    cout<<endl;
    cout<<"\n________________________\n";
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
    //  cout<<"res size: "<<res.size()<<endl;
    cout<<"res is: ";
    for(int i=0; i<b_size; i++)
    {
        cout<<res[i]<<" ";

    }

    if(c==1)
    {
        cout<<"\nCarry is 01: re-add";
        vector<int> temp(b_size,0);
        temp[b_size-1]=1;
        return add(res,temp,b_size);
    }

    return res;
}
vector<int> complementor(vector<int> a)
{
    vector<int> comp;
    for(int i=0; i<a.size(); i++)
    {
        comp.push_back(a[i]==1?0:1);
    }
    return comp;
}

void receiver(vector<int> data,vector<int> prev,vector<int> comp,int b_size)
{
    vector<int> check=add(prev,comp,b_size);
    vector<int> comp_check=complementor(check);
    bool error=false;
    for(int i=0;i<comp_check.size();i++){
       if(comp_check[i]==1){
         cout<<"\n E R R O R __ D E T E C T E D\nA C K __ T Y P E: negative\n M E S S A G E : Please retransmit the data";
         error=true;
         break;
       }

    }
    if(!error){
      cout<<"\nNO __ E R R O R __ D E T E C T E D\nA C K __ T Y P E: positive\n M E S S A G E : Data receivd successfully";
    }
}

void process(int n,int b_size,vector<int> data)
{
    /*  for(int i=0; i<n; i++)
      {
          cout<<data[i]<<" ";

      }
      cout<<"\n"<<endl;*/
    vector<int> prev,curr,comp;
    ///Init prev and curr
    int itr1=0;
    int itr2=b_size;
    bool init=false;
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

    }

    ///Prev will have addition
    ///Save prev as it is for error detection
    ///What wil be sent receiver is data and complement

    comp=complementor(prev);
    receiver(data,prev,comp,b_size);
}

int main()
{
    int n,b_size,bit;
    vector<int> data;
    cout<<"Enter the number of bits in data stream: ";
    cin>>n;
    cout<<"Enter the block size:  ";
    cin>>b_size;
    cout<<"Enter the data stream received: ";
    for(int i=0; i<n; i++)
    {
        cin>>bit;
        data.push_back(bit);
    }
    process(n,b_size,data);
    //Temp part

    /*   vector<int> b1,b2;
       cout<<"Enter b1: ";
       for(int i=0; i<b_size; i++)
       {
           cin>>bit;
           b1.push_back(bit);
       }
       cout<<endl;
       cout<<"Enter b2: ";
       for(int i=0; i<b_size; i++)
       {
           cin>>bit;
           b2.push_back(bit);
       }
       cout<<endl;
       vector<int> res=add(b1,b2,b_size);
        cout<<"res is: ";
       for(int i=0; i<b_size; i++)
       {
           cout<<res[i]<<" ";

       }*/
    return 0;
}

