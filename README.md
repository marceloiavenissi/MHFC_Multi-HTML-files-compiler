# MHFC - Multi HTML files compiler

This project was create in 2019 with aims to compile multi development html files to one file for deploy. 
To that it finds include's tags and gets the value into quotation marks.

## The code operation

It is write in c++ and the algorithm use a state machine to find the tags. 
Then, it extract the partial files paths and replace by partial files contents.

## To use MHFC command

To examplefy a site with four pages, it have in all pages a top bar menu and a footer with contacts. 

So, you can extract the menu and footer to partial files: 

```menu-part.html```
```footer-part.html```

Then, replace on the codes on the pages by include tags.

And to join the code for deploy run this command: 

```
mhfc index.html deploy/index.html
mhfc profiler.html deploy/profiler.html
mhfc login.html deploy/login.html
mhfc contacts.html deploy/contacts.html
```

## To include html parts - the use of the include tag
To include html parts to pages, you should adding they with the tag include and a relative file path by argument.

E.g.:
```<include "header.html"/>```
```<include  'footer.html' >```
