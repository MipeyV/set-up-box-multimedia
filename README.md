# **Séance du 09-12-2025**  

## **4ᵉ étape : Photos et Vidéos**  

Contrairement à la fonction d'affichage:  

- elle ne peut pas avoir d'implementation au niveau de la classe de base (car chaque type d'objet nécessite un programme différent pour être joué).

### Comment appelle-t-on ce type de méthode et comment faut-il les déclarer ?

En C++, on appelle cela une **méthode virtuelle pure** (ou **méthode abstraite**).  
Elle est déclarée à l’aide du mot-clé `virtual` suivi de `= 0`.

Dans notre cas, la méthode `play()` est déclarée ainsi dans la classe de base `Multimedia` :

```cpp
virtual void play() const = 0;
```

### Si vous avez fait ce qui précède comme demandé, il ne sera plus possible d'instancier des objets de la classe de base. Pourquoi ?

On ne pourra plus instancier la classe de base car elle devient une **classe abstraite** du fait qu’elle possède au moins une **méthode virtuelle pure** (ou méthode abstraite), à savoir la méthode :

```cpp
virtual void play() const = 0;
```

## **5ème étape : Traitement uniforme (en utillisant le polymorphisme)**  

On veut maintenant pouvoir traiter de manière uniforme une liste comprenant à la fois des photos et des vidéos sans avoir à se préoccuper de leur type.  

Pour ce faire créer dans main.cpp un tableau dont les éléments sont tantôt une photo tantôt une vidéo. Ecrire ensuite une boucle permettant d'afficher les attributs de tous les élements du tableau ou de les "jouer". Cette boucle doit traiter tous les objets dérivant de la classe de base de la même manière.

### Quelle est la propriété caractéristique de l'orienté objet qui permet de faire cela ?

Le polymorphisme

### Qu'est-il spécifiquement nécessaire de faire dans le cas du C++ ?

En C++, pour que le polymorphisme fonctionne, il est nécessaire de :

- **déclarer les méthodes de la classe de base comme `virtual`** (ici `print` et `play`) :
```cpp
virtual std::ostream& print(std::ostream& os) const;
virtual void play() const = 0;
```

### Quel est le type des éléments du tableau : le tableau doit-il contenir des objets ou des pointeurs vers ces objets ? Pourquoi ? Comparer à Java.

Le tableau doit contenir des pointeurs de type Multimedia :  

```cpp
std::array<Multimedia*, 4> tab;
```  

En Java, les obbjets sont des références (pointeurs) vers le type d'objet, mais il n'est pas differencié dans sa déclaration car il se déclare comme un type normal. 

### Compiler, exécuter et vérifier que le résultat est correct

Le résultat attendu est l'exécution de la méthode play, associée à la bonne classe de l'objet, et c'est bien le cas ! 

# **Séance du 16-12-2025**

## **6ème étape : Films et tableaux**

**Important :**  

On définit un tableau par deux choses :  
- l'adresse en mémoire du premier élément (int*)
- sa taille (int)  

```cpp
int* hapters;
int  nbChapters;
```  

Cela implique plusieurs choses dans l'accès et les modifications des données.  

Lorsqu'on donne en entrée un tableau, ce qui est vraiment transmis, c'est son adresse en mémoire de son premier élément, donc s'il faut modifier un tableau, il faut aussi indiquer sa taille pour itérer dessus. 

Par ce fait, il faut donc pour :
- Les setters : 
    - Donner en arguments l'adresse, et la taille du tableau
    - Supprimer en amont le tableau existant à remplacer
    - Réallouer un espace en mémoire dépendant de la taille du nouveau tableau si cela diffère de l'ancien tableau
    - Ittérer pour affecter les valeurs du nouveau tableau sur notre tableau
- Les accesseurs : 
    - Ils doivent retourner des adresses de tableau const afin de ne pas pouvoir altérer les données

## **7ème étape : Destruction et copie des objets**

### Parmi les classes précédemment écrites quelles sont celles qu'il faut modifier afin qu'il n'y ait pas de fuite mémoire quand on détruit les objets ? Modifiez le code de manière à l'éviter.

Il n'y a que dans la classe Film, où l'on fait intervenir new, lorsqu'on initialise notre tableau avec l'allocation en mémoire. Il faut donc s'assurer que notre destructeur libère correctement la mémoire avec delete, lorsqu'on modifie l'objet sur son tableau ou supprime notre objet.

### La copie d'objet peut également poser problème quand ils ont des variables d'instance qui sont des pointeurs. Quel est le problème et quelles sont les solutions ? Implementez-en une.

Même soucis que les tableaux, les pointeurs doivent pointer vers des valeurs valables, pour éviter les pointeurs pendants.