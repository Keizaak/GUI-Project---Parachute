Projet IG - Parachute crypté
============================
# Équipe
* ANCETTE Raphaël
* GUIGNOL Camille

# Description
Le but de ce projet était d'afficher un message choisi par l'utilisateur traduit en binaire sous forme de tableau et de parachute, à l'instar du parachute du rover Perseverance récemment arrivé sur Mars.

----------------------------

# Fonctionnalités implémentées
## Interface
![Capture d'écran de l'interface]("etc/gui.jpg")

L'interface s'adapte à la taille de la fenêtre.

## Conversion en binaire
Le message entré par l'utilisateur est filtré à l'aide d'un `QRegExpValidator` qui utilise une expression régulière. De ce fait, nous n'autorisons que les lettres de l'alphabet (minuscules et majuscules) ainsi que deux caractères spéciaux : `@` et `_`. Cela permet d'éviter toute incohérence lors de la traduction en binaire, notamment l'apparition de $-1$.
À partir de ce message, nous récupérons chacun des caractères qui le composent pour les convertir en leur code ASCII. Nous appliquons ensuite un décalage correspondant à la valeur ASCII du caractère `@`. Grâce à cela, la lettre A correspondra à l'entier $1$.
Ensuite, par division euclidienne, on calcule le code binaire de ce caractère sous sept bits.
Enfin, on range la traduction binaire du message dans un vecteur d'entiers afin de pouvoir l'utiliser ultérieurement, notamment lors de l'affichage des représentations graphiques.

## Affichage du tableau binaire
Dans le widget correspondant à l'affichage du tableau binaire, nous parcourons le vecteur construit précédemment puis nous dessinons les différents bits par colonne. Nous obtenons ainsi un tableau contenant sept lignes, une par bit du caractère, et $N$ colonnes, $N$ étant le nombre de caractères du message entré par l'utilisateur.
Enfin, nous affichons ces bits sous forme de cercles, coloriés en gris pour un bit à $0$ et en rouge pour un bit à $1$. Le rayon de chaque cercle dépend de la longueur du message afin de permettre au tableau de toujours être affiché en entier, même si le message est long. Nous utilisons également le rayon afin d'espacer uniformément nos cercles.

## Construction du parachute
Tout d'abord, nous centrons le parachute en fonction de la taille du widget dans lequel il est dessiné.
Ensuite, notre parachute va être composé d'un certain nombre de secteurs (correspondant aux colonnes dans le parachute) et de pistes (correspondant aux lignes dans le parachute) formant des cases trapézoïdales. Ces derniers sont choisis par l'utilisateur.
Chacune des cases sont ensuite dessinées en partant du centre du parachute à partir de l'angle $2\pi$ et dans le sens anti-trigonométrique. Quand nous avons effectué un tour complet, nous pouvons passer à la piste du dessus, et ce, jusqu'à avoir dessiné toutes les cases (au total $nb secteurs* nbpistes$).
Nous parcourons en même temps le tableau binaire afin de pouvoir colorier nos cases avec la bonne couleur : blanc pour un bit à $0$ et rouge pour un bit à $1$.

## Sauvegarde et chargement
Afin de conserver la responsabilité unique, nous créons deux classes : une pour la sauvegarde et une pour le chargement.
### Sauvegarde
Tout d'abord, nous demandons depuis le contrôleur à l'utilisateur l'emplacement du fichier ainsi que son nom et son format à l'aide de `QFileDialog`. Nous récupérons également les valeurs des paramètres à sauvegarder de notre application depuis le modèle (le message, le nombre de pistes et le nombre de secteurs).
Enfin, nous allons donner cela à notre fonction de sauvegarde qui va utiliser `QDataStream` pour écrire ces valeurs dans le fichier.
### Chargement
Nous utilisons le même principe que pour la sauvegarde. Nous demandons d'abord depuis le contrôleur l'emplacement du fichier à charger à l'utilisateur que nous donnons à notre fonction de chargement. Cette dernière vérifie la validité du message contenu dans le fichier et récupère les autres données qui sont envoyées au contrôleur par le biais des paramètres de la fonction, mis sous forme de pointeurs. Le contrôleur peut ensuite affecter au modèle ces valeurs, ce qui aura pour conséquence de déclencher un signal permettant de mettre à jour la vue.

## Traduction de l'application
Pour traduire notre application, nous avons utilisé l'outil `QLinguist` qui génère un fichier `.xml` contenant chaque chaîne de caractères contenue dans l'application et un espace pour la traduction. Il suffit ensuite de le compléter et d'utiliser le même outil afin de récupérer un fichier `.qm`. Ce dernier est ensuite chargé dans le `main` de l'application afin de la traduire.

----------------------------

# Modélisation logicielle
## Architecture
Pour concevoir notre logiciel, nous avons utilisé une architecture MVC (Modèle Vue Contrôleur). Nous avons choisi cette architecture par soucis de simplicité puisque c'était celle utilisée dans les précédents TPs.
Nous avons deux modèles : un contenant les informations sur le nombre de pistes et de secteurs et un autre pour le message et la conversion en binaire. Ainsi, nous garantissons le principe de responsabilité unique, mais également une meilleure clarté du code. En effet, le nombre de pistes et de secteurs n'est utile que pour le dessin du parachute.
Notre vue sera composée du form `.ui` et des différents widgets de l'application (parachute et tableau binaire).
Enfin, notre contrôleur `Main Window` fera le lien entre le modèle et la vue et gérera les actions de l'utilisateur.
## Patrons de conception
Nous utilisons principalement le patron Observateur dans nos modèles. Par l'envoi d'un signal, cela nous permet de mettre à jour automatiquement et facilement la vue à chaque changement de valeurs dans le modèle (message, nombre de secteurs, nombre de pistes).
Pour la sauvegarde et le chargement, nous avions pensé à différents patrons de conception. Cependant, aucun ne correspondait à notre utilisation. En effet, le patron Mémento permet de conserver les différents états de l'application. Le patron Commande, lui, sauvegarde les différentes actions effectuées sur le logiciel. Or, nous souhaitons seulement sauvegarder des données particulières et non pas un historique d'états ou de valeurs. Enfin, le patron Stratégie nous serait utile que si nous souhaitions utiliser différentes méthodes de sauvegarde, ce qui n'est pas le cas ici.

----------------------------

# Améliorations possibles
Bien que soit que notre logiciel soit abouti, il est loin d'être parfait et peut encore être largement amélioré :
* Possibilité de choisir la couleur des cases pour le parachute et le tableau binaire ;
* Dessiner notre parachute de façon plus réaliste en utilisant des parallélogrammes plutôt que des trapèzes pour avoir un effet "dents de scie" ;
* Améliorer l'interface pour la rendre plus ergonomique ;
* Définir un minimum pour le nombre de pistes et de secteurs en fonction de la longueur du message. Cela éviterait de perdre des informations sur la traduction binaire dans le parachute, qui devient trop petit pour lire tous les bits ;
* Définir un maximum sur la longueur du message. Cela éviterait d'avoir un parachute ou tableau qui devient vite illisible ;
* Avoir la traduction qui s'adapte en fonction de la langue du système ;
* Implémenter un "Dark Mode" pour le confort des yeux.
