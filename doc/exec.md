# **Execution**

## **1. access**
    int access(const char *pathname, int mode);

Definition
- access() vérifie si le processus appelant peut accéder au fichier pathname.
- Le mode indique la (les) vérification(s) d'accessibilité à effectuer.
- F_OK R_OK, W_OK et X_OK servent à tester respectivement, si le fichier existe, la lecture, l'écriture et l'exécution du fichier.

Return Value
- renvoie 0 s'il réussit (toutes les requêtes sont autorisées)
- -1 s'il échoue (au moins une requête du mode est interdite), auquel cas errno contient le code d'erreur 127

---

## **2. open**
    #include <sys/types.h>
    #include <sys/stat.h>
    #include <fcntl.h>

    int open(const char *pathname, int flags, mode_t mode);

Definition
- Un appel à open() crée une nouvelle description de fichier ouvert
- Par défaut, le nouveau descripteur de fichier est configuré pour rester ouvert au travers d'un execve
- Le paramètre flags doit inclure l'un des mode d'accès suivants : O_RDONLY, O_WRONLY ou O_RDWR.

Return Value
- renvoient le nouveau descripteur de fichier s'ils réussissent
- -1 s'ils échouent, auquel cas errno contient le code d'erreur 127

---

## **3. read**
    ssize_t read(int fd, void *buf, size_t count);

Definition
- read() lit jusqu'à count octets depuis le descripteur de fichier fd

Return Value
- renvoie -1 s'il échoue, auquel cas errno contient le code d'erreur 127
- Sinon, read() renvoie le nombre d'octets lus (0 en fin de fichier)

---

## **4. execve**
    int execve(const char *fichier, char *const argv[], char *const envp[]);   

Definition
- execve() exécute le programme correspondant au fichier.
- Celui-ci doit être un exécutable binaire.

`int main(int argc, char *argv[], char *envp[]).`

Return Value
- en cas d'échec il renvoie -1 et errno contient le code d'erreur