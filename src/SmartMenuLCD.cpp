#include "SmartMenuLCD.h"

LCD mylcd;

//Variable comptant le nombre d'ecrans crees
unsigned int Menu::nbscreens=0;
//Variable comptant le nombre d'objets crees
unsigned int Screen::nbobjects=0;


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
}

//Methode permettant de selectionner l'objet editable precedent affiche sur l'ecran
void Screen::Prev(){
    int i;
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
}

//Methode permettant d'afficher tous les textes/valeurs de l'ecran courant
void Screen::display(){
 
     vector<ScreenObject*>::iterator itso;
     
    for(itso=objects.begin();itso!=objects.end();itso++){
            (*itso)->display();
    }
}


/*********** Constructeurs/methodes de la classe Menu *************/

//constructeur par defaut initialisant un ecran proposant un affichage de la temperature
Menu::Menu(){                                   
    Text *obj = new Text("Temperature:",0,0);
    string nom="Temperature";
    Screen* newScreen = new Screen(obj,nom);
    screens.push_back(newScreen);
    currentScreen=0;  
    nbscreens++; 
}

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
    unsigned int i;

   mylcd.clear();
    for (i=currentScreen;(i<currentScreen+2 && i<nbscreens);i++){
        if(i==currentScreen){
            mylcd.setCursor(0,i-currentScreen);
            mylcd.print(">");
        }
         mylcd.setCursor(1,i-currentScreen);
         mylcd.print(screens[i]->getName());
    }
        
}

//Methode permettant de valider l'affichage de l'ecran selectionne
void Menu::enter(){ 
    mylcd.clear();
    screens[currentScreen]->display();
}

//Methode permettant de retourner au Menu principal ou de sortir d'une zone d'edition 
void Menu::back(){  
    currentScreen=0;
    display();
}

//Methode permettant de positionner le curseur de selection vers l'ecran suivant
void Menu::next(){
 if(currentScreen<nbscreens) {
        currentScreen++;
    }
    display();
}

//Methode permettant de positionner le curseur de selection vers l'ecran precedent
void Menu::prev(){
    if(currentScreen>0) {
        currentScreen--;
    }
    display();
}





