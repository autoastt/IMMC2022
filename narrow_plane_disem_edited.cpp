#include<bits/stdc++.h>
#include "Sequence_Generator.h"
using namespace std;
const int N=50,M=50,NXM=350,NS=1000;
info p[NXM];
bool arr[N][M];
double t_boarding,t_disembarking,t_seat=4,t_walk=2,wait[NXM];
int nPeople,nRows,nCols,bin[M][2];
double t_boarding_avg,t_disembarking_avg;
vector<double> t_boarding_acc,t_disembarking_acc;
map<int,string> state;
map<char,int> side,c2i;
set<int> s;

void boarding(){
    while(!s.empty()){
        t_boarding++;
        for(int i=1;i<=nPeople;i++){
            //cout << t_boarding << " " << i << " " << state[i] << " " << p[i].pos << " " << wait[i] << "\n";
            if(state[i]=="Not in Aisle"){
                if(arr[4][1]) break;
                state[i]="In Aisle";
                arr[4][1]=true;
                wait[i]=p[i].speed;
                p[i].pos=1;
                break;
            }
            else if(state[i]=="In Aisle"){
                // at thier seat
                if(p[i].pos==p[i].seaty){
                    state[i]="Storage";
                    wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2); // time step for storage
                    // no luggage, just wait for seating
                    if(wait[i]==0){
                        state[i]="Waiting";
                        bin[p[i].seaty][side[p[i].seatx]]+=p[i].luggage;
                        // if there are people sit before
                        if(p[i].seatx=='A' and (arr[2][p[i].seaty] and arr[3][p[i].seaty])){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seatx=='A' and (arr[2][p[i].seaty] or arr[3][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='B' and arr[3][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='E' and arr[5][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='F' and (arr[5][p[i].seaty] and arr[6][p[i].seaty])){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seatx=='F' and (arr[5][p[i].seaty] or arr[6][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        state[i]="Seated";
                        arr[4][p[i].seaty]=false;
                        arr[c2i[p[i].seatx]][p[i].seaty]=true;
                        p[i].pos=-1;
                        s.erase(i);
                    }
                    continue;
                }
                wait[i]--;
                if(wait[i]==0){
                    // there is space in front of them
                    if(!arr[4][p[i].pos+1]){
                        arr[4][p[i].pos]=false;
                        arr[4][++p[i].pos]=true;
                        wait[i]=p[i].speed;
                    }
                    else wait[i]=1;
                }
            }
            else if(state[i]=="Storage"){
                wait[i]--;
                if(wait[i]==0){
                    state[i]="Waiting";
                    bin[p[i].seaty][side[p[i].seatx]]+=p[i].luggage;
                    // if there are people sit before
                    if(p[i].seatx=='A' and (arr[2][p[i].seaty] and arr[3][p[i].seaty])){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seatx=='A' and (arr[2][p[i].seaty] or arr[3][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='B' and arr[3][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='E' and arr[5][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='F' and (arr[5][p[i].seaty] and arr[6][p[i].seaty])){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seatx=='F' and (arr[5][p[i].seaty] or arr[6][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    state[i]="Seated";
                    arr[4][p[i].seaty]=false;
                    arr[c2i[p[i].seatx]][p[i].seaty]=true;
                    p[i].pos=-1;
                    s.erase(i);
                }
            }
            else if(state[i]=="Waiting"){
                wait[i]--;
                if(wait[i]==0){
                    state[i]="Seated";
                    arr[4][p[i].seaty]=false;
                    arr[c2i[p[i].seatx]][p[i].seaty]=true;
                    p[i].pos=-1;
                    s.erase(i);
                }
            }
            else if(state[i]=="Seated") continue;
        }
        //cout << t_boarding << " " << s.size() << "\n";
    }
}

void disembarking(){
    set<int> out;
    vector<pair<int,int>> q;
    while(out.size()<nPeople){
        t_disembarking++;
        for(int check=0;check<3;check++){
            for(int i=1;i<=nPeople;i++){
                if(state[i]=="Seated"){
                    p[i].pos=p[i].seaty;
                    if(p[i].seatx=='A' and !arr[2][p[i].seaty]){
                        arr[1][p[i].seaty]=false;
                        arr[2][p[i].seaty]=true;
                        p[i].seatx='B';
                    }
                    else if(p[i].seatx=='B' and !arr[3][p[i].seaty]){
                        arr[2][p[i].seaty]=false;
                        arr[3][p[i].seaty]=true;
                        p[i].seatx='C';
                    }
                    else if(p[i].seatx=='C' and !arr[4][p[i].seaty]){
                        state[i]="Waiting";
                        arr[3][p[i].seaty]=false;
                        arr[4][p[i].seaty]=true;
                        p[i].seatx='X';
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='D' and !arr[4][p[i].seaty]){
                        state[i]="Waiting";
                        arr[5][p[i].seaty]=false;
                        arr[4][p[i].seaty]=true;
                        p[i].seatx='Y';
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='E' and !arr[5][p[i].seaty]){
                        arr[6][p[i].seaty]=false;
                        arr[5][p[i].seaty]=true;
                        p[i].seatx='D';
                    }
                    else if(p[i].seatx=='F' and !arr[6][p[i].seaty]){
                        arr[7][p[i].seaty]=false;
                        arr[6][p[i].seaty]=true;
                        p[i].seatx='E';
                    }
                }
            }
        }
        for(int i=1;i<=nPeople;i++){
            if(state[i]=="Waiting"){
                wait[i]--;
                if(wait[i]==0){
                    state[i]="Storage";
                    // time step for storage
                    wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2);
                    if(wait[i]==0){
                        bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                        state[i]="In Aisle";
                        wait[i]=p[i].speed;
                        q.push_back({p[i].pos,i});
                    }
                }
            }
            else if(state[i]=="Storage"){
                wait[i]--;
                if(wait[i]==0){
                    bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                    state[i]="In Aisle";
                    wait[i]=p[i].speed;
                    q.push_back({p[i].pos,i});
                }
            }
        }
        sort(q.begin(),q.end());
        for(int j=0;j<q.size();j++){
            int i=q[j].second;
            //cout << t_disembarking << " " << out.size() << " " << i << " " << state[i] << " " << wait[i] << " " << p[i].pos << " " << p[i].luggage << " " << bin[p[i].seaty][side[p[i].seatx]] << "\n";
            if(state[i]=="In Aisle"){
                wait[i]--;
                if(wait[i]==0){
                    // there is space in front of them
                    if(!arr[4][p[i].pos-1]){
                        arr[4][p[i].pos]=false;
                        arr[4][--p[i].pos]=true;
                        q[j].first=p[i].pos;
                        if(p[i].pos==0){
                            state[i]="Not in Aisle";
                            p[i].pos=-1;
                            arr[4][0]=false;
                            out.insert(i);
                            q.erase(q.begin()+j);
                            continue;
                        }
                        wait[i]=p[i].speed;
                    }
                    else wait[i]=1;
                }
            }
        }
        //cout << t_disembarking << " " << out.size() << "\n";
    }
}

int main(){
    ofstream myfile;
    myfile.open("edited.csv");
    int k=1,temp;
    side['A']=side['B']=side['C']=side['X']=0;
    side['D']=side['E']=side['F']=side['Y']=1;
    c2i['A']=1;
    c2i['B']=2;
    c2i['C']=3;
    c2i['D']=5;
    c2i['E']=6;
    c2i['F']=7;
    //cin >> nPeople;
    nPeople=198;
    p[0].pos=1e9;
    //for(int i=1;i<=nPeople;i++) cout << i << " " << p[i].pos << " " << p[i].seatx << " " << p[i].seaty << " " << p[i].luggage << " " << p[i].speed << "\n";
    for(int j=1;j<=NS;j++){
        if(j==NS) cout << "END!";
        else if(j%100==0) cout << "Simulation number: " << j << "\nKeep going. . .\n";
        fill_n(arr[0],N*M,false);
        fill_n(wait,NXM,0);
        fill_n(bin[0],M*2,0);
        //random(p,nPeople,6,j);
        seat(p,nPeople,6,20,j);
        //section(p,nPeople,6,3,60,j,6);
        //repyramid(p,60,j);
        //cout << j << " before rand\n";
        //seatsection(p,nPeople,6,60,j);
        //cout << "after rand\n";
        //test_case1(p,nPeople,6,33);
        for(int i=1;i<=nPeople;i++){
            s.insert(i);
            state[i]="Not in Aisle";
            p[i].pos=0;
            //cout << i << " " << p[i].pos << " " << p[i].seatx << " " << p[i].seaty << " " << p[i].luggage << " " << p[i].speed << "\n";
        }
        boarding();
        //cout << "disem\n";
        disembarking();
        //cout << "fin\n";
        //cout << "time " << j << " = " << t_boarding << " " << t_disembarking << "\n";
        t_boarding_avg+=t_boarding;
        t_disembarking_avg+=t_disembarking;
        t_boarding_acc.push_back(t_boarding);
        t_disembarking_acc.push_back(t_disembarking);
        t_boarding=t_disembarking=0;
    }
    t_boarding_avg/=NS;
    t_disembarking_avg/=NS;
    sort(t_boarding_acc.begin(),t_boarding_acc.end());
    sort(t_disembarking_acc.begin(),t_disembarking_acc.end());
    myfile << "Time AVG. = " << t_boarding_avg << " " << t_disembarking_avg << "\n";
    myfile << "Time 5% = " << t_boarding_acc[5*NS/100-1] << " " << t_disembarking_acc[5*NS/100-1] << "\n";
    myfile << "Time 95% = " << t_boarding_acc[95*NS/100-1] << " " << t_disembarking_acc[95*NS/100-1] << "\n";
    myfile << "Time boarding:\n";
    for(int i=0;i<t_boarding_acc.size();i++) myfile << t_boarding_acc[i] << "\n";
    myfile << "Time disembarking\n";
    for(int i=0;i<t_disembarking_acc.size();i++) myfile << t_disembarking_acc[i] << "\n";
    /*
    cout << "Time average = " << t_boarding_avg << " " << t_disembarking_avg << "\n";
    cout << "Time 5% = " << t_boarding_acc[5*NS/100-1] << " " << t_disembarking_acc[5*NS/100-1] << "\n";
    cout << "Time 95% = " << t_boarding_acc[95*NS/100-1] << " " << t_disembarking_acc[95*NS/100-1] << "\n";
    */
    myfile.close();
}
