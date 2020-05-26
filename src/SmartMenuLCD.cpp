#include "SmartMenuLCD.h"

LCD mylcd;

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
    if(not(editing)) {
        if(currentObject==nbobjects-1) currentObject--;
        for(i=currentObject+1;i<nbobjects;i++){
            if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
                currentObject=i;
                mylcd.clear();
                mylcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
                mylcd.print(">");
                this->display();
                break;
            }
        }
    } else {
        if(typeid(*objects[currentObject])==typeid(EditableValue)){
            ((EditableValue*)objects[currentObject])->increment();
        }else{  //it is an EditableText
            ((EditableText*)objects[currentObject])->next();

        }
    }  
}

//Methode permettant de selectionner l'objet editable precedent affiche sur l'ecran
void Screen::Prev(){
    int i;
    if(not(editing)) {
        if(currentObject==0) currentObject++;
        for(i=currentObject-1;i>=0;i--){
             if(typeid(*objects[i])==typeid(EditableValue) || typeid(*objects[i])==typeid(EditableText)){
                 currentObject=i;
                 mylcd.clear();
                 mylcd.setCursor(objects[i]->getx()-1,objects[i]->gety());
                 mylcd.print(">");
                 this->display();
                 break;
             }
        }
    } else {
        if(typeid(*objects[currentObject])==typeid(EditableValue)){
            ((EditableValue*)objects[currentObject])->decrement();
        }else{  //it is an EditableText
            ((EditableText*)objects[currentObject])->prev();
            
        }
    }  
}

//Methode permettant d'afficher tous les textes/valeurs de l'ecran courant
void Screen::display(){
     vector<ScreenObject*>::iterator itso;
     mylcd.clear();
    for(itso=objects.begin();itso!=objects.end();itso++){
            (*itso)->display();
    }
    if(editing) objects[currentObject]->display();//last to be displayed to keep last cursor pos
}

void Screen::enter(){
    if(typeid(*objects[currentObject])==typeid(EditableValue)){
        editing=true;
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
    mylcd.clear();
    if(screenEntered){
        screens[currentScreen]->display();
    }else{
        for (unsigned int i=currentScreen;(i<currentScreen+2 && i<nbscreens);i++){
            if(i==currentScreen){
                mylcd.setCursor(0,i-currentScreen);
                mylcd.print(">");
            }
            mylcd.setCursor(1,i-currentScreen);
            mylcd.print(screens[i]->getName());
        }
    }
        
}

//Methode permettant de valider l'affichage de l'ecran selectionne
void Menu::enter(){ 
    if(screenEntered){
        screens[currentScreen]->enter();
    }else{
        screenEntered=true;
    }
    display();
}

//Methode permettant de retourner au Menu principal ou de sortir d'une zone d'edition 
void Menu::back(){ 
    if(screenEntered){
        screens[currentScreen]->back();
        if(true)screenEntered=false;    //TODO
    }else{
        screenEntered=false;
        currentScreen=0;
    }
    display();
    
}

//Methode permettant de positionner le curseur de selection vers l'ecran suivant
void Menu::next(){
    
    if(screenEntered){
        screens[currentScreen]->Next();
    }else{
        if(currentScreen<nbscreens-1) {
            currentScreen++;
        }
    }
    display();
}

//Methode permettant de positionner le curseur de selection vers l'ecran precedent
void Menu::prev(){
    
    if(screenEntered){
        screens[currentScreen]->Prev();
    }else{
        if(currentScreen>0) {
            currentScreen--;
        }
    }
    display();
}





