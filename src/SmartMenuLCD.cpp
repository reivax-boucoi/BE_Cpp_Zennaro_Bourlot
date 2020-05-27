#include "SmartMenuLCD.h"

extern LCD myLcd;

/*********** Constructeurs/methodes de la classe Screen *************/

//Constructeur d'objets de type Screen
Screen::Screen(ScreenObject*firstobj,string nom){
   objects.push_back(firstobj);                 //ajout d'un premier texte/d'une premire valeur a afficher
    currentObject=0;
    nbobjects++;
    name=nom;
}

//Methode pour ajouter un nouvel element (Texte/valeur) a afficher
void Screen::addObject(ScreenObject*newObj){
    objects.push_back(newObj);
    nbobjects++;
}

//Assesseur permettant de recuperer le nom de l'ecran affiche
string Screen::getName(){
    return name;
}

//Methode permettant de selectionner le prochain objet editable affiche sur l'ecran
void Screen::Next(){
    unsigned int i;
   
        if(prevx!=-1 && prevy !=-1 && prev_obj!=currentObject) {
            myLcd.setCursor(prevx,prevy);
            myLcd.print(" ");      
        } else {
            myLcd.setCursor(prevx,prevy);
            myLcd.print(">"); 
            }  

    if(not(editing)) {
         
        if(currentObject>=nbobjects-1) currentObject--;
        prev_obj=currentObject;
        for(i=currentObject+1;i<nbobjects;i++){
            if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
                currentObject=i;
                //myLcd.clear();
                myLcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
                prevx=objects[i]->getx()-1;
                 prevy=objects[i]->gety();
                myLcd.print(">");
                break;
            }
        }
            
    } else {
        if(typeid(*objects[currentObject])==typeid(EditableValue)){
            ((EditableValue*)objects[currentObject])->increment();
        }else{  //it is an EditableText
            ((EditableText*)objects[currentObject])->next();

        }
        //prev_obj=currentObject;
        //prevx=objects[currentObject]->getx()-1;
        //prevy=objects[currentObject]->gety();
    }  
    display();
}

//Methode permettant de selectionner l'objet editable precedent affiche sur l'ecran
void Screen::Prev(){
    int i;
    
      if(prevx!=-1 && prevy !=-1 && prev_obj!=currentObject) {
            myLcd.setCursor(prevx,prevy);
            myLcd.print(" ");      
        } else {
            myLcd.setCursor(prevx,prevy);
            myLcd.print(">"); 
            }      

    if(not(editing)) {
     
        if(currentObject<=0) currentObject=1;
        prev_obj=currentObject;
        for(i=currentObject-1;i>=0;i--){
             if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
                 currentObject=i;
                // myLcd.clear();
                 myLcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
                 prevx=objects[i]->getx()-1;
                 prevy=objects[i]->gety();
                 myLcd.print(">");
                // this->display();
                 break;
             }
        }
    } else {
        if(typeid(*objects[currentObject])==typeid(EditableValue)){
            ((EditableValue*)objects[currentObject])->decrement();
        }else{  //it is an EditableText
            ((EditableText*)objects[currentObject])->prev();
            
        }
       // prev_obj=currentObject;
        //prevx=objects[currentObject]->getx()-1;
        //prevy=objects[currentObject]->gety();
    } 
    display(); 
}

//Methode permettant d'afficher tous les textes/valeurs de l'ecran courant
void Screen::display(){
     vector<ScreenObject*>::iterator itso;
    for(itso=objects.begin();itso!=objects.end();itso++){
            (*itso)->display();
    }
    if(editing) objects[currentObject]->display();//last to be displayed to keep last cursor pos
}

void Screen::enter(){
    if(typeid(*objects[currentObject])==typeid(EditableValue) || typeid(*objects[currentObject])==typeid(EditableText)){
        editing=true;
         if(typeid(*objects[currentObject])==typeid(EditableValue))((EditableValue*)objects[currentObject])->advanceCursor();
    }
   display();
}

void Screen::back(){
    editing=false;
    currentObject=0;
    display();
}
/*********** Constructeurs/methodes de la classe Menu *************/


//constructeur initialisant un objet de type Screen donne pour l'ajouter au Menu principal
Menu::Menu(Screen *s){
    screens.push_back(s);
    currentScreen=0;  
    nbscreens++;  
}

//Methode permettant d'ajouter un objet de type Screen dans le Menu principal
void Menu::addScreen(Screen *s){
    screens.push_back(s);
    nbscreens++; 
}

//Methode permettant d'afficher le Menu principale (les noms associes aux ecrans sont affiches)
void Menu::display(){
    myLcd.clear();
    if(screenEntered){
        screens[currentScreen]->display();
    }else{
        for (unsigned int i=currentScreen;(i<currentScreen+2 && i<nbscreens);i++){
            if(i==currentScreen){
                myLcd.setCursor(0,i-currentScreen);
                myLcd.print(">");
            }
            myLcd.setCursor(1,i-currentScreen);
            myLcd.print(screens[i]->getName());
        }
    }
        
}

//Methode permettant de valider l'affichage de l'ecran selectionne
void Menu::enter(){ 
    if(screenEntered){
        tmp=0;
        screens[currentScreen]->enter();
    }else{
        screenEntered=true;
        tmp=1;
        display();
    }
    
}

//Methode permettant de retourner au Menu principal ou de sortir d'une zone d'edition 
void Menu::back(){ 
    if(tmp==0){
        
        if(screenEntered){
        screens[currentScreen]->back();
        screenEntered=false; 
        //if(not(screens[currentScreen]->getEditing()))screenEntered=false;    //TODO
        }else{
            currentScreen=0;
            display();
        }
    } else {
            screenEntered=false;
            currentScreen=0;
            display();
            tmp=0;
        }
    
    
}

//Methode permettant de positionner le curseur de selection vers l'ecran suivant
void Menu::next(){
    
    if(screenEntered){
        screens[currentScreen]->Next();
    }else{
        if(currentScreen<nbscreens-1) {
            currentScreen++;
        }
    display();
    }
    
}

//Methode permettant de positionner le curseur de selection vers l'ecran precedent
void Menu::prev(){
    
    if(screenEntered){
        screens[currentScreen]->Prev();
    }else{
        if(currentScreen>0) {
            currentScreen--;
        }
        display();
    }
    
}





