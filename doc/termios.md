# **Termios**

## **1. tcsetattr**
    int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);

Definition
- Configuration du terminal  
- récupère les paramètres associés à l'objet référencé par fd et les stocke dans la structure termios pointée par termios_p.

Return Value
- renvoie 0 s'il réussit
- -1 s'il échoue auquel cas errno contient le code d'erreur 127

---

## **2. tcgetattr**
    int tcgetattr(int fd, struct termios *termios_p);

Definition
- Configuration du terminal  
- fixe les paramètres du terminal

Return Value
- renvoie 0 s'il réussit
- -1 s'il échoue auquel cas errno contient le code d'erreur 127

---
