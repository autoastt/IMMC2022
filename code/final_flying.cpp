#include<bits/stdc++.h>
#include "Sequence_Generator.h"
using namespace std;
const int N=50,M=50,NXM=350,NS=1000;
info p[NXM];
bool arr[N][M];
double t_boarding,t_disembarking,t_seat=4,t_walk=2,wait[NXM];
int nPeople=318,nRows=15,bin[M][10];
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
                p[i].posx=4;
                break;
            }
            else if(state[i]=="In Aisle"){
                // at their seat
                if(p[i].pos==p[i].seaty){
                    state[i]="Storage";
                    // time step for storage
                    wait[i]=ceil((bin[p[i].seaty][side[p[i].seatx]]+p[i].luggage)*p[i].luggage*p[i].speed/2); 
                    // no luggage, just wait for seating
                    if(wait[i]==0){
                        state[i]="Waiting";
                        bin[p[i].seaty][side[p[i].seatx]]+=p[i].luggage;
                        // if there are people sit before
                        if(p[i].seatx=='A' and arr[2][p[i].seaty] and arr[3][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seatx=='A' and (arr[2][p[i].seaty] or arr[3][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='B' and arr[3][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='E' and arr[5][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='F' and arr[6][p[i].seaty] and arr[5][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='F' and (arr[6][p[i].seaty] or arr[5][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='H' and arr[10][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='G' and arr[9][p[i].seaty] and arr[10][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='G' and (arr[9][p[i].seaty] or arr[10][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='K' and arr[12][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='L' and arr[12][p[i].seaty] and arr[13][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='L' and (arr[12][p[i].seaty] or arr[13][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='N' and arr[17][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='M' and arr[16][p[i].seaty] and arr[17][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='M' and (arr[16][p[i].seaty] or arr[17][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='Q' and arr[19][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='R' and arr[19][p[i].seaty] and arr[20][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='R' and (arr[19][p[i].seaty] or arr[20][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='T' and arr[24][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='S' and arr[23][p[i].seaty] and arr[24][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='S' and (arr[23][p[i].seaty] or arr[24][p[i].seaty])){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='W' and arr[26][p[i].seaty]){
                            wait[i]=floor(0.5+3*t_seat); continue; }
                        else if(p[i].seatx=='X' and arr[26][p[i].seaty] and arr[27][p[i].seaty]){
                            wait[i]=floor(0.5+5*t_seat); continue; }
                        else if(p[i].seaty=='X' and (arr[26][p[i].seaty] or arr[27][p[i].seaty])){
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
                    if(p[i].posx==25 && p[i].seatx>='S'){
                        // there is space in front of them
                        if(!arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                        continue;
                    }
                    else if(p[i].posx==18 && p[i].seatx>='M'){
                        if(!arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                        continue;
                    }
                    else if(p[i].posx==11 && p[i].seatx>='G'){
                        if(!arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
                            wait[i]=p[i].speed;
                        }
                        else wait[i]=1;
                        continue;
                    }
                    else if(p[i].posx==4){
                        if(!arr[p[i].posx][p[i].pos+1]){
                            arr[p[i].posx][p[i].pos]=false;
                            arr[p[i].posx][++p[i].pos]=true;
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
                    if(p[i].seatx=='A' and arr[2][p[i].seaty] and arr[3][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seatx=='A' and (arr[2][p[i].seaty] or arr[3][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='B' and arr[3][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='E' and arr[5][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='F' and arr[6][p[i].seaty] and arr[5][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='F' and (arr[6][p[i].seaty] or arr[5][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='H' and arr[10][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='G' and arr[9][p[i].seaty] and arr[10][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='G' and (arr[9][p[i].seaty] or arr[10][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='K' and arr[12][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='L' and arr[12][p[i].seaty] and arr[13][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='L' and (arr[12][p[i].seaty] or arr[13][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='N' and arr[17][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='M' and arr[16][p[i].seaty] and arr[17][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='M' and (arr[16][p[i].seaty] or arr[17][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='Q' and arr[19][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='R' and arr[19][p[i].seaty] and arr[20][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='R' and (arr[19][p[i].seaty] or arr[20][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='T' and arr[24][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='S' and arr[23][p[i].seaty] and arr[24][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='S' and (arr[23][p[i].seaty] or arr[24][p[i].seaty])){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='W' and arr[26][p[i].seaty]){
                        wait[i]=floor(0.5+3*t_seat); continue; }
                    else if(p[i].seatx=='X' and arr[26][p[i].seaty] and arr[27][p[i].seaty]){
                        wait[i]=floor(0.5+5*t_seat); continue; }
                    else if(p[i].seaty=='X' and (arr[26][p[i].seaty] or arr[27][p[i].seaty])){
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
    myfile.open("data.csv");
    int temp=1;
    for(int i='A';i<='X';i++){
        side[i]=temp;
        if((i-'A'+1)%3==0) temp++;
    }
    for(int i='A';i<='X';i++){
        c2i[char(i)]=i-'A'+1;
        if(i=='C' || i=='I' || i=='O' || i=='U') i++;
    }
    p[0].pos=1e9;
    for(int j=1;j<=NS;j++){
        fill_n(arr[0],N*M,false);
        fill_n(wait,NXM,0);
        fill_n(bin[0],M*10,0);
        // from sequene generator
        flying_wing(p,0,j);
        // initialize the passengers
        for(int i=1;i<=nPeople;i++){
            s.insert(i);
            state[i]="Not in Aisle";
            p[i].pos=0;
        }
        boarding();
        t_boarding_avg+=t_boarding;
        t_boarding_acc.push_back(t_boarding);
        t_boarding=0;
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
