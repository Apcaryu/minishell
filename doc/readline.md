# **readline**
    #include <stdio.h>
    #include <readline/readline.h>
    #include <readline/history.h>

    char *readline(const char *prompt);

Definition
- Read a line from the terminal and return it, using a prompt.
- The line returned is allocated with malloc(3).

Return Value
- It return the line read
- If prompt is NULL or the empty string, no prompt is issued.

---

## **1. rl_clear_history**
    void rl_clear_history(void);

Definition
- Clear the history list by deleting all of the entries, in the same manner as the History library’s clear_history() function. 
- This differs from clear_history because it frees private data Readline saves in the history list.

Return Value
- Void

---

## **2. rl_on_new_line**
    int rl_on_new_line(void);

Definition
- Tell the update functions that we have moved onto a new (empty) line, usually after outputting a newline. 

Return Value
- boolean ?

---

## **3. rl_replace_line**
    void rl_replace_line(const char *text, int clear_undo);

Definition
- Replace the contents of rl_line_buffer with text. The point and mark are preserved, if possible. 
- If clear_undo is non-zero, the undo list associated with the current line is cleared.

Return Value
- Void

---

## **4. rl_redisplay**
    void rl_redisplay(void);

Definition
- Change what's displayed on the screen to reflect the current contents of rl_line_buffer.

Return Value
- Void

---

## **5. add_history**
    void add_history(const char *string);

Definition
- Place string at the end of the history list.
- If you want the user to be able to get at the line later, (with C-p for example), you must call `add_history(input)` to save the line away in a history list of such lines.

Return Value
- Void
