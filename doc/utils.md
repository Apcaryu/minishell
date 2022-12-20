# **utils**

## **1. getcwd**
    char *getcwd(char *buf, size_t size);

Definition
- Copie le chemin d'accès absolu du répertoire de travail courant dans la chaîne pointée par buf, qui est de longueur size.
- Si le chemin du répertoire en cours nécessite un tampon plus long que size octets, la fonction renvoie NULL.
- Si buf est NULL, le comportement de getcwd() est indéfini.
- malloc utilisee, ne pas oublier de free

Return Value
- NULL en cas d'échec, avec errno contenant le code d'erreur.
- En cas de réussite buf est renvoyé.

---

## **2. chdir**
    int chdir(const char *path);

Definition
- remplace le répertoire de travail courant du processus appelant par celui indiqué dans le chemin path

Return Value
- renvoient 0 s'ils réussissent
- -1 s'ils échouent, auquel cas errno contient le code d'erreur 127

---

## **3. stat**
    int stat(const char *path, struct stat *buf);

Definition
- récupère l'état du fichier pointé par path et remplit le tampon buf.

Return Value
- renvoie -1 s'il échoue, auquel cas errno contient le code d'erreur 127
- 0 en cas de reussite

---

## **4. lstat**
    int lstat(const char *path, struct stat *buf);

Definition
- lstat() est identique à stat(), sauf que si path est un lien symbolique, il donne l'état du lien lui-même plutôt que celui du fichier visé.

Return Value
- renvoie -1 s'il échoue, auquel cas errno contient le code d'erreur 127
- 0 en cas de reussite

---

## **5. fstat**
    int fstat(int fd, struct stat *buf);

Definition
- fstat() est identique à stat(), sauf que le fichier ouvert est pointé par le descripteur fd, obtenu avec open(2).

Return Value
- renvoie -1 s'il échoue, auquel cas errno contient le code d'erreur 127
- 0 en cas de reussite

---

## **6. unlink**
    int unlink(const char *pathname);  

Definition
- unlink() détruit un nom dans le système de fichiers.
- Si ce nom était le dernier lien sur un fichier, et si aucun processus n'a ouvert ce fichier, ce dernier est effacé, et l'espace qu'il utilisait est rendu disponible.
- Si le nom était le dernier lien sur un fichier, mais qu'un processus conserve encore le fichier ouvert, celui-ci continue d'exister jusqu'à ce que le dernier descripteur le référençant soit fermé.
- Si le nom correspond à un lien symbolique, le lien est supprimé.
- Si le nom correspond à une socket, une FIFO, ou un périphérique, le nom est supprimé mais les processus qui ont ouvert l'objet peuvent continuer à l'utiliser.  

Return Value
- renvoie -1 s'il échoue, auquel cas errno contient le code d'erreur 127
- 0 en cas de reussite

---

## **7. opendir**
    DIR *opendir(const char *name);

Definition
- La fonction opendir() ouvre un flux répertoire correspondant au répertoire name, et renvoie un pointeur sur ce flux. Le flux est positionné sur la première entrée du répertoire.

Return Value
- renvoient un pointeur sur le flux répertoire
- NULL si une erreur se produit, auquel cas errno contient le code d'erreur

---

## **8. readdir**
    struct dirent *readdir(DIR *dir);

Definition
- Consulter un répertoire  
- La fonction readdir() renvoie un pointeur sur une structure dirent représentant l'entrée suivante du flux répertoire pointé par dir.

Return Value
- renvoient un pointeur sur le flux répertoire
- NULL si une erreur se produit, auquel cas errno contient le code d'erreur

---

## **9. closedir**
    #include <sys/types.h>
    #include <dirent.h>

    int closedir(DIR *dir); 

Definition
- La fonction closedir() ferme le flux de répertoire associé à dir.

Return Value
- renvoie 0 si elle réussit
- -1 si elle échoue, auquel cas errno contient le code d'erreur. 

---

## **10. isatty**
    int isatty(int desc);

Definition
- Vérifier si un descripteur se rapporte à un terminal  

Return Value
- renvoie 1 si desc est un descripteur de fichier ouvert connecté à un terminal,
- 0

---

## **11. ttyname**
    char *ttyname(int fd);

Definition
- Obtenir le nom d'un terminal   

Return Value
- renvoie un pointeur sur le chemin d'accès.
- renvoie NULL et remplit errno avec le code d'erreur.

---

## **12. ttyslot**
    int ttyslot(void);

Definition
- Trouver l'emplacement du terminal en cours dans un fichier   

Return Value
- Si elle réussit, cette fonction renvoie le numéro d'entrée
- Si elle échoue elle renvoie 0 ou -1 selon les differents systeme d'exploitation

---

## **13. ioctl**
    #include <sys/ioctl.h>

    int ioctl(int d, int requête, ...);  

Definition
- Contrôler les périphériques  
- La fonction ioctl() modifie le comportement des périphériques sous-jacents des fichiers spéciaux.
- Le second argument est le code de la requête dépendant du périphérique.
- Le troisième argument est un pointeur non typé

Return Value
- -1 si elle échoue
- 0 si elle réussit

---

## **14. getenv**
    char *getenv(const char *name);

Definition
- La fonction getenv() recherche dans la liste des variables d'environnement un variable nommée name, et renvoie un pointeur sur la chaîne value correspondante.  

Return Value
- renvoie un pointeur sur la valeur correspondante, dans l'environnement du processus,
- NULL s'il n'y a pas de correspondance