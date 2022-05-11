#include<bits/stdc++.h>
#include "Sequence_Generator.h"
using namespace std;
const int N=50,M=50,NXM=350,NS=1000;
info p[NXM];
bool arr[N][M];
double t_boarding,t_disembarking,t_seat=4,t_walk=2,wait[NXM];
int nPeople=252,nRows=36,bin[M][10];
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
                int pos;
                if(p[i].ent=='F') pos=1;
                else pos=nRows+2;
                if(arr[3][pos]) continue;;
                state[i]="In Aisle";
                arr[3][pos]=true;
                wait[i]=p[i].speed;
                p[i].pos=pos;
                p[i].posx=3;
                break;
            }
            else if(state[i]=="In Aisle"){
                // at their seat
                if(p[i].pos==p[i].seaty){
                    state[i]="Storage";
                    wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2); // time step for storage
                    // no luggage, just wait for seating
                    if(wait[i]==0){
                        state[i]="Waiting";
                        bin[p[i].seaty][side[p[i].seatx]]+=p[i].luggage;
                        // if there are people sit before
                        if(p[i].seatx=='A' and arr[2][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='G' and arr[8][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='D' and arr[6][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        state[i]="Seated";
                        arr[p[i].posx][p[i].seaty]=false;
                        arr[c2i[p[i].seatx]][p[i].seaty]=true;
                        p[i].pos=p[i].posx=-1;
                        s.erase(i);
                    }
                    continue;
                }
                wait[i]--;
                if(wait[i]==0){
                    // check if it is the correct column or not
                    if(p[i].posx==3 && p[i].seatx<='C'){
                        // there is space in front of them
                        if(p[i].ent=='F' && !arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else if(p[i].ent=='B' && !arr[p[i].posx][p[i].pos-1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][--p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                        continue;
                    }
                    else if(p[i].posx==7 && p[i].seatx>'C'){
                        if(p[i].ent=='F' && !arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else if(p[i].ent=='B' && !arr[p[i].posx][p[i].pos-1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][--p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                        continue;
                    }
                    if(!arr[p[i].posx+1][p[i].pos]){
                        arr[p[i].posx][p[i].pos]=false;
                        arr[++p[i].posx][p[i].pos]=true;
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
                    if(p[i].seatx=='A' and arr[2][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='G' and arr[8][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='D' and arr[6][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    state[i]="Seated";
                    arr[p[i].posx][p[i].seaty]=false;
                    arr[c2i[p[i].seatx]][p[i].seaty]=true;
                    p[i].pos=p[i].posx=-1;
                    s.erase(i);
                }
            }
            else if(state[i]=="Waiting"){
                wait[i]--;
                if(wait[i]==0){
                    state[i]="Seated";
                    arr[p[i].posx][p[i].seaty]=false;
                    arr[c2i[p[i].seatx]][p[i].seaty]=true;
                    p[i].pos=p[i].posx=-1;
                    s.erase(i);
                }
            }
            else if(state[i]=="Seated") continue;
        }
    }
}

int main(){
    // file for collecting the data
    ofstream myfile;
    myfile.open ("data.csv");
    side['A']=side['B']=side['X']=1;
    side['C']=side['Y']=2;
    side['D']=side['E']=side['Z']=3;
    side['F']=side['G']=side['W']=4;
    c2i['A']=1;
    c2i['B']=2;
    c2i['C']=4;
    c2i['D']=5;
    c2i['E']=6;
    c2i['F']=8;
    c2i['G']=9;
    p[0].pos=1e9;
    for(int j=1;j<=NS;j++){
        if(j==NS) cout << "END!";
        else if(j%100==0) cout << "Simulation number: " << j << "\nKeep going. . .\n";
        fill_n(arr[0],N*M,false);
        fill_n(wait,NXM,0);
        fill_n(bin[0],M*10,0);
        // from sequence generator
        doubleaisle(p,nPeople,7,36,60,j);
        // initialize the passengers
        for(int i=1;i<=nPeople;i++){
            s.insert(i);
            state[i]="Not in Aisle";
        }
        boarding();
        t_boarding_avg+=t_boarding;
        t_boarding_acc.push_back(t_boarding);
        t_boarding=t_disembarking=0;
    }
    t_boarding_avg/=NS;
    sort(t_boarding_acc.begin(),t_boarding_acc.end());
    myfile << "Time AVG. = " << t_boarding_avg << "\n";
    myfile << "Time 5% = " << t_boarding_acc[5*NS/100-1] << "\n";
    myfile << "Time 95% = " << t_boarding_acc[95*NS/100-1] << "\n";
    myfile << "Time boarding:\n";
    for(int i=0;i<t_boarding_acc.size();i++) myfile << t_boarding_acc[i] << "\n";
    myfile.close();
}
