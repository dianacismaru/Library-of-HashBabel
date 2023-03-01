Copyright (C) 2022 Cismaru Diana-Iuliana (311CA / 2021-2022)

# The library of HashBabel

## Description of the project:

> 	For the implementation of this project I was able to work with data
structures, especially with **hashtables**. The main header I have been using
(`main.h`) includes important data about the structures that I've created.
Each command that involved working with books or users was supported by the
generic hashtable functions. 

## Further details:
>	Although there are quite a lot of comments in the code, there are a few things
that require additional explanation:

### 1. Book commands
> 	Before doing the actual task, I managed to check if the book or definition
was already added.

### 2. User commands
>	For this part, I had to do a lot of verifications before working with users:
I had to check whether the user was already registered into the system, whether
it was banned, whether he wanted to borrow a book that was already borrowed or
did not even exist, or he wanted to return a book that he did not even borrow.

> User commands involved working with the structure that I've created and
constantly updating the numbers from the variables inside the structure, such
as repeatedly calculating the score of a user or keeping track of borrowing
situation.

### 3. Rankings
>	This was my favorite part: I managed to create arrays of books and users
and then I used qsort function that worked perfectly for
the compare functions that I've made with the specific criteria.

### Other comments:
>	Although I am happy with the final product, I have to mention the fact
that I decided to use static buffers, because dynamically allocation could
have caused timeout on some tests; also, having to free the memory for all
the buffers would have ruined my modularization (that I'm very proud of),
because I would have had to duplicate many lines of code.

>	From another perspective, I am glad that I was able to work with
generic hashtables.

### Resources:

1. [Linked-List implementation](https://ocw.cs.pub.ro/courses/sd-ca/laboratoare/lab-04)
2. [Hash Function](http://www.cse.yorku.ca/~oz/hash.html)
3. [Resizing](https://www.algolist.net/Data_structures/Hash_table/Dynamic_resizing)
