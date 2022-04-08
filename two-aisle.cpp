#include<bits/stdc++.h>
#include "Sequence_Generator.h"
using namespace std;
const int N=50,M=50,NXM=350,NS=1000;
info p[NXM];
bool arr[N][M];
double t_boarding,t_disembarking,t_seat=4,t_walk=2,wait[NXM];
int nPeople=252,nRows=36,nCols,bin[M][10];
double t_boarding_avg,t_disembarking_avg;
vector<double> t_boarding_acc,t_disembarking_acc;
map<int,string> state;
map<char,int> side,c2i;
set<int> s;

void boarding(){
    while(!s.empty()){
        t_boarding++;
        for(int i=1;i<=nPeople;i++){
            //cout << s.size() << " " << i << " " << state[i] << " " << wait[i] << " " << p[i].pos << " " << p[i].posx << "\n";
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
        //cout << t_boarding << " " << s.size() << "\n";
    }
}
// reverse method
void disembarking(){
    set<int> out;
    vector<pair<int,int>> q[2];
    while(out.size()<nPeople){
        t_disembarking++;
        for(int check=0;check<3;check++){
            for(int i=1;i<=nPeople;i++){
                //if(out.size()==108) cout << t_disembarking << " " << out.size() << " " << i << " " << state[i] << " " << wait[i] << " " << p[i].pos << " " << p[i].posx << "\n";
                if(state[i]=="Seated"){
                    p[i].pos=p[i].seaty;
                    if(p[i].seatx=='A' and !arr[2][p[i].seaty]){
                        arr[1][p[i].seaty]=false;
                        arr[2][p[i].seaty]=true;
                        p[i].seatx='B';
                    }
                    else if(p[i].seatx=='B' and !arr[3][p[i].seaty]){
                        state[i]="Waiting";
                        arr[2][p[i].seaty]=false;
                        arr[3][p[i].seaty]=true;
                        p[i].seatx='X';
                        p[i].posx=3;
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='C' and !arr[3][p[i].seaty]){
                        state[i]="Waiting";
                        arr[4][p[i].seaty]=false;
                        arr[3][p[i].seaty]=true;
                        p[i].seatx='Y';
                        p[i].posx=3;
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='D' and !arr[6][p[i].seaty]){
                        arr[5][p[i].seaty]=false;
                        arr[6][p[i].seaty]=true;
                        p[i].seatx='E';
                    }
                    else if(p[i].seatx=='E' and !arr[7][p[i].seaty]){
                        state[i]="Waiting";
                        arr[6][p[i].seaty]=false;
                        arr[7][p[i].seaty]=true;
                        p[i].seatx='Z';
                        p[i].posx=7;
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='F' and !arr[7][p[i].seaty]){
                        state[i]="Waiting";
                        arr[8][p[i].seaty]=false;
                        arr[7][p[i].seaty]=true;
                        p[i].seatx='W';
                        p[i].posx=7;
                        wait[i]=t_seat;
                    }
                    else if(p[i].seatx=='G' and !arr[8][p[i].seaty]){
                        arr[9][p[i].seaty]=false;
                        arr[8][p[i].seaty]=true;
                        p[i].seatx='F';
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
                        q[p[i].ent=='F'?0:1].push_back({p[i].pos,i});
                    }
                }
            }
            else if(state[i]=="Storage"){
                wait[i]--;
                if(wait[i]==0){
                    bin[p[i].seaty][side[p[i].seatx]]-=p[i].luggage;
                    state[i]="In Aisle";
                    wait[i]=p[i].speed;
                    q[p[i].ent=='F'?0:1].push_back({p[i].pos,i});
                }
            }
        }
        sort(q[0].begin(),q[0].end());
        sort(q[1].begin(),q[1].end(),greater<pair<int,int>>());
        for(int k=0;k<2;k++){
            for(int j=0;j<q[k].size();j++){
                int i=q[k][j].second;
                //cout << t_disembarking << " " << out.size() << " " << i << " " << state[i] << " " << wait[i] << " " << p[i].pos << " " << p[i].posx << " " << bin[p[i].seaty][side[p[i].seatx]] << "\n";
                if(state[i]=="In Aisle"){
                    wait[i]--;
                    if(wait[i]==0){
                        if(!k){
                            if(p[i].pos==1){
                                if(!arr[p[i].posx-1][p[i].pos]){
                                    arr[p[i].posx][p[i].pos]=false;
                                    arr[--p[i].posx][p[i].pos]=true;
                                    wait[i]=p[i].speed;
                                }
                                else wait[i]=1;
                            }
                            else if(!arr[p[i].posx][p[i].pos-1]){
                                arr[p[i].posx][p[i].pos]=false;
                                arr[p[i].posx][--p[i].pos]=true;
                                q[k][j].first=p[i].pos;
                                wait[i]=p[i].speed;
                            }
                            else wait[i]=1;
                            if(p[i].pos==1 && p[i].posx==3){
                                state[i]="Not in Aisle";
                                p[i].pos=-1;
                                arr[3][1]=false;
                                out.insert(i);
                                q[k].erase(q[k].begin()+j);
                                continue;
                            }
                        }
                        else{
                            if(p[i].pos==nRows+2){
                                if(!arr[p[i].posx-1][p[i].pos]){
                                    arr[p[i].posx][p[i].pos]=false;
                                    arr[--p[i].posx][p[i].pos]=true;
                                    wait[i]=p[i].speed;
                                }
                                else wait[i]=1;
                            }
                            else if(!arr[p[i].posx][p[i].pos+1]){
                                arr[p[i].posx][p[i].pos]=false;
                                arr[p[i].posx][++p[i].pos]=true;
                                q[k][j].first=p[i].pos;
                                wait[i]=p[i].speed;
                            }
                            else wait[i]=1;
                            if(p[i].pos==nRows+2 && p[i].posx==3){
                                state[i]="Not in Aisle";
                                p[i].pos=-1;
                                arr[3][nRows+2]=false;
                                out.insert(i);
                                q[k].erase(q[k].begin()+j);
                                continue;
                            }
                        }
                    }
                }
            }
        }
        //cout << t_disembarking << " " << out.size() << "\n";
    }
}

int main(){
    ofstream myfile;
    myfile.open ("edited_two-aisle_.csv");
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
    //cin >> nPeople;
    p[0].pos=1e9;
    //for(int i=1;i<=nPeople;i++) cout << i << " " << p[i].pos << " " << p[i].seatx << " " << p[i].seaty << " " << p[i].luggage << " " << p[i].speed << "\n";
    for(int j=1;j<=NS;j++){
        if(j==NS) cout << "END!";
        else if(j%100==0) cout << "Simulation number: " << j << "\nKeep going. . .\n";
        fill_n(arr[0],N*M,false);
        fill_n(wait,NXM,0);
        fill_n(bin[0],M*10,0);
        //cout << "before rand\n";
        doubleaisle(p,nPeople,7,36,0,j);
        for(int i=1;i<=nPeople;i++){
            s.insert(i);
            state[i]="Not in Aisle";
            //cout << i << " " << p[i].pos << " " << p[i].seatx << " " << p[i].seaty << " " << p[i].luggage << " " << p[i].speed << " " << p[i].ent << "\n";
        }
        //cout << "board\n";
        boarding();
        disembarking();
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
