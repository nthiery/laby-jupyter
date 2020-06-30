#include "include/laby/global_fr.hpp"

//To know if we wear a rock.
bool contient=false;

//Count the number of rock the ant can see without take it.
int cptrock=0;
bool rockbf=false;

//Count the number of web the ant can see without erase it
int cptnet=0;
bool netbf=false;

/**Count the ant's shift for set the rock. 
   Start at 1 cause we beggin with one shift in left before use the function SetRock().
*/
int setrock=1;

//To avoid the problem 'function undefine'.
void BackTracking(bool rck, bool wallL);

/**Show steps on the board and forward. 
   (NB: if we unactivate the steps widget, they still showed but only void case xD).
*/
void Step(){
    trace();
    avance();
}

//Move the ant in 180 degree.
void Gauche2(){
    gauche();
    gauche();
}

//To know if the ant can set the rock.
bool TestWall(){
    return regarde()==Tile::Wall;
}

//Rotate the ant while he see nothing to set the rock.
void SetRock(int &cpt,bool back){
    if(back){
        while(cpt!=0){
            droite();
            cpt--;
        }
        cpt=1;
    }
    else{
        while(TestWall()){
            gauche();
            cpt++;
        }
    }
}

//Open the door and finish the Labyrinth. Plus, set the rock if the ant wear one.
void EndLaby(){
    if(contient){
        gauche();
        SetRock(setrock,false);
        pose();
        contient=false;
        SetRock(setrock,true);
        trace();
        ouvre();
    }
    else{trace();ouvre();}
}

//Keep position of a rock.
void PosCaillou(){
    cptrock++;
    rockbf=true;
}

//keep position of a web.
void PosToile(){
    cptnet++;
    netbf=true;
}

//Let the ant wear a rock (if able).
void TakeRock(){
    if(contient==false){
        prend();
        contient=true;
        if(netbf){
            Gauche2();
            BackTracking(true,true);
        }
    }
    else{PosCaillou();
        gauche();
        SetRock(setrock,false);
        pose();
        SetRock(setrock,true);
        prend();}
}

//Let the ant set a rock on a web (if able).
void BreakNet(){
    if(contient){
        pose();
        cptnet--;
        if(cptnet==0){netbf=false;}
        contient=false;
        /*if(rockbf){
            Gauche2();
            BackTracking(false,true);
        }*/
    }
    else{
        PosToile();
        gauche();
    }
}

//Let the ant find a wall when the game start.
void SearchWall(){
    bool test=true;
    while(test){
        switch(regarde()){            
            case Tile::Wall : gauche(); test=false; break;
            case Tile::Rock : TakeRock(); break;
            case Tile::Web : BreakNet(); break;
            case Tile::Void : Step(); break;
            case Tile::SmallRock : Step(); break;
            case Tile::SmallWeb : Step(); break;       
            case Tile::Exit : EndLaby(); test=false; break;
            default: break;
        }
    }
}

//Check if the ant get a wall on the right (or the left if wall_left is True).
bool WallRight(bool rck, bool wall_left){
    switch(regarde()){
        case Tile::Rock : TakeRock();
                          if(wall_left){
                              if(rck){
                                  cptrock--;
                                  if(cptrock==0){rockbf=false; break;} 
                                  Gauche2(); return false; break;
                              }
                          }
                          else{return true; break;}
            
        case Tile::Web : BreakNet(); 
                         if(wall_left){
                             if(rck==false){
                                 cptrock--;
                                 if(cptrock==0){rockbf=false; break;} 
                                 Gauche2(); return false; break;
                             }
                         }
                         else{return true; break;}
            
        case Tile::Exit : EndLaby(); return false; break;
            
        case Tile::Void : return true; break;
            
        case Tile::Wall : if(wall_left){droite();}
                          else{gauche();} 
                          return true; break;
            
        case Tile::SmallRock : return true; break;
            
        case Tile::SmallWeb : return true; break;
            
        case Tile::FootN : if(direction()==Direction::North){Gauche2();return true; break;}else{return true; break;}
            
        case Tile::FootS : if(direction()==Direction::South){Gauche2();return true; break;}else{return true; break;}
            
        case Tile::FootE : if(direction()==Direction::East){Gauche2();return true; break;}else{return true; break;}
            
        case Tile::FootW : if(direction()==Direction::West){Gauche2();return true; break;}else{return true; break;}
            
        default : return false; 
    }
    return false;
}

//Let the ant do his backtracking.
void BackTracking(bool rck,bool wallL){
    while(WallRight(rck,wallL)){
        if(WallRight(rck,wallL)){
            Step();
            gauche();
        }
    }
}

//The Main Code!
void Walk(){
    SearchWall();
    droite();
    while(WallRight(false,false)){
        if(WallRight(false,false)){
            Step();
            droite();
        }
        else{return 0;}
    }
}
