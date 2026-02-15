# **Compte Rendu - TP C++ / TP JAVA-SWING**
---
# **TP - C++**
---
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

## **8ème étape : Créer des groupes**

### Le groupe ne doit pas détruire les objets quand il est détruit car un objet peut appartenir à plusieurs groupes (on verra ce point à la question suivante). On rappelle aussi que la liste d'objets doit en fait être une liste de pointeurs d'objets. Pourquoi ? Comparer à Java.

La liste ne doit pas contenir en elle même des instances d'objets, mais une liste de pointeurs, qui chacun, pointe vers l'instance d'un objet. Cela permet de ne pas re-instancier à chaque fois un objet. Cependant, il faut faire attention avec ce type d'objet qui peuvent contenir des pointeurs pendants si jamais l'objet vers lequel le pointeur pointe advenait à être détruit.

## **9ème étape : Gestion automatique de la mémoire**

### Utilisation des smart pointers (shared_ptr)

Les **smart pointers** gèrent automatiquement la mémoire : les objets sont supprimés quand plus personne ne les utilise. Cela évite les fuites mémoires et les pointeurs pendants.

**Modifications effectuées :**
- Remplacement de `std::list<Multimedia*>` par `std::list<std::shared_ptr<Multimedia>>` dans la classe `Group`
- Ajout de messages de destruction dans les destructeurs pour vérifier que tout fonctionne correctement

## **10ème étape : Gestion cohérente des données**

### Objectif

Créer une classe `Database` qui gère **tous** les objets multimédia et groupes de manière centralisée et cohérente.

### Architecture

```cpp
Database
├─ map<string, shared_ptr<Multimedia>>  // Tous les objets (Photo, Video, Film)
└─ map<string, shared_ptr<Group>>       // Tous les groupes
```

### Méthodes implémentées

**Création :**
- `createPhoto(name, path, latitude, longitude)` → crée une Photo et l'enregistre
- `createVideo(name, path, duration)` → crée une Video et l'enregistre
- `createFilm(name, path, duration, chapters, nbChapters)` → crée un Film et l'enregistre
- `createGroup(name)` → crée un Group et l'enregistre

**Recherche et affichage :**
- `search(name)` → cherche un objet et affiche ses infos
- `searchGroup(name)` → cherche un groupe et affiche son contenu
- `printAll()` → affiche tous les objets multimédia
- `printAllGroups()` → affiche tous les groupes

**Lecture :**
- `play(name)` → joue un objet multimédia par son nom

### Avantages de cette approche

- **Cohérence** : Un seul endroit pour créer les objets (évite les incohérences)
- **Retrouvabilité** : Accès direct par le nom grâce aux `map`
- **Préparation serveur** : Structure prête pour le Point 11 (client/serveur)

### Comment interdire la création directe d'objets avec `new` ?

On pourrait rendre les constructeurs des classes Multimedia, Photo, Video, Film **private**, et faire de Database une **classe amie (friend)**. Cependant, pour simplifier, nous laissons les constructeurs publics et comptons sur le respect du protocole de la Database.


## **11ème étape : Client / Serveur**

On a réalisé un serveur TCP pour permettre à un client d’interroger la base multimédia à distance.
Le serveur écoute sur le **port 3331**, lit une commande par ligne, puis renvoie une réponse texte nettoyée.

### Commandes supportées
- `search` `<nom>` : recherche un objet et affiche ses infos
- `play` `<nom>` : lance la lecture d’un objet
- `list` : affiche tous les objets
- `groups` : affiche tous les groupes  

Une base minimale est créée au démarrage (photo/vidéo/film) pour pouvoir tester rapidement les commandes.

---
# **TP - JAVA-SWING** :
---

## **1ère étape : Fenêtre principale et quelques intéracteurs**

Dans cette partie, on a créé une première Classe `SwingClient` qui sert de point d'entrée et lance l'interface Swing.

On a aussi une classe `PrincipalWindow` qui représente la fenêtre principale et contient les boutons comme attributs.

## **2ème étape : Menus, barre d'outils et actions**

On a ajouté une **barre de menus** (`JMenuBar` + `JMenu`) et une **barre d’outils** (`JToolBar`) placée au Nord de la fenêtre.  

Les commandes du menu et de la toolbar réutilisent les mêmes Actions (`AbstractAction`) que les boutons, ce qui évite de dupliquer le code et garantit un comportement identique partout.

## **3ème étape : Intéraction Client/Serveur**

On a integre le Client.java (equivalent Java de client.cpp) dans le package swing puis on l'a instantie dans PrincipalWindow.
Les actions Search et Play envoient respectivement les requetes search <nom> et play <nom> au serveur C++.
La reponse est affichee dans le JTextArea, et l'appel reseau est fait dans un thread pour ne pas bloquer l'interface.

## **4eme etape : Makefile Java**

On a adapte le Makefile dans swing/ pour compiler et lancer le client Swing avec un simple make run.
Le javac -d . genere les classes dans le bon repertoire (package swing) et java -cp . swing.SwingClient lance l'application.