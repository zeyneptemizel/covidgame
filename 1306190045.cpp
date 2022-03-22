//ZEYNEP TEMİZEL 1306190045
//Codeblocks ile hazırlanmıstır.
#include <iostream>
#include <vector>
#include <cstring>
#include <fstream>
#include <cctype>
#include <sstream>

using namespace std;
vector <string> lines;
vector <char> genn;
vector <int> positioning;
vector <string> infectedEntites;


void getInfo (){
ifstream read;
read.open("INPUT.txt");
string full;
while (!read.eof()){

    getline(read, full);
    lines.push_back(full);
}
read.close();
}


// x y kordinat
struct Position{
    int X = 0;
    int Y = 0;
};
// entity
class Entity{
    public:
    Position position;
    bool bulastirma =false;
    bool borninfected = false;
    bool bornimmune = false;
    bool nearEnemy =false;             //3x3 alanda infected varsa true olacak.
    bool infected =false  ;            //
    bool immune = false   ;             // entity de A ve B yoksa true olcak
    bool dead=false ;                   // when die becomes true
    bool removed=false;                 //after 5 turns of dying becomes true
    int deathTurns = 0;           // dead true olunca 5 tur sayacak ve 5 günün sonunda infected false olacak ve removed true olacak.
    int infectedTurns = 0;        //  nearenemy true olunca 3 tur sayacak ve infected true olacak
    int nearEnemyTurns =0;
    vector <Position> turns;
    string gene0;
    string gene1;
    string gene2;
    string gene3;
    string gene4;
    vector <string> ALLGENES;
    vector <Position> allturns;
    bool yeniEnfekte =false;
    bool sonradanInfect = false;


};

// entitiler bu liste içine eklenecek
vector <Entity> entities;


vector<string> parse(string str, string delimiter){
size_t pos = 0;

    vector <string> stringVector;
    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);
        stringVector.push_back(token);
        str.erase(0, pos + delimiter.length());
    }
    stringVector.push_back(str);


    return stringVector;

}



Position getPostition(string str, string delimiter){

    int countt = 0;
    Position position;
    size_t pos = 0;

    string token;
    while ((pos = str.find(delimiter)) != string::npos) {
        token = str.substr(0, pos);


            position.X = stoi(token);
            countt += 1;




        str.erase(0, pos + delimiter.length());
    }

    position.Y = stoi(str);




    return position;

}

