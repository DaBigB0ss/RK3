#include <iostream>
#include <math.h>
#include <time.h>
#include <windows.h>
#include <iomanip>

using namespace std;

struct Creature
{
    double x,y;
};

double Function(Creature creature)
{
    return -1*sqrt(log(1+creature.x*creature.x+creature.y*creature.y));
}

void Mutation(Creature &creature)
{
    double d=0.025;
    if(rand()%10+1<=5)
    {
        if(rand()%10+1<=5)
            creature.x+=d;
        else
            creature.x-=d;
    }
    else
    {
        if(rand()%10+1<=5)
            creature.y+=d;
        else
            creature.y-=d;
    }
}

void Genetic(Creature *population)
{
    double P_nothit[4]={0,0,0,0},x_buf[3]={0,0,0},y_buf[3]={0,0,0},P_summary=0,random,maximum;
    int j_ignore=0,j_maximum=0,k=0;
    for(int j=0;j<4;j++)
    {
        P_summary+=Function(population[j]);
    }
    for(int j=0;j<4;j++)
    {
        P_nothit[j]=1-Function(population[j])/P_summary;
    }
    random=(rand()%int((P_nothit[0]+P_nothit[1]+P_nothit[2]+P_nothit[3])*10000))/10000.;
    j_ignore=0;
    for(int j=0;j<4;j++)
    {
        if(random<P_nothit[j])
        {
            j_ignore=j;
            break;
        }
        else
        {
            P_nothit[j+1]=P_nothit[j]+P_nothit[j+1];
        }
    }
    if(j_ignore!=0)
    {
        maximum=Function(population[0]);
        j_maximum=0;
    }
    else
    {
        maximum=Function(population[1]);
        j_maximum=1;
    }
    for(int j=0;j<4;j++)
    {
        if((j!=j_ignore)&&(Function(population[j])>maximum))
        {
            maximum=Function(population[j]);
            j_maximum=j;
        }
    }
    x_buf[0]=x_buf[1]=x_buf[2]=0;
    y_buf[0]=y_buf[1]=y_buf[2]=0;
    k=0;
    for(int j=0;j<4;j++)
    {
        if(j==j_maximum)
        {
            x_buf[0]=population[j].x;
            y_buf[0]=population[j].y;
        }
        else if(j!=j_ignore)
        {
            k++;
            x_buf[k]=population[j].x;
            y_buf[k]=population[j].y;
        }
    }
    population[0].x=x_buf[0];
    population[0].y=y_buf[1];
    population[1].x=x_buf[0];
    population[1].y=y_buf[2];
    population[2].x=x_buf[1];
    population[2].y=y_buf[0];
    population[3].x=x_buf[2];
    population[3].y=y_buf[0];
}

int main()
{
    srand(time(NULL));
    Creature population[4];
    double maximum=0;
    int mutationflag=0;
    cout << "-------------------" << endl;
    cout << fixed << setprecision(4) << "| Starting points |" << endl;
    cout << "-----------------------------------" << endl;
    for(int i=0;i<4;i++)
    {
        population[i].x=(rand()%20001-10000)/10000.;
        population[i].y=(rand()%20001-10000)/10000.;
        cout << "| " << i+1 << " | ";
        if(population[i].x>0)
            cout << " ";
        cout << population[i].x << " | ";
        if(population[i].y>0)
            cout << " ";
        cout << population[i].y << " | ";
        if(Function(population[i])>0)
                cout << " ";
            cout << Function(population[i]) << " | " << endl;
    }
    cout << "-----------------------------------" << endl << endl << endl;
    for(int i=0;i<20;i++)
    {
        Genetic(population);
        mutationflag=0;
        if(rand()%100+1<=25)
        {
            Mutation(population[rand()%4]);
            mutationflag=1;
        }
        else
        {
            mutationflag=0;
        }
        cout << "---------------------------" << endl;
        cout << "| Iteration - " << i+1;
        if(i<9)
            cout << " ";
        cout << "          |" << endl;
        if(mutationflag==1)
            cout << "| Mutation and Crossover  |" << endl;
        else
            cout << "| Crossover               |" << endl;
        cout << "-----------------------------------" << endl;
        for(int j=0;j<4;j++)
        {
            cout << "| " << j+1 << " | ";
            if(population[j].x>0)
                cout << " ";
            cout << population[j].x << " | ";
            if(population[j].y>0)
                cout << " ";
            cout << population[j].y << " | ";
            if(Function(population[j])>0)
                cout << " ";
            cout << Function(population[j]) << " | " << endl;
        }
        maximum=Function(population[0]);
        for(int j=0;j<4;j++)
        {
            if(maximum<Function(population[j]))
                maximum=Function(population[j]);
        }
        cout << "---------------------------------------------------------" << endl;
        cout << "| Average Function: " << (Function(population[0])+Function(population[1])+Function(population[2])+Function(population[3]))/4. << " | Maximum Function: " << maximum << " |" << endl;
        cout << "---------------------------------------------------------" << endl << endl;
    }
    return 0;
}
