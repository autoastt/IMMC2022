#include<bits/stdc++.h>
#include "Sequence_Generator.h"
using namespace std;
const int N=50,M=50,NXM=350,NS=1000;
info p[NXM];
bool arr[N][M];
double t_boarding,t_disembarking,t_seat=4,t_walk=2,wait[NXM];
int nPeople=198,nRows=33,bin[M][2];
double t_boarding_avg,t_disembarking_avg;
vector<double> t_boarding_acc,t_disembarking_acc;
map<int,string> state;
map<char,int> side,c2i;
set<int> s;

void boarding(){
    while(!s.empty()){
        t_boarding++;
        for(int i=1;i<=nPeople;i++){
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
                    // time step for storage
                    wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2);
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
    }
}

vector<pair<int,int>> a[3];

void re_wilma(){
    for(int k=0;k<3;k++){
        sort(a[k].begin(),a[k].end());
        while(!a[k].empty()){
            t_disembarking++;
            for(int j=0;j<a[k].size();j++){
                int i=a[k][j].second;
                if(state[i]=="Seated"){
                    p[i].pos=p[i].seaty;
                    if(!arr[4][p[i].seaty]){
                        arr[c2i[p[i].seatx]][p[i].seaty]=false;
                        arr[4][p[i].seaty]=true;
                        if(p[i].seatx<='C') p[i].seatx='X';
                        else p[i].seatx='Y';
                        wait[i]=t_seat;
                        state[i]="Waiting";
                    }
                }
                else if(state[i]=="Waiting"){
                    wait[i]--;
                    if(wait[i]==0){
                        state[i]="Storage";
                        // time step for storage
                        wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2);
                        if(wait[i]==0){
                            bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                            state[i]="In Aisle";
                            wait[i]=p[i].speed;
                        }
                    }
                }
                else if(state[i]=="Storage"){
                    wait[i]--;
                    if(wait[i]==0){
                        bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                        state[i]="In Aisle";
                        wait[i]=p[i].speed;
                    }
                }
                else if(state[i]=="In Aisle"){
                    wait[i]--;
                    if(wait[i]==0){
                        // there is space in front of them
                        if(!arr[4][p[i].pos-1]){
                            arr[4][p[i].pos]=false;
                            arr[4][--p[i].pos]=true;
                            a[k][j].first=p[i].pos;
                            if(p[i].pos==0){
                                state[i]="Not in Aisle";
                                p[i].pos=-1;
                                arr[4][0]=false;
                                a[k].erase(a[k].begin()+j);
                                continue;
                            }
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                    }
                }
            }
        }
    }

}

int dis[NXM],tt[NXM];
struct G{
    int d,t,i,p;
    bool operator<(const G&o)const{
        if(d==o.d) return t<o.t;
        return d<o.d;
    }
};
bool cmpp(G a,G b){
    return a.p<b.p;
}
void greedy(){
    set<int> out;
    vector<G> q;
    for(int i=1;i<=nPeople;i++){
        dis[i]=abs(4-c2i[p[i].seatx])+p[i].seaty;
        tt[i]=t_seat+ceil(p[i].luggage*p[i].luggage*p[i].speed/2);
        p[i].pos=p[i].seaty;
        q.push_back({dis[i],tt[i],i,p[i].pos});
    }
    while(out.size()<nPeople){
        t_disembarking++;
        sort(q.begin(),q.end());
        for(int j=0;j<q.size();j++){
            int i=q[j].i;
            if(state[i]=="Seated"){
                if(arr[4][p[i].seaty]) continue;
                arr[c2i[p[i].seatx]][p[i].seaty]=false;
                arr[4][p[i].seaty]=true;
                if(p[i].seatx<='C') p[i].seatx='X';
                else p[i].seatx='Y';
                wait[i]=t_seat;
                state[i]="Waiting";
            }
        }
        sort(q.begin(),q.end(),cmpp);
        for(int j=0;j<q.size();j++){
            int i=q[j].i;
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
                    }
                }
            }
            else if(state[i]=="Storage"){
                wait[i]--;
                if(wait[i]==0){
                    bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                    state[i]="In Aisle";
                    wait[i]=p[i].speed;
                }
            }
            else if(state[i]=="In Aisle"){
                wait[i]--;
                if(wait[i]==0){
                    // there is space in front of them
                    if(!arr[4][p[i].pos-1]){
                        arr[4][p[i].pos]=false;
                        arr[4][--p[i].pos]=true;
                        q[j].p=p[i].pos;
                        if(p[i].pos==0){
                            state[i]="Not in Aisle";
                            p[i].pos=-1;
                            arr[4][0]=false;
                            q.erase(q.begin()+j);
                            out.insert(i);
                            continue;
                        }
                        wait[i]=p[i].speed;
                    }
                    else wait[i]=1;
                }
            }
        }
    }
}

int main(){
    // file for collecting the data
    ofstream myfile;
    myfile.open("data.csv");
    side['A']=side['B']=side['C']=side['X']=0;
    side['D']=side['E']=side['F']=side['Y']=1;
    c2i['A']=1;
    c2i['B']=2;
    c2i['C']=3;
    c2i['D']=5;
    c2i['E']=6;
    c2i['F']=7;
    p[0].pos=1e9;
    for(int j=1;j<=NS;j++){
        fill_n(arr[0],N*M,false);
        fill_n(wait,NXM,0);
        fill_n(bin[0],M*2,0);
        // choose boarding method from sequence generator
        /*
        random(p,nPeople,6,j);
        seat(p,nPeople,6,0,j);
        section(p,nPeople,6,0,j,1);
        repyramid(p,60,j);
        seatsection(p,nPeople,6,20,j);
        */
        // initialize the passengers
        for(int i=1;i<=nPeople;i++){
            s.insert(i);
            state[i]="Not in Aisle";
            p[i].pos=0;
            if(p[i].seatx=='C' || p[i].seatx=='D') a[0].push_back({p[i].pos,i});
            else if(p[i].seatx=='B' || p[i].seatx=='E') a[1].push_back({p[i].pos,i});
            else a[2].push_back({p[i].pos,i});
        }
        boarding();
        // choose disembarking method
        /*
        re_wilma();
        greedy();
        */
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
    myfile.close();
}
