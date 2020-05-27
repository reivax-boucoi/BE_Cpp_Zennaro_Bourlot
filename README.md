# BE C++

> ZENNARO Thomas <br>
> BOURLOT Xavier <br>

---
### INSA Toulouse 4A 2019-2020

Le projet est une libraire LCD permettant la gestion de menus et d'écrans, ainsi que l'affichage et l'édition de valeurs. Un diagramme de classe présente la hiérarchisation du projet. Des cas d'utilisations ainsi qu'un diagramme de séquence complètent cette description.

---
#### Structuration du code :

- `SmartMenuLCD` implémente les classes `Screen` et `Menu`
- `Encoder` simule un encodeur basique (fonctions Enter/Back/Up/Down)
- `LCDObject` implémente les classes `Value` et `Text`, ainsi que `EditableValue` et `EditableText`
- `core_simulation` a été étendu pour inclure un périphérique LCD.

> Note : Encoder et LCD on été implémentés directement (sans passer par `mydevices`) afin de contourner les limitations de l'interface arduino, le but du projet n'étant pas le développement de ces interfaces.