int main()
{
                                  // Burda inputtan size ve turn countu çekiyor.
     getInfo();
     size_t i = 0;

        string arraySizeLine=lines[0];
        for ( ; i < arraySizeLine.length(); i++ ){ if ( isdigit(arraySizeLine[i]) ) break; }
        arraySizeLine = arraySizeLine.substr(i, arraySizeLine.length() - i );
        int arraySize = atoi(arraySizeLine.c_str());


        string turnCountLine=lines[1];

        for ( ; i < turnCountLine.length(); i++ ){ if ( isdigit(turnCountLine[i]) ) break; }
        turnCountLine = turnCountLine.substr(i, turnCountLine.length() - i );
        int turnCount = atoi(turnCountLine.c_str());

        int size =arraySize;


int entityCount=0;                            //burda inputtan kaç tane entitiy olduðu bilgisini çeker.
for (int i =0; i<lines.size(); i++)
{
    if(lines[i].find("entity") == 0){

        entityCount++;

    }
}



for(int i=2;i<entityCount+2;i++){         //In this loop, we take the genes
    int temp=lines[i].size();
    for(int j=0;j<temp;j++){
            if (isupper(lines[i][j])){
           genn.push_back(lines[i][j]);


            }

    }


    int xnerde = lines[i].find("x");           // in this loop we take starting locations.
    string tempX= "";
    string tempY= "";
    int itempX;
    int itempY;
    for(int c=4; c>0; c--){
            if(isdigit(lines[i][xnerde-c]))
                {

            tempX += lines[i][xnerde-c];
            }
    }

    for(int o=1;o<5;o++){

        if(isdigit(lines[i][xnerde+o])){

           tempY+= lines[i][xnerde+o];

           }
           }

           istringstream(tempX) >> itempX;
           istringstream(tempY) >> itempY;
            positioning.push_back(itempX);
           positioning.push_back(itempY);

}


        for (int k = 0; k< entityCount; k++){    //in this loop, we create the entites

        Entity entity;
        entity.gene0=genn[0];
        entity.gene1=genn[1];
        entity.gene2=genn[2];
        entity.gene3=genn[3];
        entity.gene4=genn[4];

        entity.ALLGENES.push_back(entity.gene0);
        entity.ALLGENES.push_back(entity.gene1);
        entity.ALLGENES.push_back(entity.gene2);
        entity.ALLGENES.push_back(entity.gene3);
        entity.ALLGENES.push_back(entity.gene4);


        genn.erase(genn.begin());
        genn.erase(genn.begin());
        genn.erase(genn.begin());
        genn.erase(genn.begin());
        genn.erase(genn.begin());



        if(entity.gene0 != "A" && entity.gene0 != "B" && entity.gene1 != "A" && entity.gene1 != "B" && entity.gene2 != "A" && entity.gene2 != "B" && entity.gene3 != "A" && entity.gene3 != "B" && entity.gene4 !=  "A" && entity.gene4 != "B")

        { entity.immune = true;
        entity.bornimmune =true;}                                            // checks if entity starts as immune.


        entity.position.X = positioning[0];           //starting positions
        entity.position.Y = positioning[1];
        positioning.erase(positioning.begin());
        positioning.erase(positioning.begin());


        if(lines[k+2][lines[k+2].size() - 1 ]=='d'){

        entity.infectedTurns=0;
        entity.borninfected =true;




        }  // checks if entity starts as infected.

entities.push_back(entity);

    }

////////////////////////////////////////////////////


    for(int ii=entityCount+2; ii<entityCount+2+turnCount+1; ii++){
    //linları almak için

    vector <string> parsedLine = parse(lines[ii]," ");

    // (jj - 2) -> pared position's entitiy
    for (int jj = 0; jj < parsedLine.size(); jj++){

        if (jj >= 2){ // okunan line doğru olsun diye

            Position pos = getPostition(parsedLine[jj],"x");

            entities[jj-2].allturns.push_back(pos);


        }

   }
}


int deadOnes = 0;
int normalOnes = 0;
int recoveredOnes= 0;
int infectedOnes = 0;
ofstream writeturns;
writeturns.open("TURNS.txt");

ofstream writeoutputs;
writeoutputs.open("OUTPUT.txt");


for(int i=0;i<3;i++){


}
///////////////////////////////////////////////////////////////////////////////////////////////////////
    //turnleri yapalým
    for (int j = 0; j< turnCount; j++){
            writeturns <<"Turn "<< j+1<<":"<<endl; ;






        for (int inE = 0; inE < entities.size(); inE++){

                if (entities[inE].sonradanInfect){
                     if(entities[inE].infectedTurns >=4){

                        entities[inE].bulastirma=true;

                    }
                } else {
                    if(entities[inE].infectedTurns >=3){

                        entities[inE].bulastirma=true;

                    }
                }



        }
        // ölünün gününü sayalım

        for (int inE = 0; inE < entities.size(); inE++){
           if (entities[inE].dead  ){


                entities[inE].deathTurns += 1;

           }
        }

        vector<string> ALL_BAD_GATES = { "A","B","C","D" };

        // 14 gün hastalğı kapan biri genlerininde A B C D varsa ÖLÜRRRRR
        for (int inE = 0; inE < entities.size(); inE++){
        if ((entities[inE].infectedTurns > 14 && entities[inE].borninfected == false) || (entities[inE].borninfected ==true  && entities[inE].infectedTurns >13)){

                int gen_sayac = 0; // 3 olursa ölür
                for (int ge = 0; ge < ALL_BAD_GATES.size(); ge++ ){

                    for  (int eg = 0; eg < entities[inE].ALLGENES.size(); eg++ ){
                        if ( entities[inE].ALLGENES[eg] == ALL_BAD_GATES[ge] ) {
                            gen_sayac += 1;

                        }
                    }
                }


                if (gen_sayac >= 3){

                    entities[inE].dead = true;
                } else {
                     if (entities[inE].infectedTurns > 31 && entities[inE].borninfected == false){
                        entities[inE].immune = true;

                         entities[inE].infected = false;
                     }
                     else if (entities[inE].infectedTurns >31 && entities[inE].borninfected ==true){

                        entities[inE].immune =true;
                        entities[inE].infected =false;

                     }

                }

           }
        }
       // ölenler 5 gün sonra silinir
        for (int inE = 0; inE < entities.size(); inE++){
           if (entities[inE].deathTurns >= 5){

                entities[inE].removed = true;
           }
        }

        // enfekte etme kodu
        for (int inE = 0; inE < entities.size(); inE++){



            for (int karsiE = 0; karsiE < entities.size(); karsiE++){

                    // ölüyse enfekte etme
                    if (!entities[karsiE].immune){
                    if (!entities[inE].immune){
                    if (entities[karsiE].removed){
                        continue;
                    }

                int x = entities[inE].position.X;
                int y = entities[inE].position.Y;

               int kx = entities[karsiE].position.X;
               int ky = entities[karsiE].position.Y;

               if ((kx -3 <= x && x <= kx +3) && (ky -3 <= y && y <= ky +3)){

                    if (entities[karsiE].bulastirma ==true ){

                           if (entities[inE].infectedTurns  == 0){

                                entities[inE].infectedTurns  = 1;
                                entities[inE].yeniEnfekte  = true;
                                entities[inE].sonradanInfect  = true;
                            }
                    }


               }


            }
            }
            }
        }






         //  hastalandığı günlerini sayalım. not: 3 günden uzun süreyse bulaştırır
        for (int inE = 0; inE < entities.size(); inE++){
           if ((entities[inE].infectedTurns != 0 || entities[inE].borninfected )&& entities[inE].yeniEnfekte == false){
            entities[inE].infectedTurns += 1;
           }
        }


        for (int inE = 0; inE < entities.size(); inE++){
           entities[inE].yeniEnfekte = false;
        }



        /* yazdır */

        for(int t = 0; t< size+1; t++){
            writeturns<<"-";

        }


        for(int e=0; e< entities.size(); e++){


                 if(entities[e].removed) {
                    continue;
                }

                if(entities[e].dead) {
                    continue;
                }

            entities[e].position.X = entities[e].allturns[j].X;
            entities[e].position.Y = entities[e].allturns[j].Y;




        }

        for(int x = 1; x< size+2; x++){writeturns << "-";

            for(int y = 1; y< size+1 ; y++){

                bool bulundu = false;

                for(int e=0; e< entities.size(); e++){


                    if(entities[e].position.X == x-1 && entities[e].position.Y == y){
                        if(entities[e].removed==1){writeturns << " ";}
                        else if(entities[e].dead==1){writeturns << 'D';}
                        else if((entities[e].infectedTurns>=1 || entities[e].infected) && entities[e].immune == 0 ){writeturns << 'X';}


                        else {writeturns << 'O';}
                        bulundu = true;
                        continue;

                    }

                }

                if(!bulundu){
if(x!=1) writeturns<<" ";
                }


            }          if(x!=1)   writeturns << "-";

            writeturns<<"\n";


        }


        for(int t = 0; t< size+2; t++){
            writeturns<<"-";
        }
        writeturns<<"\n";



    }


        for (int inE = 0; inE < entities.size(); inE++){
           if (entities[inE].dead  ){
                deadOnes += 1;
           }
        }

        for (int inE = 0; inE < entities.size(); inE++){
           if (entities[inE].immune  ){
                if (entities[inE].infectedTurns  >= 30  ){
                    recoveredOnes += 1;
                }
           }
        }

        // infected turns 14 - 1 arasında olacak ve inmune olmayan
        for (int inE = 0; inE < entities.size(); inE++){
           if (entities[inE].immune == false && entities[inE].dead ==false ){
                if (entities[inE].infectedTurns >0  ){
                    infectedOnes += 1;
                }
           }
        }

        // normal olanlar
        normalOnes = entityCount - infectedOnes -recoveredOnes - deadOnes;

////////////////////////////////////////////////////////////////////////////////////////////////

writeoutputs<<"Normal     : " << normalOnes<< endl;
writeoutputs<<"Infected   : " << infectedOnes<< endl;
writeoutputs<<"Dead       : " << deadOnes << endl;
writeoutputs<<"Recovered  : " << recoveredOnes << endl;


for (int z = 1 ; z < entityCount +1; z++){

    writeoutputs<<"entity " << z <<" " << entities[z-1].position.X << "x" << entities[z-1].position.Y << " ";
    if (entities[z-1].dead ==1) writeoutputs<< "dead" << endl;

    else if(entities[z-1].immune ==1 && entities[z-1].bornimmune==false) writeoutputs<< "immune" << endl;
    else if (entities[z-1].infectedTurns  >1 && entities[z-1].immune ==false && entities[z-1].dead ==false) writeoutputs << "infected" <<endl;
    else if(entities[z-1].bornimmune ==1) {writeoutputs << "normal" << endl;}
    else writeoutputs << "normal" << endl;


}

writeoutputs.close();
writeturns.close();

}

